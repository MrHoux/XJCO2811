#include "settingwindow.h"
#include <QMessageBox>
#include <QFrame>
#include <QStyle>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>
#include <functional>
#include <QToolButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

extern QString translate(const QString& text);

SettingWindow::SettingWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void animateButton(QWidget *button) {
    QPropertyAnimation *scaleX = new QPropertyAnimation(button, "scale");
    scaleX->setDuration(200);
    scaleX->setKeyValueAt(0, 1.0);
    scaleX->setKeyValueAt(0.5, 0.95);
    scaleX->setKeyValueAt(1, 1.0);

    QPropertyAnimation *opacity = new QPropertyAnimation(button, "windowOpacity");
    opacity->setDuration(200);
    opacity->setKeyValueAt(0, 1.0);
    opacity->setKeyValueAt(0.5, 0.8);
    opacity->setKeyValueAt(1, 1.0);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(scaleX);
    group->addAnimation(opacity);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void SettingWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);

    QWidget *header = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    header->setStyleSheet(
        "background-color: #ffffff;"
        "border-bottom: 1px solid #e0e0e0;"
        );

    QPushButton *backBtn = new QPushButton(QStringLiteral("‹"));
    backBtn->setFixedSize(46, 38);
    backBtn->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    font-size: 22px;"
        "    color: #333;"
        "    background: transparent;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    color: #007aff;"
        "}"
        );

    QLabel *title = new QLabel(translate("Settings"));
    title->setStyleSheet(
        "font-size: 18px;"
        "font-weight: bold;"
        "color: #1a1a1a;"
        );

    headerLayout->addWidget(backBtn);
    headerLayout->addStretch();
    headerLayout->addWidget(title);
    headerLayout->addStretch();
    mainLayout->addWidget(header);


    connect(backBtn, &QPushButton::clicked, this, &SettingWindow::backToHome);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(4, 4, 4, 4);
    contentLayout->setSpacing(12);

    auto makeSectionCard = [](const QString &sectionTitle) {
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background:#ffffff; border-radius:20px; }");
        QVBoxLayout *layout = new QVBoxLayout(card);
        layout->setContentsMargins(14, 12, 14, 14);
        layout->setSpacing(10);
        QLabel *label = new QLabel(sectionTitle);
        label->setStyleSheet("font-weight:800; font-size:13px; letter-spacing:1px; color:#0b0b0b;");
        layout->addWidget(label);
        return std::make_pair(card, layout);
    };

    auto addRow = [this](QVBoxLayout *layout, const QString &text, const QString &subtitle, const std::function<void()> &onClick) {
        QPushButton *btn = new QPushButton();
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet("QPushButton { text-align:left; padding:10px 12px; border:2px solid #0b0b0b; border-radius:14px; background:transparent; }"
                           "QPushButton:hover { background:#f2f2f2; }");
        QHBoxLayout *row = new QHBoxLayout(btn);
        row->setContentsMargins(4, 2, 4, 2);
        row->setSpacing(8);

        QVBoxLayout *txtCol = new QVBoxLayout();
        txtCol->setContentsMargins(0, 0, 0, 0);
        txtCol->setSpacing(2);
        QLabel *titleLbl = new QLabel(text);
        titleLbl->setStyleSheet("font-weight:800; color:#0b0b0b;");
        txtCol->addWidget(titleLbl);
        row->addLayout(txtCol);
        if (onClick) QObject::connect(btn, &QPushButton::clicked, this, onClick);
        layout->addWidget(btn);
    };

    QFrame *userCard = new QFrame();
    userCard->setStyleSheet(
        "QFrame {"
        "    background: #ffffff;"
        "    border: none;"
        "    border-radius: 0px;"
        "}"
        );
    QHBoxLayout *userLayout = new QHBoxLayout(userCard);
    userLayout->setContentsMargins(16, 14, 16, 14);
    userLayout->setSpacing(12);

    m_avatarLabel = new QLabel();
    m_avatarLabel->setFixedSize(72, 72);
    m_avatarLabel->setAlignment(Qt::AlignCenter);
    m_avatarLabel->setScaledContents(true);
    m_avatarLabel->setStyleSheet(
        "border-radius: 30px;"
        "border: none;"
        "background: #f4f4f4;"
        "color: #0b0b0b;"
        "font-size: 20px;"
        "font-weight: bold;"
        );

    QVBoxLayout *userInfo = new QVBoxLayout();
    userInfo->setContentsMargins(0, 0, 0, 0);
    userInfo->setSpacing(4);
    m_nameLabel = new QLabel(translate("Guest"));
    m_nameLabel->setStyleSheet(
        "font-size: 18px;"
        "font-weight: bold;"
        "color: #0b0b0b;"
        );
    m_handleLabel = new QLabel("@guest");
    m_handleLabel->setStyleSheet(
        "color: #0b0b0b;"
        "font-size: 13px;"
        );
    userInfo->addWidget(m_nameLabel);
    userInfo->addWidget(m_handleLabel);

    QPushButton *shareBtn = new QPushButton(translate("Share Profile"));
    shareBtn->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:14px; background:transparent; font-weight:700;");
    QObject::connect(shareBtn, &QPushButton::clicked, this, [this]() {
        emit shareProfileRequested();
    });

    userLayout->addWidget(m_avatarLabel);
    userLayout->addLayout(userInfo);
    userLayout->addStretch();
    userLayout->addWidget(shareBtn);
    contentLayout->addWidget(userCard);

    auto features = makeSectionCard(translate("FEATURES"));
    addRow(features.second, translate("Audio"), translate("Playback, volume & mute"), [this]() {
        emit openDetail(translate("Audio"), translate("Audio"));
    });
    contentLayout->addWidget(features.first);

    auto settings = makeSectionCard(translate("SETTINGS"));
    addRow(settings.second, translate("Notifications"), translate("Push, sound, vibrate"), [this]() {
        emit openDetail(translate("Notifications"), translate("Notifications"));
    });
    addRow(settings.second, translate("Privacy"), translate("Visibility & account safety"), [this]() {
        emit openDetail(translate("Privacy"), translate("Privacy"));
    });
    addRow(settings.second, translate("Time Zone"), translate("Local time & auto-detect"), [this]() {
        emit openDetail(translate("Time Zone"), translate("Time Zone"));
    });
    addRow(settings.second, translate("Other"), translate("Language, cache & data"), [this]() {
        emit openDetail(translate("Other"), translate("Other"));
    });
    contentLayout->addWidget(settings.first);

    auto about = makeSectionCard(translate("ABOUT"));
    addRow(about.second, translate("Share FeeL"), translate("Invite friends with a quick link"), [this]() {
        emit openDetail(translate("Share FeeL"), translate("Share FeeL"));
    });
    addRow(about.second, translate("Rate FeeL"), translate("Leave a review to support us"), [this]() {
        emit openDetail(translate("Rate FeeL"), translate("Rate FeeL"));
    });
    addRow(about.second, translate("Help"), translate("FAQ and contact support"), [this]() {
        emit openDetail(translate("Help"), translate("Help"));
    });
    addRow(about.second, translate("About"), translate("Version, build and story"), [this]() {
        emit openDetail(translate("About"), translate("About"));
    });
    contentLayout->addWidget(about.first);

    QPushButton *logoutBtn = new QPushButton(translate("Log Out"));
    logoutBtn->setStyleSheet(
        "QPushButton {"
        "    padding: 16px;"
        "    font-size: 16px;"
        "    font-weight: 600;"
        "    color: white;"
        "    background-color: #ff4757;"
        "    border: none;"
        "    border-radius: 12px;"
        "    margin-top: 30px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #ff3742;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #ff2e3d;"
        "}"
        );
    QObject::connect(logoutBtn, &QPushButton::clicked, []() {
        QMessageBox msgBox;
        msgBox.setWindowTitle(translate("Log Out"));
        msgBox.setText(translate("Are you sure you want to log out?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::Yes) {
            QMessageBox::information(nullptr, translate("Logged Out"), translate("You have been successfully logged out."));
        }
    });
    contentLayout->addWidget(logoutBtn);

    contentLayout->addStretch();
    scrollArea->setWidget(content);
    mainLayout->addWidget(scrollArea);



    QLabel *featuresTitle = new QLabel(this);

    featuresTitle->setStyleSheet(
        "color: #8e8e93;"
        "font-weight: 600;"
        "font-size: 13px;"
        "margin-top: 10px;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        );

    auto createStyledButton = [](const QString& text) {
        QToolButton *btn = new QToolButton();
        btn->setText(text);
        btn->setStyleSheet(
            "QToolButton {"
            "    text-align: left;"
            "    padding: 16px 20px;"
            "    font-size: 16px;"
            "    font-weight: 500;"
            "    color: #1a1a1a;"
            "    background: white;"
            "    border: none;"
            "    border-radius: 12px;"
            "    margin: 5px 0;"
            "}"
            "QToolButton:hover {"
            "    background: #f5f5f7;"
            "    transform: translateY(-1px);"
            "}"
            "QToolButton:pressed {"
            "    background: #e5e5ea;"
            "}"
            );
        QLabel *arrow = new QLabel("›", btn);
        arrow->setStyleSheet(
            "color: #c7c7cc;"
            "font-size: 24px;"
            "font-weight: bold;"
            );
        arrow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        QHBoxLayout *btnLayout = new QHBoxLayout(btn);
        btnLayout->setContentsMargins(0, 0, 10, 0);
        btnLayout->addStretch();
        btnLayout->addWidget(arrow);

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(15);
        shadow->setColor(QColor(0, 0, 0, 20));
        shadow->setOffset(0, 2);
        btn->setGraphicsEffect(shadow);

        return btn;
    };

    scrollArea->setStyleSheet(
        "QScrollArea {"
        "    border: none;"
        "    background: #f5f5f7;"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: transparent;"
        "    width: 8px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #c7c7cc;"
        "    border-radius: 4px;"
        "    min-height: 30px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #a0a0a5;"
        "}"
        );

}

void SettingWindow::setUserProfile(const FriendData& profile)
{
    m_profile = profile;

    if (m_nameLabel) {
        m_nameLabel->setText(profile.name);
    }

    if (m_handleLabel) {
        m_handleLabel->setText(profile.handle);
    }

    if (m_avatarLabel) {
        QPixmap pm(profile.avatar);
        if (!pm.isNull()) {
            m_avatarLabel->setPixmap(pm.scaled(m_avatarLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        } else {
            m_avatarLabel->setPixmap(QPixmap());
            m_avatarLabel->setText(profile.name.left(1).toUpper());
        }
    }
}
