#include "settingwindow.h"
#include <QMessageBox>
#include <QFrame>
#include <QStyle>

extern QString translate(const QString& text);

SettingWindow::SettingWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void SettingWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // nav
    QWidget *header = new QWidget();
    header->setStyleSheet("background-color: #f8f8f8;");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(15, 15, 15, 15);

    QPushButton *backBtn = new QPushButton("←");
    backBtn->setStyleSheet("QPushButton { border: none; font-size: 20px; color: #333; background: transparent; }");
    backBtn->setFixedSize(40, 40);

    QLabel *title = new QLabel(translate("Settings"));
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");

    headerLayout->addWidget(backBtn);
    headerLayout->addWidget(title);
    headerLayout->addStretch();

    mainLayout->addWidget(header);

    // back
    connect(backBtn, &QPushButton::clicked, this, &SettingWindow::backToHome);

    // content
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: white; }");

    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(15);

    QFrame *userCard = new QFrame();
    userCard->setStyleSheet("QFrame { background: white; border: 1px solid #eee; border-radius: 10px; }");
    QHBoxLayout *userLayout = new QHBoxLayout(userCard);
    userLayout->setContentsMargins(15, 15, 15, 15);

    m_avatarLabel = new QLabel();
    m_avatarLabel->setFixedSize(60, 60);
    m_avatarLabel->setStyleSheet("border-radius: 30px; border: 2px solid #ddd; background: #e0e0e0;");
    m_avatarLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *userInfo = new QVBoxLayout();
    userInfo->setSpacing(5);
    m_nameLabel = new QLabel(translate("Guest"));
    m_nameLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    m_handleLabel = new QLabel("@guest");
    m_handleLabel->setStyleSheet("color: #666;");
    userInfo->addWidget(m_nameLabel);
    userInfo->addWidget(m_handleLabel);

    userLayout->addWidget(m_avatarLabel);
    userLayout->addLayout(userInfo);
    userLayout->addStretch();

    contentLayout->addWidget(userCard);

    // FEATURES
    QLabel *featuresTitle = new QLabel(translate("FEATURES"));
    featuresTitle->setStyleSheet("color: #888; font-weight: bold; font-size: 12px; margin-top: 10px;");
    contentLayout->addWidget(featuresTitle);

    // AUDIO
    QPushButton *audioBtn = new QPushButton(translate("Audio"));
    audioBtn->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #333;"
        "    background: white;"
        "    border: 1px solid #eee;"
        "    border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "    background: #f9f9f9;"
        "}"
        );
    contentLayout->addWidget(audioBtn);

    connect(audioBtn, &QPushButton::clicked, [this]() {
        emit openDetail(translate("Audio"), translate("Audio"));
    });

    // SETTINGS
    QLabel *settingsTitle = new QLabel(translate("SETTINGS"));
    settingsTitle->setStyleSheet("color: #888; font-weight: bold; font-size: 12px; margin-top: 20px;");
    contentLayout->addWidget(settingsTitle);

    auto createBtn = [this](const QString& text) {
        QPushButton *btn = new QPushButton(text);
        btn->setStyleSheet(
            "QPushButton {"
            "    text-align: left;"
            "    padding: 15px;"
            "    font-size: 16px;"
            "    color: #333;"
            "    background: white;"
            "    border: 1px solid #eee;"
            "    border-radius: 8px;"
            "}"
            "QPushButton:hover {"
            "    background: #f9f9f9;"
            "}"
            );
        return btn;
    };

    QPushButton *notificationsBtn = createBtn(translate("Notifications"));
    QPushButton *privacyBtn = createBtn(translate("Privacy"));
    QPushButton *timezoneBtn = createBtn(translate("Time Zone"));
    QPushButton *otherBtn = createBtn(translate("Other"));

    contentLayout->addWidget(notificationsBtn);
    contentLayout->addWidget(privacyBtn);
    contentLayout->addWidget(timezoneBtn);
    contentLayout->addWidget(otherBtn);

    connect(notificationsBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Notifications", "Notifications");
    });
    connect(privacyBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Privacy", "Privacy");
    });
    connect(timezoneBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Time Zone", "Time Zone");
    });
    connect(otherBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Other", "Other");
    });

    // ABOUT
    QLabel *aboutTitle = new QLabel(translate("ABOUT"));
    aboutTitle->setStyleSheet("color: #888; font-weight: bold; font-size: 12px; margin-top: 20px;");
    contentLayout->addWidget(aboutTitle);

    QPushButton *shareBtn = createBtn(translate("Share FeeL"));
    QPushButton *rateBtn = createBtn(translate("Rate FeeL"));
    QPushButton *helpBtn = createBtn(translate("Help"));
    QPushButton *aboutBtn = createBtn(translate("About"));

    contentLayout->addWidget(shareBtn);
    contentLayout->addWidget(rateBtn);
    contentLayout->addWidget(helpBtn);
    contentLayout->addWidget(aboutBtn);

    connect(shareBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Share FeeL", "Share FeeL");
    });
    connect(rateBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Rate FeeL", "Rate FeeL");
    });
    connect(helpBtn, &QPushButton::clicked, [this]() {
        emit openDetail("Help", "Help");
    });
    connect(aboutBtn, &QPushButton::clicked, [this]() {
        emit openDetail("About", "About");
    });

    // OUT
    QPushButton *logoutBtn = new QPushButton(translate("Log Out"));
    logoutBtn->setStyleSheet("QPushButton { padding: 12px; font-size: 16px; font-weight: bold; color: white; background: #ff4757; border: none; border-radius: 8px; margin-top: 30px; }"
                             "QPushButton:hover { background: #ff3742; }");
    contentLayout->addWidget(logoutBtn);

    connect(logoutBtn, &QPushButton::clicked, []() {
        QMessageBox msgBox;
        msgBox.setWindowTitle(translate("Log Out"));
        msgBox.setText(translate("Are you sure you want to log out?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::Yes) {
            QMessageBox::information(nullptr, translate("Logged Out"), translate("You have been successfully logged out."));
        }
    });

    contentLayout->addStretch();

    scrollArea->setWidget(content);
    mainLayout->addWidget(scrollArea);
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

        m_avatarLabel->setText(profile.name.left(1).toUpper());
    }
}
