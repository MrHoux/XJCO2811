//
//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include <iostream>
#include <algorithm>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFileDialog>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QList>
#include <functional>
#include <QtCore/QString>
#include <QEvent>
#include <QMouseEvent>
#include <QtWidgets/QDialog>
#include "chatwindow.h"
#include "the_button.h"
#include "friends_data.h"

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << Qt::endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << Qt::endl;
        }
    }

    return out;
}

// helper: draw a heart outline/fill icon for like buttons
QIcon makeHeartIcon(bool filled, int size = 22) {
    QPixmap pm(size, size);
    pm.fill(Qt::transparent);
    QPainter painter(&pm);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const qreal w = size;
    const qreal h = size;
    QPainterPath heart;
    heart.moveTo(w * 0.50, h * 0.82);
    heart.cubicTo(w * 0.15, h * 0.60, w * 0.05, h * 0.28, w * 0.26, h * 0.20);
    heart.cubicTo(w * 0.44, h * 0.13, w * 0.50, h * 0.26, w * 0.50, h * 0.30);
    heart.cubicTo(w * 0.50, h * 0.26, w * 0.56, h * 0.13, w * 0.74, h * 0.20);
    heart.cubicTo(w * 0.95, h * 0.28, w * 0.85, h * 0.60, w * 0.50, h * 0.82);

    painter.setPen(QPen(QColor("#0b0b0b"), 2));
    if (filled) painter.setBrush(QColor("#e63946"));
    painter.drawPath(heart);
    return QIcon(pm);
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder (prompt if not provided)
    std::vector<TheButtonInfo> videos;
    QString folder;
    if (argc == 2) {
        folder = QString::fromLocal8Bit(argv[1]);
    }
    if (folder.isEmpty()) {
        folder = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Select video folder"), QDir::homePath());
    }
    if (!folder.isEmpty()) {
        videos = getInfoIn(folder.toStdString());
    }

    if (videos.size() == 0) {
        QMessageBox::information(
                    NULL,
                    QString("FeeL"),
                    QString("no videos found in selected folder."));
        exit(-1);
    }

    // create the main window with a centered phone mock
    QWidget window;
    window.setWindowTitle("FeeL");
    window.setMinimumSize(520, 900);

    QHBoxLayout *root = new QHBoxLayout();
    root->setContentsMargins(40, 30, 40, 30);
    root->addStretch();
    window.setLayout(root);
    window.setStyleSheet("QWidget { font-family: 'Segoe UI'; }");

    QFrame *phone = new QFrame();
    phone->setObjectName("phoneFrame");
    phone->setMinimumWidth(360);
    phone->setStyleSheet("#phoneFrame { background:#ffffff; border:2px solid #0b0b0b; border-radius:46px; }");
    QVBoxLayout *phoneLayout = new QVBoxLayout(phone);
    phoneLayout->setSpacing(12);
    phoneLayout->setContentsMargins(28, 28, 28, 20);

    QWidget *header = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *logo = new QLabel("FeeL");
    logo->setStyleSheet("font-weight:800; letter-spacing:4px; font-size:20px;");
    headerLayout->addWidget(logo);
    headerLayout->addStretch();
    QFrame *square = new QFrame();
    square->setFixedSize(30, 30);
    square->setStyleSheet("border:2px solid #0b0b0b; border-radius:8px;");
    headerLayout->addWidget(square);
    phoneLayout->addWidget(header);

    // stacked content area to switch between home/friends/profile
    QStackedWidget *contentStack = new QStackedWidget();

    // friend data (avatar resources from resources.qrc)
    auto makeHandle = [](const QString &name) {
        QString h = name.toLower();
        h.replace(" ", "");
        return QStringLiteral("@") + h;
    };

    FriendData myProfile(QStringLiteral("Ho"),
                         makeHandle(QStringLiteral("Ho")),
                         QStringLiteral("Keep it real, share the moment."),
                         QStringLiteral("Followed by 120 friends"),
                         QStringLiteral(":/avatars/avatar7.jpg"),
                         18, 24, 32,
                         QList<QString>({QStringLiteral(":/avatars/avatar7.jpg"), QStringLiteral(":/avatars/avatar6.jpg")}));

    QList<FriendData> friends = {
        FriendData(QStringLiteral("Sakura"), makeHandle(QStringLiteral("Sakura")), QStringLiteral("Loves travel and photography."),
                   QStringLiteral("Followed by 220k people"), QStringLiteral(":/avatars/avatar1.jpg"), 42, 134, 178),
        FriendData(QStringLiteral("Gummy Japan"), makeHandle(QStringLiteral("Gummy Japan")), QStringLiteral("Sweet tooth, sweeter vibes."),
                   QStringLiteral("Followed by 160k people"), QStringLiteral(":/avatars/avatar2.jpg"), 30, 210, 198),
        FriendData(QStringLiteral("Airi Kato"), makeHandle(QStringLiteral("Airi Kato")), QStringLiteral("Cafe hunter & music lover."),
                   QStringLiteral("Followed by 40k people"), QStringLiteral(":/avatars/avatar3.jpg"), 18, 88, 93),
        FriendData(QStringLiteral("Osaki"), makeHandle(QStringLiteral("Osaki")), QStringLiteral("Street snaps and daily life."),
                   QStringLiteral("Followed by 170k people"), QStringLiteral(":/avatars/avatar4.jpg"), 25, 156, 167),
        FriendData(QStringLiteral("MINAMI"), makeHandle(QStringLiteral("MINAMI")), QStringLiteral("Minimal vibes, maximal energy."),
                   QStringLiteral("Followed by 260k people"), QStringLiteral(":/avatars/avatar5.jpg"), 52, 220, 231),
        FriendData(QStringLiteral("Leo"), makeHandle(QStringLiteral("Leo")), QStringLiteral("Runner, reader, ramen."),
                   QStringLiteral("Followed by 15k people"), QStringLiteral(":/avatars/avatar6.jpg"), 9, 54, 61),
        FriendData(QStringLiteral("Mika"), makeHandle(QStringLiteral("Mika")), QStringLiteral("Film photos & calm days."),
                   QStringLiteral("Followed by 32k people"), QStringLiteral(":/avatars/avatar7.jpg"), 16, 102, 110)
    };

    // helper to create a circular avatar pixmap
    auto makeAvatarPixmap = [](const QString &path, int size) -> QPixmap {
        QPixmap src(path);
        if (src.isNull()) return QPixmap();
        QPixmap scaled = src.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPixmap mask(size, size);
        mask.fill(Qt::transparent);
        QPainter painter(&mask);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, size, size);
        scaled.setMask(mask.createMaskFromColor(Qt::transparent));
        QPixmap result(size, size);
        result.fill(Qt::transparent);
        QPainter out(&result);
        out.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath clipPath;
        clipPath.addEllipse(0, 0, size, size);
        out.setClipPath(clipPath);
        out.drawPixmap(0, 0, scaled);
        return result;
    };

    auto showShareSheet = [&](const QString &title, QWidget *parent) {
        QDialog dialog(parent);
        dialog.setModal(true);
        dialog.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        dialog.setAttribute(Qt::WA_TranslucentBackground);
        QVBoxLayout *outer = new QVBoxLayout(&dialog);
        outer->setContentsMargins(24, 24, 24, 24);

        QFrame *sheet = new QFrame();
        sheet->setObjectName("shareSheet");
        sheet->setStyleSheet("#shareSheet { background:#ffffff; border:2px solid #0b0b0b; border-radius:22px; }");
        QVBoxLayout *sheetLayout = new QVBoxLayout(sheet);
        sheetLayout->setSpacing(12);
        sheetLayout->setContentsMargins(18, 18, 18, 18);

        QLabel *titleLbl = new QLabel(title);
        titleLbl->setStyleSheet("font-weight:800; font-size:16px;");
        sheetLayout->addWidget(titleLbl);

        QLabel *subtitle = new QLabel("Send to apps or drop inside friends.");
        subtitle->setStyleSheet("color:#6a6a6a;");
        sheetLayout->addWidget(subtitle);

        QStringList apps = {"Copy link", "Instagram", "Messages", "Save to board"};
        QHBoxLayout *appRow = new QHBoxLayout();
        appRow->setSpacing(8);
        for (const auto &app : apps) {
            QPushButton *chip = new QPushButton(app);
            chip->setStyleSheet("padding:8px 12px; border:1px solid #0b0b0b; border-radius:12px; background:#f7f7f7; font-weight:600;");
            appRow->addWidget(chip);
        }
        appRow->addStretch();
        sheetLayout->addLayout(appRow);

        QLabel *friendsTitle = new QLabel("Friends in FeeL");
        friendsTitle->setStyleSheet("font-weight:700; font-size:14px; margin-top:6px;");
        sheetLayout->addWidget(friendsTitle);

        QVBoxLayout *friendRows = new QVBoxLayout();
        friendRows->setSpacing(8);
        const int friendSample = qMin(4, friends.size());
        for (int i = 0; i < friendSample; ++i) {
            const FriendData &f = friends.at(i);
            QWidget *row = new QWidget();
            QHBoxLayout *rowLayout = new QHBoxLayout(row);
            rowLayout->setContentsMargins(0, 0, 0, 0);
            rowLayout->setSpacing(10);

            QLabel *av = new QLabel();
            av->setFixedSize(36, 36);
            av->setPixmap(makeAvatarPixmap(f.avatar, 36));
            rowLayout->addWidget(av);

            QVBoxLayout *text = new QVBoxLayout();
            text->setContentsMargins(0, 0, 0, 0);
            text->setSpacing(0);
            QLabel *name = new QLabel(f.name);
            name->setStyleSheet("font-weight:700;");
            QLabel *handle = new QLabel(f.handle);
            handle->setStyleSheet("color:#555;");
            text->addWidget(name);
            text->addWidget(handle);
            rowLayout->addLayout(text);
            rowLayout->addStretch();

            QPushButton *send = new QPushButton("Send");
            send->setStyleSheet("padding:6px 12px; border:1px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:600;");
            rowLayout->addWidget(send);
            friendRows->addWidget(row);
        }
        sheetLayout->addLayout(friendRows);

        QPushButton *close = new QPushButton("Close");
        close->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#fdfdfd; font-weight:700;");
        QObject::connect(close, &QPushButton::clicked, &dialog, &QDialog::accept);
        sheetLayout->addWidget(close, 0, Qt::AlignRight);

        outer->addWidget(sheet);
        dialog.exec();
    };

    // profile page (populated on selection)
    QWidget *profilePage = new QWidget();
    QVBoxLayout *profileLayout = new QVBoxLayout(profilePage);
    profileLayout->setContentsMargins(16, 16, 16, 16);
    profileLayout->setSpacing(16);
    QPushButton *backToFriends = new QPushButton("Friends");
    backToFriends->setStyleSheet("padding:8px 16px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
    profileLayout->addWidget(backToFriends, 0, Qt::AlignLeft);

    QLabel *profileAvatar = new QLabel();
    profileAvatar->setFixedSize(160, 160);
    profileAvatar->setAlignment(Qt::AlignCenter);
    profileAvatar->setStyleSheet("background:#d7d7d7; border-radius:80px; border:2px solid #0b0b0b;");
    profileLayout->addWidget(profileAvatar, 0, Qt::AlignHCenter);

    QLabel *profileName = new QLabel("Guest");
    profileName->setStyleSheet("font-size:24px; font-weight:700; color:#0b0b0b;");
    profileLayout->addWidget(profileName, 0, Qt::AlignHCenter);

    QLabel *profileHandle = new QLabel("@guest");
    profileHandle->setStyleSheet("font-size:14px; color:#666;");
    profileLayout->addWidget(profileHandle, 0, Qt::AlignHCenter);

    QLabel *profileFollowStatus = new QLabel();
    profileFollowStatus->setStyleSheet("font-size:13px; color:#444; border:2px solid #0b0b0b; border-radius:12px; padding:6px 10px; background:#ffffff;");
    profileLayout->addWidget(profileFollowStatus, 0, Qt::AlignHCenter);

    QHBoxLayout *statsRow = new QHBoxLayout();
    statsRow->setSpacing(28);
    auto statWidget = [](QLabel **valueLabel, const QString &label) {
        QWidget *w = new QWidget();
        QVBoxLayout *l = new QVBoxLayout(w);
        l->setContentsMargins(0, 0, 0, 0);
        l->setSpacing(2);
        QLabel *v = new QLabel("0");
        *valueLabel = v;
        v->setStyleSheet("font-size:18px; font-weight:700;");
        QLabel *t = new QLabel(label);
        t->setStyleSheet("font-size:12px; color:#444;");
        v->setAlignment(Qt::AlignCenter);
        t->setAlignment(Qt::AlignCenter);
        l->addWidget(v);
        l->addWidget(t);
        return w;
    };
    QLabel *berealValue = nullptr;
    QLabel *friendsValue = nullptr;
    QLabel *followingValue = nullptr;
    QWidget *berealStat = statWidget(&berealValue, "Posts");
    QWidget *friendsStat = statWidget(&friendsValue, "Friends");
    QWidget *followingStat = statWidget(&followingValue, "Following");
    statsRow->addStretch();
    statsRow->addWidget(berealStat);
    statsRow->addWidget(friendsStat);
    statsRow->addWidget(followingStat);
    statsRow->addStretch();
    profileLayout->addLayout(statsRow);

    QPushButton *shareProfile = new QPushButton("Share Profile");
    shareProfile->setStyleSheet("padding:12px 18px; border-radius:18px; background:#2f2f2f; color:#ffffff; font-weight:700;");
    profileLayout->addWidget(shareProfile, 0, Qt::AlignHCenter);
    QObject::connect(shareProfile, &QPushButton::clicked, &window, [&]() {
        showShareSheet(QStringLiteral("Share %1").arg(myProfile.handle), &window);
    });

    // gallery grid
    QWidget *galleryWrap = new QWidget();
    QGridLayout *galleryLayout = new QGridLayout(galleryWrap);
    galleryLayout->setSpacing(10);
    profileLayout->addWidget(galleryWrap);
    profileLayout->addStretch();
    contentStack->addWidget(profilePage);

    auto clearLayout = [](QLayout *layout) {
        if (!layout) return;
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) child->widget()->deleteLater();
            delete child;
        }
    };

    // select friend and populate profile
    auto applyProfile = [&](const FriendData &f) {
        QPixmap avatar = makeAvatarPixmap(f.avatar, 160);
        if (!avatar.isNull()) {
            profileAvatar->setPixmap(avatar);
        } else {
            profileAvatar->setPixmap(QPixmap());
        }
        profileName->setText(f.name);
        profileHandle->setText(f.handle);
        if (f.name == myProfile.name) {
            profileFollowStatus->setText("This is you");
            profileFollowStatus->setVisible(false);
        } else {
            profileFollowStatus->setText("Follow");
            profileFollowStatus->setVisible(true);
        }
        // update stats
        berealValue->setText(QString::number(f.bereals));
        friendsValue->setText(QString::number(f.friends));
        followingValue->setText(QString::number(f.following));
        clearLayout(galleryLayout);
        int col = 0, row = 0;
        const QList<QString> gallery = f.gallery.isEmpty() ? QList<QString>({f.avatar, f.avatar}) : f.gallery;
        for (const QString &img : gallery) {
            QLabel *thumb = new QLabel();
            thumb->setFixedSize(160, 180);
            thumb->setStyleSheet("border-radius:24px; background:#f3f3f3; border:2px solid #0b0b0b;");
            QPixmap pm(img);
            if (!pm.isNull()) {
                thumb->setPixmap(pm.scaled(160, 180, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
            }
            thumb->setAlignment(Qt::AlignCenter);
            galleryLayout->addWidget(thumb, row, col);
            if (++col == 2) { col = 0; ++row; }
        }
    };

    // helper for responsive feed layout resize
    class ResizeWatcher : public QObject {
    public:
        std::function<void()> onResize;
        explicit ResizeWatcher(QObject *parent = nullptr) : QObject(parent) {}
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override {
            if (event->type() == QEvent::Resize && onResize) onResize();
            return QObject::eventFilter(obj, event);
        }
    };

    class PlayTapFilter : public QObject {
    public:
        std::function<void()> onClick;
        explicit PlayTapFilter(QObject *parent = nullptr) : QObject(parent) {}
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override {
            if (event->type() == QEvent::MouseButtonPress) {
                if (onClick) onClick();
            }
            return QObject::eventFilter(obj, event);
        }
    };

    struct FeedCard {
        QWidget *widget = nullptr;
        QMediaPlayer *player = nullptr;
        QVideoWidget *video = nullptr;
        QVBoxLayout *commentsList = nullptr;
        QLineEdit *commentInput = nullptr;
        QToolButton *likeButton = nullptr;
        QLabel *likeCountLabel = nullptr;
        QToolButton *shareButton = nullptr;
        int likeCount = 0;
        bool liked = false;
        TheButtonInfo *info = nullptr;
        FriendData account;
    };

    std::function<void()> refreshFeedGeometry;
    std::function<void(FeedCard&)> openDetailSheet;

    auto updateLikeUI = [&](FeedCard &fc) {
        if (fc.likeButton) {
            fc.likeButton->setChecked(fc.liked);
            fc.likeButton->setIcon(makeHeartIcon(fc.liked, 22));
        }
        if (fc.likeCountLabel) fc.likeCountLabel->setText(QString::number(fc.likeCount));
    };

    // home page cards showing friend accounts as publishers
    auto buildPhoneCard = [&](FeedCard &fc, TheButtonInfo* info, const FriendData &account, bool autoPlay) {
        fc.info = info;
        fc.account = account;
        fc.liked = false;
        fc.likeCount = 120 + account.bereals * 6 + account.friends / 2;

        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background:#ffffff; border:2px solid #101010; border-radius:28px; }");
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setSpacing(12);
        cardLayout->setContentsMargins(18, 18, 18, 18);

        QWidget *mediaSurface = nullptr;
        QMediaPlayer *cardPlayer = nullptr;
        QVideoWidget *cardVideo = nullptr;
        if (info != nullptr) {
            cardVideo = new QVideoWidget(card);
            cardVideo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            cardVideo->setStyleSheet("border:1px solid #101010; border-radius:16px; background:#050505;");
            cardPlayer = new QMediaPlayer(cardVideo);
            QMediaPlaylist *loop = new QMediaPlaylist(cardPlayer);
            loop->addMedia(*info->url);
            loop->setPlaybackMode(QMediaPlaylist::Loop);
            cardPlayer->setPlaylist(loop);
            cardPlayer->setVideoOutput(cardVideo);
            if (autoPlay) {
                cardPlayer->play();
            } else {
                cardPlayer->play();
                cardPlayer->pause();
                cardPlayer->setPosition(0);
            }
            mediaSurface = cardVideo;
        } else {
            QFrame *placeholder = new QFrame();
            placeholder->setMinimumHeight(260);
            placeholder->setStyleSheet("border:1px solid #101010; border-radius:16px; background:#f7f7f7;");
            QLabel *videoText = new QLabel("VIDEOSALV", placeholder);
            videoText->setAlignment(Qt::AlignCenter);
            videoText->setStyleSheet("font-size:18px; letter-spacing:4px; color:#9a9a9a;");
            mediaSurface = placeholder;
        }
        cardLayout->addWidget(mediaSurface);
        cardLayout->setAlignment(mediaSurface, Qt::AlignCenter);

        auto goProfile = [=, &contentStack, &applyProfile]() {
            applyProfile(account);
            contentStack->setCurrentWidget(profilePage);
        };

        QHBoxLayout *profileRow = new QHBoxLayout();
        profileRow->setSpacing(10);
        QPushButton *avatarBtn = new QPushButton();
        avatarBtn->setFixedSize(44, 44);
        avatarBtn->setIconSize(QSize(44, 44));
        avatarBtn->setFlat(true);
        QPixmap avatar = makeAvatarPixmap(account.avatar, 44);
        if (!avatar.isNull()) {
            avatarBtn->setIcon(QIcon(avatar));
        }
        avatarBtn->setStyleSheet("border:1px solid #101010; border-radius:22px; background:#fdfdfd;");
        QObject::connect(avatarBtn, &QPushButton::clicked, &window, goProfile);

        QVBoxLayout *profileText = new QVBoxLayout();
        profileText->setContentsMargins(0, 0, 0, 0);
        profileText->setSpacing(0);
        QPushButton *nameBtn = new QPushButton(account.name);
        nameBtn->setFlat(true);
        nameBtn->setStyleSheet("text-align:left; font-weight:700; font-size:15px; color:#0b0b0b;");
        QObject::connect(nameBtn, &QPushButton::clicked, &window, goProfile);
        profileText->addWidget(nameBtn);
        QPushButton *handleBtn = new QPushButton(account.handle);
        handleBtn->setFlat(true);
        handleBtn->setStyleSheet("text-align:left; font-size:13px; color:#5a5a5a;");
        QObject::connect(handleBtn, &QPushButton::clicked, &window, goProfile);
        profileText->addWidget(handleBtn);
        QPushButton *followButton = new QPushButton("FOLLOW");
        followButton->setStyleSheet("QPushButton { border:1px solid #101010; border-radius:16px; padding:4px 16px; background:#ffffff; font-weight:600; }");
        profileRow->addWidget(avatarBtn);
        profileRow->addLayout(profileText);
        profileRow->addStretch();
        profileRow->addWidget(followButton);
        cardLayout->addLayout(profileRow);

        QHBoxLayout *statsRow = new QHBoxLayout();
        statsRow->setSpacing(10);
        QToolButton *likeBtn = new QToolButton();
        likeBtn->setCheckable(true);
        likeBtn->setAutoRaise(true);
        likeBtn->setIcon(makeHeartIcon(false, 22));
        likeBtn->setStyleSheet("QToolButton { border:none; padding:6px; }");
        QLabel *likeCount = new QLabel(QString::number(fc.likeCount));
        likeCount->setStyleSheet("font-weight:700; color:#0b0b0b;");
        statsRow->addWidget(likeBtn);
        statsRow->addWidget(likeCount);
        statsRow->addStretch();
        QToolButton *shareBtn = new QToolButton();
        shareBtn->setText("Share");
        shareBtn->setStyleSheet("QToolButton { padding:8px 14px; border:1px solid #101010; border-radius:14px; background:#ffffff; font-weight:700; }");
        statsRow->addWidget(shareBtn);
        cardLayout->addLayout(statsRow);

        QVBoxLayout *commentSection = new QVBoxLayout();
        commentSection->setSpacing(6);
        QLabel *commentLabel = new QLabel("Comments");
        commentLabel->setStyleSheet("font-weight:700; color:#0b0b0b;");
        commentSection->addWidget(commentLabel);

        QVBoxLayout *commentsList = new QVBoxLayout();
        commentsList->setContentsMargins(0, 0, 0, 0);
        commentsList->setSpacing(10);
        commentSection->addLayout(commentsList);

        QLineEdit *commentInput = new QLineEdit();
        commentInput->setPlaceholderText("Add a comment...");
        commentInput->setStyleSheet("padding:10px 12px; border:0; border-radius:14px; background:#f5f5f5;");
        commentSection->addWidget(commentInput);

        auto addComment = [=, &fc]() {
            const QString text = commentInput->text().trimmed();
            if (text.isEmpty())
                return;
            QHBoxLayout *row = new QHBoxLayout();
            row->setSpacing(8);

            QLabel *avatarLbl = new QLabel();
            avatarLbl->setFixedSize(28, 28);
            QPixmap myAvatar = makeAvatarPixmap(myProfile.avatar, 28);
            if (!myAvatar.isNull()) {
                avatarLbl->setPixmap(myAvatar);
            }
            avatarLbl->setStyleSheet("border-radius:14px;");
            row->addWidget(avatarLbl);

            QVBoxLayout *textCol = new QVBoxLayout();
            textCol->setContentsMargins(0, 0, 0, 0);
            textCol->setSpacing(2);
            QLabel *nameLbl = new QLabel(myProfile.name);
            nameLbl->setStyleSheet("font-weight:700; font-size:13px;");
            QLabel *bodyLbl = new QLabel(text);
            bodyLbl->setStyleSheet("font-size:12px; color:#0b0b0b;");
            bodyLbl->setWordWrap(true);
            textCol->addWidget(nameLbl);
            textCol->addWidget(bodyLbl);
            row->addLayout(textCol);

            QWidget *rowWrap = new QWidget();
            rowWrap->setLayout(row);
            commentsList->addWidget(rowWrap);
            commentInput->clear();
            if (refreshFeedGeometry) refreshFeedGeometry();
        };
        QObject::connect(commentInput, &QLineEdit::returnPressed, &window, addComment);

        cardLayout->addLayout(commentSection);

        QObject::connect(likeBtn, &QToolButton::clicked, &window, [&, likeBtn, likeCount]() {
            fc.liked = likeBtn->isChecked();
            fc.likeCount += fc.liked ? 1 : (fc.likeCount > 0 ? -1 : 0);
            updateLikeUI(fc);
            likeCount->setText(QString::number(fc.likeCount));
        });

        QObject::connect(shareBtn, &QToolButton::clicked, &window, [&, account]() {
            showShareSheet(QStringLiteral("Share %1").arg(account.handle), &window);
        });

        PlayTapFilter *cardTap = new PlayTapFilter(card);
        cardTap->onClick = [&]() {
            if (openDetailSheet) openDetailSheet(fc);
        };
        card->installEventFilter(cardTap);
        if (mediaSurface) {
            PlayTapFilter *mediaTap = new PlayTapFilter(mediaSurface);
            mediaTap->onClick = cardTap->onClick;
            mediaSurface->installEventFilter(mediaTap);
        }

        fc.widget = card;
        fc.player = cardPlayer;
        fc.video = cardVideo;
        fc.commentsList = commentsList;
        fc.commentInput = commentInput;
        fc.likeButton = likeBtn;
        fc.likeCountLabel = likeCount;
        fc.shareButton = shareBtn;
        updateLikeUI(fc);
    };

    openDetailSheet = [&](FeedCard &fc) {
        // overlay that stays inside the phone frame
        QWidget *overlay = new QWidget(phone);
        overlay->setObjectName("detailOverlay");
        overlay->setStyleSheet("#detailOverlay { background: rgba(0,0,0,120); }");
        overlay->setGeometry(phone->rect());
        overlay->raise();
        overlay->show();

        auto computeCardSize = [&]() {
            const int margin = 16;
            int w = static_cast<int>(phone->width() * 0.92);
            int h = static_cast<int>(phone->height() * 0.9);
            w = qBound(260, w, phone->width() - margin * 2);
            h = qBound(340, h, phone->height() - margin * 2);
            return QSize(w, h);
        };
        QSize cardSize = computeCardSize();

        QVBoxLayout *outer = new QVBoxLayout(overlay);
        outer->setContentsMargins(10, 10, 10, 10);

        QScrollArea *scroll = new QScrollArea(overlay);
        scroll->setFrameShape(QFrame::NoFrame);
        scroll->setWidgetResizable(true);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        outer->addWidget(scroll, 1);

        QWidget *scrollWrap = new QWidget();
        scrollWrap->setStyleSheet("background: transparent;");
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWrap);
        scrollLayout->setContentsMargins(0, 0, 0, 0);
        scrollLayout->setAlignment(Qt::AlignHCenter);

        QFrame *panel = new QFrame();
        panel->setObjectName("detailPanel");
        panel->setStyleSheet("#detailPanel { background:#ffffff; border:2px solid #0b0b0b; border-radius:24px; }");
        panel->setMinimumSize(cardSize);
        panel->setMaximumSize(cardSize);
        panel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        QVBoxLayout *panelLayout = new QVBoxLayout(panel);
        panelLayout->setSpacing(12);
        panelLayout->setContentsMargins(16, 16, 16, 16);
        scrollLayout->addWidget(panel, 0, Qt::AlignHCenter);
        scrollLayout->addStretch();
        scroll->setWidget(scrollWrap);

        QWidget *videoWrap = nullptr;
        QMediaPlayer *modalPlayer = nullptr;
        const int videoHeight = qMax(180, static_cast<int>(cardSize.height() * 0.45));
        if (fc.info != nullptr) {
            QVideoWidget *modalVideo = new QVideoWidget(panel);
            modalVideo->setMinimumHeight(videoHeight);
            modalVideo->setMaximumHeight(videoHeight + 40);
            modalVideo->setStyleSheet("border:1px solid #0b0b0b; border-radius:14px; background:#050505;");
            modalPlayer = new QMediaPlayer(modalVideo);
            QMediaPlaylist *loop = new QMediaPlaylist(modalPlayer);
            loop->addMedia(*fc.info->url);
            loop->setPlaybackMode(QMediaPlaylist::Loop);
            modalPlayer->setPlaylist(loop);
            modalPlayer->setVideoOutput(modalVideo);
            modalPlayer->play();
            videoWrap = modalVideo;
        } else {
            QFrame *ph = new QFrame();
            ph->setMinimumHeight(videoHeight);
            ph->setStyleSheet("border:1px solid #0b0b0b; border-radius:14px; background:#f5f5f5;");
            QLabel *txt = new QLabel("No video", ph);
            txt->setAlignment(Qt::AlignCenter);
            txt->setStyleSheet("color:#7a7a7a; font-weight:700;");
            videoWrap = ph;
        }
        panelLayout->addWidget(videoWrap);

        QHBoxLayout *userRow = new QHBoxLayout();
        userRow->setSpacing(10);
        QLabel *avatar = new QLabel();
        avatar->setFixedSize(48, 48);
        avatar->setPixmap(makeAvatarPixmap(fc.account.avatar, 48));
        userRow->addWidget(avatar);
        QVBoxLayout *userText = new QVBoxLayout();
        userText->setContentsMargins(0, 0, 0, 0);
        userText->setSpacing(0);
        QLabel *name = new QLabel(fc.account.name);
        name->setStyleSheet("font-weight:800; font-size:16px;");
        QLabel *handle = new QLabel(fc.account.handle);
        handle->setStyleSheet("color:#555;");
        userText->addWidget(name);
        userText->addWidget(handle);
        userRow->addLayout(userText);
        userRow->addStretch();
        panelLayout->addLayout(userRow);

        QHBoxLayout *actionRow = new QHBoxLayout();
        actionRow->setSpacing(12);
        QToolButton *likeBtn = new QToolButton();
        likeBtn->setCheckable(true);
        likeBtn->setChecked(fc.liked);
        likeBtn->setIcon(makeHeartIcon(fc.liked, 22));
        likeBtn->setStyleSheet("QToolButton { border:none; padding:8px; }");
        QLabel *likeCount = new QLabel(QString::number(fc.likeCount));
        likeCount->setStyleSheet("font-weight:700;");
        actionRow->addWidget(likeBtn);
        actionRow->addWidget(likeCount);
        actionRow->addStretch();
        QToolButton *shareBtn = new QToolButton();
        shareBtn->setText("Share");
        shareBtn->setStyleSheet("QToolButton { padding:8px 14px; border:1px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:700; }");
        actionRow->addWidget(shareBtn);
        panelLayout->addLayout(actionRow);

        QObject::connect(likeBtn, &QToolButton::clicked, overlay, [&, likeBtn, likeCount]() {
            fc.liked = likeBtn->isChecked();
            fc.likeCount += fc.liked ? 1 : (fc.likeCount > 0 ? -1 : 0);
            updateLikeUI(fc);
            likeBtn->setIcon(makeHeartIcon(fc.liked, 22));
            likeCount->setText(QString::number(fc.likeCount));
        });

        QObject::connect(shareBtn, &QToolButton::clicked, overlay, [&]() {
            showShareSheet(QStringLiteral("Share %1").arg(fc.account.handle), overlay);
        });

        QLabel *chatTitle = new QLabel("Live chat");
        chatTitle->setStyleSheet("font-weight:800; font-size:14px;");
        panelLayout->addWidget(chatTitle);

        QVBoxLayout *chatList = new QVBoxLayout();
        chatList->setSpacing(10);
        QStringList sampleTexts = {
            "This angle looks fire.",
            "Where was this shot?",
            "Drop the playlist please.",
            "I need this energy today."
        };
        int chatCount = qMin(4, friends.size());
        for (int i = 0; i < chatCount; ++i) {
            const FriendData &chatter = friends.at(i);
            QWidget *row = new QWidget();
            QHBoxLayout *rowLayout = new QHBoxLayout(row);
            rowLayout->setContentsMargins(0, 0, 0, 0);
            rowLayout->setSpacing(10);
            QLabel *av = new QLabel();
            av->setFixedSize(30, 30);
            av->setPixmap(makeAvatarPixmap(chatter.avatar, 30));
            rowLayout->addWidget(av);
            QVBoxLayout *txt = new QVBoxLayout();
            txt->setContentsMargins(0, 0, 0, 0);
            txt->setSpacing(0);
            QLabel *nm = new QLabel(chatter.name);
            nm->setStyleSheet("font-weight:700;");
            QLabel *body = new QLabel(sampleTexts.at(i % sampleTexts.size()));
            body->setWordWrap(true);
            body->setStyleSheet("color:#333;");
            txt->addWidget(nm);
            txt->addWidget(body);
            rowLayout->addLayout(txt);
            chatList->addWidget(row);
        }
        panelLayout->addLayout(chatList);

        QPushButton *close = new QPushButton("Close");
        close->setStyleSheet("padding:10px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#fdfdfd; font-weight:700;");
        panelLayout->addWidget(close, 0, Qt::AlignRight);

        outer->setAlignment(scroll, Qt::AlignCenter);

        // keep overlay sized with phone
        ResizeWatcher *overlayWatcher = new ResizeWatcher(overlay);
        overlayWatcher->onResize = [=]() mutable {
            overlay->setGeometry(phone->rect());
            QSize newSize = computeCardSize();
            panel->setMinimumSize(newSize);
            panel->setMaximumSize(newSize);
        };
        phone->installEventFilter(overlayWatcher);

        // close handlers
        auto closeOverlay = [overlay, modalPlayer]() {
            if (modalPlayer) modalPlayer->stop();
            overlay->deleteLater();
        };
        QObject::connect(close, &QPushButton::clicked, overlay, closeOverlay);
        PlayTapFilter *overlayTap = new PlayTapFilter(overlay);
        overlayTap->onClick = closeOverlay;
        overlay->installEventFilter(overlayTap);
    };

    // home page (video feed with friend accounts)
    QWidget *homePage = new QWidget();
    QVBoxLayout *homeLayout = new QVBoxLayout(homePage);
    homeLayout->setContentsMargins(0, 0, 0, 0);
    QScrollArea *feedArea = new QScrollArea();
    feedArea->setFrameShape(QFrame::NoFrame);
    feedArea->setWidgetResizable(true);
    QWidget *feedContent = new QWidget();
    feedContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QGridLayout *feedLayout = new QGridLayout(feedContent);
    feedLayout->setSpacing(18);
    feedLayout->setContentsMargins(0, 0, 0, 0);
    QVector<FeedCard> feedCards;
    feedCards.reserve(static_cast<int>(videos.size()) + 1);
    auto addCard = [&](TheButtonInfo *info, const FriendData &publisher, bool autoPlay) {
        feedCards.append(FeedCard());
        buildPhoneCard(feedCards.last(), info, publisher, autoPlay);
    };
    if (videos.size() > 0) {
        for (size_t i = 0; i < videos.size(); ++i) {
            const FriendData &publisher = friends.isEmpty() ? myProfile : friends.at(i % friends.size());
            bool autoPlay = (i == 0);
            addCard(&videos.at(i), publisher, autoPlay);
        }
    } else {
        addCard(nullptr, myProfile, true);
    }

    auto clearGrid = [](QGridLayout *layout) {
        if (!layout) return;
        while (layout->count() > 0) {
            QLayoutItem *item = layout->takeAt(0);
            if (item->widget()) {
                layout->removeWidget(item->widget());
            }
            delete item;
        }
    };

    refreshFeedGeometry = [&]() {
        feedLayout->activate();
        feedContent->setMinimumHeight(feedLayout->sizeHint().height());
        feedContent->adjustSize();
        feedArea->updateGeometry();
    };

    int lastColumns = -1;
    int lastWidth = -1;

    std::function<void()> rebuildFeed = [&]() {
        clearGrid(feedLayout);
        int viewportWidth = feedArea->viewport()->width();
        int columns = 1;
        if (viewportWidth > 980) columns = 3;
        else if (viewportWidth > 640) columns = 2;

        if (columns == lastColumns && lastWidth >= 0 && std::abs(viewportWidth - lastWidth) < 32) {
            return;
        }
        lastColumns = columns;
        lastWidth = viewportWidth;

        const int spacing = feedLayout->horizontalSpacing();
        const int margins = feedLayout->contentsMargins().left() + feedLayout->contentsMargins().right();
        int cardWidth = (viewportWidth - spacing * (columns - 1) - margins) / columns;
        if (cardWidth < 200) cardWidth = 200;
        int targetVideoHeight = static_cast<int>(cardWidth * 9.0 / 16.0);

        for (int i = 0; i < feedCards.size(); ++i) {
            int row = i / columns;
            int col = i % columns;
            FeedCard &fc = feedCards[i];
            if (fc.widget) {
                fc.widget->setMinimumWidth(cardWidth);
                fc.widget->setMaximumWidth(QWIDGETSIZE_MAX);
                fc.widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            }
            if (fc.video) {
                fc.video->setMaximumHeight(targetVideoHeight);
                fc.video->setMinimumHeight(qMax(160, targetVideoHeight - 120));
                fc.video->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            }
            feedLayout->addWidget(fc.widget, row, col, Qt::AlignCenter);
        }
        for (int c = 0; c < columns; ++c) {
            feedLayout->setColumnStretch(c, 1);
        }
        feedLayout->setRowStretch(feedLayout->rowCount(), 1);
        feedContent->setMinimumHeight(feedLayout->sizeHint().height());
        feedContent->adjustSize();
    };

    ResizeWatcher *feedWatcher = new ResizeWatcher(feedArea);
    feedWatcher->onResize = rebuildFeed;
    feedArea->viewport()->installEventFilter(feedWatcher);
    rebuildFeed();

    feedArea->setWidget(feedContent);
    homeLayout->addWidget(feedArea);
    contentStack->addWidget(homePage);

    // friends page with cards
    QWidget *friendsPage = new QWidget();
    QVBoxLayout *friendsLayout = new QVBoxLayout(friendsPage);
    friendsLayout->setContentsMargins(12, 12, 12, 12);
    friendsLayout->setSpacing(12);
    QScrollArea *friendsArea = new QScrollArea();
    friendsArea->setFrameShape(QFrame::NoFrame);
    friendsArea->setWidgetResizable(true);
    QWidget *friendsListWrap = new QWidget();
    QVBoxLayout *friendsListLayout = new QVBoxLayout(friendsListWrap);
    friendsListLayout->setContentsMargins(0, 0, 0, 0);
    friendsListLayout->setSpacing(10);

    QLineEdit *search = new QLineEdit();
    search->setPlaceholderText("Add or search friends");
    search->setStyleSheet("padding:10px 12px; border:2px solid #101010; border-radius:16px; background:#f2f2f2;");

    // static headers and containers
    QLabel *friendsTitle = new QLabel("Friends");
    friendsTitle->setStyleSheet("font-size:18px; font-weight:700;");
    QWidget *friendsCardsWrap = new QWidget();
    QVBoxLayout *friendsCardsLayout = new QVBoxLayout(friendsCardsWrap);
    friendsCardsLayout->setContentsMargins(0, 0, 0, 0);
    friendsCardsLayout->setSpacing(10);

    QLabel *popularTitle = new QLabel("Recommend Accounts");
    popularTitle->setStyleSheet("font-size:18px; font-weight:700;");
    QWidget *popularCardsWrap = new QWidget();
    QVBoxLayout *popularCardsLayout = new QVBoxLayout(popularCardsWrap);
    popularCardsLayout->setContentsMargins(0, 0, 0, 0);
    popularCardsLayout->setSpacing(10);

    friendsListLayout->addWidget(search);
    friendsListLayout->addWidget(friendsTitle);
    friendsListLayout->addWidget(friendsCardsWrap);
    friendsListLayout->addWidget(popularTitle);
    friendsListLayout->addWidget(popularCardsWrap);
    friendsListLayout->addStretch();

    // helpers
    auto clearLayoutWithWidgets = [](QLayout *layout) {
        if (!layout) return;
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) child->widget()->deleteLater();
            delete child;
        }
    };

    QList<FriendData> friendSubset = friends.mid(0, 3);
    QList<FriendData> popularSubset = friends.mid(3); // disjoint from friends
    ChatWindow *chatPage = new ChatWindow();
    chatPage->setThreads(friendSubset);
    QObject::connect(chatPage, &ChatWindow::showProfile, &window, [=](const FriendData &f) {
        applyProfile(f);
        contentStack->setCurrentWidget(profilePage);
    });

    auto renderCards = [&](const QList<FriendData> &list, QVBoxLayout *targetLayout, const QString &filter, bool isFriendList) {
        clearLayoutWithWidgets(targetLayout);
        const bool hasFilter = !filter.trimmed().isEmpty();
        int added = 0;
        int idxCounter = 0;
        for (const auto &f : list) {
            if (hasFilter) {
                const QString text = filter.trimmed();
                if (!f.name.contains(text, Qt::CaseInsensitive) &&
                    !f.handle.contains(text, Qt::CaseInsensitive)) {
                    continue;
                }
            }
            ++added;
            int idx = idxCounter++;
            QFrame *card = new QFrame();
            card->setStyleSheet("QFrame { background:#ffffff; border:2px solid #0b0b0b; border-radius:18px; }");
            QHBoxLayout *cardLayout = new QHBoxLayout(card);
            cardLayout->setContentsMargins(12, 10, 12, 10);
            cardLayout->setSpacing(12);

            QPushButton *avatarBtn = new QPushButton();
            avatarBtn->setFixedSize(56, 56);
            avatarBtn->setIconSize(QSize(56, 56));
            avatarBtn->setFlat(true);
            QPixmap avatar = makeAvatarPixmap(f.avatar, 56);
            if (!avatar.isNull()) {
                avatarBtn->setIcon(QIcon(avatar));
            }
            avatarBtn->setStyleSheet("border:2px solid #0b0b0b; border-radius:28px; background:#fdfdfd;");
            cardLayout->addWidget(avatarBtn);

            QVBoxLayout *infoColumn = new QVBoxLayout();
            infoColumn->setContentsMargins(0, 0, 0, 0);
            infoColumn->setSpacing(0);
            QPushButton *nameBtn = new QPushButton(f.name);
            nameBtn->setFlat(true);
            nameBtn->setStyleSheet("text-align:left; font-weight:700; font-size:16px; color:#0b0b0b;");
            infoColumn->addWidget(nameBtn);
            QLabel *handleLbl = new QLabel(f.handle);
            handleLbl->setStyleSheet("font-size:13px; color:#5a5a5a;");
            infoColumn->addWidget(handleLbl);
            QLabel *followersLbl = new QLabel(QStringLiteral("Followed by %1 people").arg(f.followers));
            followersLbl->setStyleSheet("font-size:12px; color:#7a7a7a;");
            infoColumn->addWidget(followersLbl);
            cardLayout->addLayout(infoColumn);
            cardLayout->addStretch();

            QPushButton *followBtn = new QPushButton(isFriendList ? "Followed" : "Follow");
            followBtn->setStyleSheet("padding:6px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
            if (isFriendList) {
                followBtn->setEnabled(false);
                followBtn->setStyleSheet("padding:6px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#e9e9e9; font-weight:600; color:#5a5a5a;");
            }
            cardLayout->addWidget(followBtn);
            if (isFriendList) {
                QPushButton *chatBtn = new QPushButton("Chat");
                chatBtn->setStyleSheet("padding:6px 12px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
                cardLayout->addWidget(chatBtn);
                QObject::connect(chatBtn, &QPushButton::clicked, &window, [=]() {
                    chatPage->openThreadByIndex(idx);
                    contentStack->setCurrentWidget(chatPage);
                });
            }

            targetLayout->addWidget(card);

            auto goProfile = [=, &contentStack, &applyProfile]() {
                applyProfile(f);
                contentStack->setCurrentWidget(profilePage);
            };
            QObject::connect(avatarBtn, &QPushButton::clicked, &window, goProfile);
            QObject::connect(nameBtn, &QPushButton::clicked, &window, goProfile);
        }
        if (added == 0) {
            QLabel *empty = new QLabel("No results");
            empty->setStyleSheet("color:#7a7a7a;");
            targetLayout->addWidget(empty);
        }
    };

    std::function<void(const QString&)> rebuildFriendsList = [&](const QString &filter) {
        renderCards(friendSubset, friendsCardsLayout, filter, true);
        renderCards(popularSubset, popularCardsLayout, filter, false);
    };

    rebuildFriendsList(QString());
    friendsArea->setWidget(friendsListWrap);
    friendsLayout->addWidget(friendsArea);
    contentStack->addWidget(friendsPage);
    contentStack->addWidget(chatPage);

    QObject::connect(search, &QLineEdit::textChanged, &window, rebuildFriendsList);

    // default profile content shows self
    applyProfile(myProfile);
    phoneLayout->addWidget(contentStack);

    QWidget *navBar = new QWidget();
    QHBoxLayout *navLayout = new QHBoxLayout(navBar);
    navLayout->setSpacing(18);
    navLayout->setContentsMargins(0, 0, 0, 0);
    QStringList navItems = {"HOME", "FRIENDS", "POST", "CHAT", "PROFILE"};
    for (const QString &item : navItems) {
        QPushButton *navButton = new QPushButton(item);
        navButton->setFlat(true);
        navButton->setStyleSheet("QPushButton { border: none; font-weight:600; color:#5f5f5f; }");
        navLayout->addWidget(navButton);

        if (item == "FRIENDS") {
            QObject::connect(navButton, &QPushButton::clicked, &window, [=]() {
                contentStack->setCurrentWidget(friendsPage);
            });
        } else if (item == "CHAT") {
            QObject::connect(navButton, &QPushButton::clicked, &window, [=]() {
                contentStack->setCurrentWidget(chatPage);
            });
        } else if (item == "PROFILE") {
            QObject::connect(navButton, &QPushButton::clicked, &window, [=]() {
                applyProfile(myProfile);
                contentStack->setCurrentWidget(profilePage);
            });
        } else if (item == "HOME") {
            QObject::connect(navButton, &QPushButton::clicked, &window, [=]() {
                contentStack->setCurrentWidget(homePage);
            });
        }
    }

    // back from profile to friends
    QObject::connect(backToFriends, &QPushButton::clicked, &window, [=]() {
        contentStack->setCurrentWidget(friendsPage);
    });

    // default page
    contentStack->setCurrentWidget(homePage);
    phoneLayout->addWidget(navBar);

    root->addWidget(phone);
    root->addStretch();

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
