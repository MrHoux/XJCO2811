//
// Chat window implementation
//

#include "chatwindow.h"
#include <QFrame>
#include <QScrollArea>
#include <QPainterPath>
#include <QPixmap>
#include <QPainter>
#include <QVariant>
#include <QMouseEvent>
#include <functional>
#include <QBitmap>
#include <QDebug>


namespace {
class TapFilter : public QObject {
public:
    std::function<void()> onClick;
    explicit TapFilter(QObject *parent = nullptr) : QObject(parent) {}
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress && onClick) onClick();
        return QObject::eventFilter(obj, event);
    }
};
}

ChatWindow::ChatWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(12);

    stack = new QStackedWidget(this);
    root->addWidget(stack);

    // list page
    listPage = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(listPage);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setSpacing(10);

    QLabel *title = new QLabel("Chat");
    title->setStyleSheet("font-size:20px; font-weight:800;");
    listLayout->addWidget(title);

    QScrollArea *listArea = new QScrollArea();
    listArea->setFrameShape(QFrame::NoFrame);
    listArea->setWidgetResizable(true);
    QWidget *listWrap = new QWidget();
    listWrapLayout = new QVBoxLayout(listWrap);
    listWrapLayout->setContentsMargins(0, 0, 0, 0);
    listWrapLayout->setSpacing(10);
    listArea->setWidget(listWrap);
    listLayout->addWidget(listArea);

    stack->addWidget(listPage);

    // thread page
    threadPage = new QWidget();
    QVBoxLayout *threadPageLayout = new QVBoxLayout(threadPage);
    threadPageLayout->setContentsMargins(0, 0, 0, 0);
    threadPageLayout->setSpacing(8);

    QHBoxLayout *header = new QHBoxLayout();
    header->setSpacing(10);
    threadAvatar = new QLabel();
    threadAvatar->setFixedSize(42, 42);
    threadAvatar->setStyleSheet("border:2px solid #0b0b0b; border-radius:21px;");
    header->addWidget(threadAvatar);

    QVBoxLayout *headerText = new QVBoxLayout();
    headerText->setContentsMargins(0, 0, 0, 0);
    headerText->setSpacing(0);
    threadTitle = new QLabel("Friend");
    threadTitle->setStyleSheet("font-weight:700; font-size:16px;");
    threadHandle = new QLabel("@friend");
    threadHandle->setStyleSheet("color:#666;");
    headerText->addWidget(threadTitle);
    headerText->addWidget(threadHandle);
    header->addLayout(headerText);
    header->addStretch();

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setStyleSheet("padding:6px 12px; border:2px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:600;");
    QObject::connect(backBtn, &QPushButton::clicked, this, [this]() {
        stack->setCurrentWidget(listPage);
    });
    header->addWidget(backBtn);
    threadPageLayout->addLayout(header);

    QScrollArea *threadArea = new QScrollArea();
    threadArea->setFrameShape(QFrame::NoFrame);
    threadArea->setWidgetResizable(true);
    QWidget *threadWrap = new QWidget();
    threadLayout = new QVBoxLayout(threadWrap);
    threadLayout->setContentsMargins(0, 0, 0, 0);
    threadLayout->setSpacing(10);
    threadLayout->addStretch();
    threadArea->setWidget(threadWrap);
    threadPageLayout->addWidget(threadArea);

    QHBoxLayout *inputRow = new QHBoxLayout();
    inputRow->setSpacing(8);
    input = new QLineEdit();
    input->setPlaceholderText("Message");
    input->setStyleSheet("padding:10px; border:2px solid #0b0b0b; border-radius:14px;");
    QPushButton *sendBtn = new QPushButton("Send");
    sendBtn->setStyleSheet("padding:10px 16px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
    inputRow->addWidget(input);
    inputRow->addWidget(sendBtn);
    threadPageLayout->addLayout(inputRow);

    QObject::connect(sendBtn, &QPushButton::clicked, this, [=]() {
        const QString text = input->text().trimmed();
        if (text.isEmpty()) return;
        history.append({true, text});
        rebuildThreadView();
        input->clear();
    });
    QObject::connect(input, &QLineEdit::returnPressed, sendBtn, &QPushButton::click);

    stack->addWidget(threadPage);
}

void ChatWindow::setThreads(const QList<FriendData> &friends) {
    threads = friends;
    if (!listWrapLayout) return;

    // safe cleaning
    while (QLayoutItem* child = listWrapLayout->takeAt(0)) {
        if (QWidget* widget = child->widget()) {
            widget->deleteLater();  // safe cleaning  widget
        }
        delete child;  // delete layout item
    }

    for (int i = 0; i < threads.size(); ++i) {
        const auto &f = threads[i];
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background:#ffffff; border:2px solid #0b0b0b; border-radius:16px; }");
        QHBoxLayout *cardLayout = new QHBoxLayout(card);
        cardLayout->setContentsMargins(10, 10, 10, 10);
        cardLayout->setSpacing(10);

        QPushButton *avatarBtn = new QPushButton();
        avatarBtn->setFlat(true);
        avatarBtn->setFixedSize(48, 48);
        avatarBtn->setIconSize(QSize(48, 48));
        avatarBtn->setStyleSheet("border:2px solid #0b0b0b; border-radius:24px; background:#ffffff;");
        QPixmap pm = makeAvatarPixmap(f.avatar, 48);
        if (!pm.isNull()) avatarBtn->setIcon(QIcon(pm));
        cardLayout->addWidget(avatarBtn);

        QVBoxLayout *info = new QVBoxLayout();
        info->setContentsMargins(0, 0, 0, 0);
        info->setSpacing(0);
        QPushButton *name = new QPushButton(f.name);
        name->setFlat(true);
        name->setStyleSheet("text-align:left; font-weight:700; font-size:15px; color:#0b0b0b;");
        QPushButton *preview = new QPushButton("Tap to open chat");
        preview->setFlat(true);
        preview->setStyleSheet("text-align:left; color:#666;");
        info->addWidget(name);
        info->addWidget(preview);
        cardLayout->addLayout(info);
        cardLayout->addStretch();

        QPushButton *open = new QPushButton("CHAT");
        open->setStyleSheet("padding:6px 12px; border:2px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:600;");
        cardLayout->addWidget(open);

        listWrapLayout->addWidget(card);

        auto openChat = [=]() { openThread(i); };
        QObject::connect(open, &QPushButton::clicked, this, [=]() { openChat(); });
        QObject::connect(name, &QPushButton::clicked, this, [=]() { openChat(); });
        QObject::connect(preview, &QPushButton::clicked, this, [=]() { openChat(); });

        TapFilter *cardTap = new TapFilter(card);
        cardTap->onClick = openChat;
        card->installEventFilter(cardTap);

        QObject::connect(avatarBtn, &QPushButton::clicked, this, [=]() {
            emit showProfile(f);
        });
    }
    listWrapLayout->addStretch();
}

QWidget* ChatWindow::buildThreadBubble(const Message &m) {
    QWidget *wrap = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(wrap);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    QLabel *bubble = new QLabel(m.text);
    bubble->setWordWrap(true);
    bubble->setTextInteractionFlags(Qt::TextSelectableByMouse);
    bubble->setStyleSheet(QString("padding:10px 14px; border-radius:16px; border:2px solid #0b0b0b; background:%1;")
                          .arg(m.outgoing ? "#ffffff" : "#f2f2f2"));

    if (m.outgoing) {
        layout->addStretch();
        layout->addWidget(bubble);
    } else {
        layout->addWidget(bubble);
        layout->addStretch();
    }
    return wrap;
}

void ChatWindow::rebuildThreadView() {
    // safe cleaning
    while (QLayoutItem* child = threadLayout->takeAt(0)) {
        if (QWidget* widget = child->widget()) {
            widget->deleteLater();
        }
        delete child;
    }

    // rebuild the message bubble
    for (const auto &m : history) {
        threadLayout->addWidget(buildThreadBubble(m));
    }
    threadLayout->addStretch();
}

void ChatWindow::openThread(int index) {
    if (index < 0 || index >= threads.size()) return;
    const auto &f = threads.at(index);
    QPixmap pm = makeAvatarPixmap(f.avatar, 42);
    if (!pm.isNull()) {
        threadAvatar->setPixmap(pm);
    } else {
        threadAvatar->setPixmap(QPixmap());
    }
    threadTitle->setText(f.name);
    threadHandle->setText(f.handle);

    history.clear();
    history.append({false, "Nice to meet you."});
    history.append({true, "Nice to meet you too."});
    history.append({false, "How's your day going?"});
    history.append({true, "Pretty good, thanks!"});
    rebuildThreadView();

    stack->setCurrentWidget(threadPage);
}

void ChatWindow::openThreadByIndex(int index) {
    openThread(index);
}

QPixmap ChatWindow::makeAvatarPixmap(const QString &path, int size) {

    QPixmap src(path);
    if (src.isNull()) {
        // 如果头像加载失败，创建简单的默认头像
        QPixmap defaultPixmap(size, size);
        defaultPixmap.fill(QColor("#e0e0e0"));
        return defaultPixmap;
    }

    //scale
    QPixmap scaled = src.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap mask(size, size);
    mask.fill(Qt::transparent);     //initially transparent
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing, true);   //edge smoothing
    painter.setBrush(Qt::white);     //effective area
    painter.setPen(Qt::NoPen);      //no outline
    painter.drawEllipse(0, 0, size, size);     //circular filling

    scaled.setMask(mask.createMaskFromColor(Qt::transparent));    //cut out

    QPixmap result(size, size);
    result.fill(Qt::transparent);
    QPainter out(&result);
    out.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath clipPath;

    clipPath.addEllipse(0, 0, size, size);    //clipping Path
    out.setClipPath(clipPath);      //set the path
    out.drawPixmap(0, 0, scaled);   //result
    return result;
}
