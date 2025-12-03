#include "detailwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QSlider>
#include <QCheckBox>
#include <QMenu>
#include <QComboBox>
#include <QToolButton>

extern QString translate(const QString& text);

DetailWindow::DetailWindow(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(320, 480); // allow responsive resizing instead of a fixed phone size
}

void DetailWindow::setupContent(const QString& title)
{
    m_title = title;
    if (QLayout *old = layout()) {
        QLayoutItem *item;
        while ((item = old->takeAt(0)) != nullptr) {
            if (QWidget *w = item->widget()) {
                w->deleteLater();
            }
            delete item;
        }
        delete old;
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);

    QWidget *header = new QWidget(this);
    header->setObjectName("header");
    header->setStyleSheet("QWidget#header { background-color: transparent; }");
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *backBtn = new QPushButton(QStringLiteral("‹"), header);
    backBtn->setObjectName("backBtn");
    backBtn->setStyleSheet(
        "QPushButton#backBtn {"
        "    padding: 6px 10px;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 12px;"
        "    font-size: 18px;"
        "    color: #0b0b0b;"
        "    background: #ffffff;"
        "}"
        "QPushButton#backBtn:hover {"
        "    background: #f5f5f5;"
        "}"
        );
    backBtn->setFixedSize(46, 36);

    QLabel *titleLabel = new QLabel(title, header);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setStyleSheet(
        "QLabel#titleLabel {"
        "    font-size: 18px;"
        "    font-weight: 800;"
        "    color: #0b0b0b;"
        "}"
        );

    headerLayout->addWidget(backBtn);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    mainLayout->addWidget(header);

    connect(backBtn, &QPushButton::clicked, this, &DetailWindow::backClicked);

    // content
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("scrollArea");
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(
        "QScrollArea#scrollArea {"
        "    border: none;"
        "    background: transparent;"
        "}"
        );

    QWidget *contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(10, 6, 10, 10);
    contentLayout->setSpacing(12);

    if (title == "Audio" || title == "音频") {
        setupAudioContent(contentLayout);
    } else if (title == "Notifications" || title == "通知") {
        setupNotificationsContent(contentLayout);
    } else if (title == "Privacy" || title =="隐私") {
        setupPrivacyContent(contentLayout);
    } else if (title == "Time Zone" || title =="时区") {
        setupTimezoneContent(contentLayout);
    } else if (title == "Other" || title =="其他") {
        setupOtherContent(contentLayout);
    } else if (title == "Share FeeL" || title =="分享FeeL") {
        setupShareContent(contentLayout);
    } else if (title == "Rate FeeL" || title =="评价Feel") {
        setupRateContent(contentLayout);
    } else if (title == "Help" || title =="帮助") {
        setupHelpContent(contentLayout);
    } else if (title == "About" || title =="更多") {
        setupAboutContent(contentLayout);
    } else {
        QLabel *defaultLabel = new QLabel("Settings for: " + title, contentWidget);
        defaultLabel->setWordWrap(true);
        defaultLabel->setStyleSheet("font-size: 16px; color: #4d4d4d;");
        contentLayout->addWidget(defaultLabel);
    }

    contentLayout->addStretch();
    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);
}

void DetailWindow::setupAudioContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *volumeLabel = new QLabel(translate("Volume"), parent);
    volumeLabel->setStyleSheet("font-size: 16px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(volumeLabel);

    QSlider *volumeSlider = new QSlider(Qt::Horizontal, parent);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(70);
    volumeSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    height: 6px;"
        "    background: #e0e0e0;"
        "    border-radius: 3px;"
        "}"
        "QSlider::handle:horizontal {"
        "    width: 20px;"
        "    margin: -8px 0;"
        "    background: #007aff;"
        "    border-radius: 10px;"
        "}"
        );
    layout->addWidget(volumeSlider);

    layout->addSpacing(20);

    QCheckBox *muteCheckbox = new QCheckBox(translate("Mute audio"), parent);
    muteCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(muteCheckbox);

    QCheckBox *autoPlayCheckbox = new QCheckBox(translate("Auto-play videos"), parent);
    autoPlayCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(autoPlayCheckbox);
}

void DetailWindow::setupNotificationsContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QCheckBox *pushCheckbox = new QCheckBox(translate("Push notifications"), parent);
    pushCheckbox->setChecked(true);
    pushCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(pushCheckbox);

    QCheckBox *soundCheckbox = new QCheckBox(translate("Sound"), parent);
    soundCheckbox->setChecked(true);
    soundCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(soundCheckbox);

    QCheckBox *vibrateCheckbox = new QCheckBox(translate("Vibrate"), parent);
    vibrateCheckbox->setChecked(true);
    vibrateCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(vibrateCheckbox);

    layout->addSpacing(20);

    QLabel *typesLabel = new QLabel(translate("Notification types"), parent);
    typesLabel->setStyleSheet("font-size: 16px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(typesLabel);

    QCheckBox *likeCheckbox = new QCheckBox(translate("Likes"), parent);
    likeCheckbox->setChecked(true);
    likeCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(likeCheckbox);

    QCheckBox *commentCheckbox = new QCheckBox(translate("Comments"), parent);
    commentCheckbox->setChecked(true);
    commentCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(commentCheckbox);

    QCheckBox *followCheckbox = new QCheckBox(translate("New followers"), parent);
    followCheckbox->setChecked(true);
    followCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(followCheckbox);
}

void DetailWindow::setupPrivacyContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *accountLabel = new QLabel(translate("Account privacy"), parent);
    accountLabel->setStyleSheet("font-size: 16px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(accountLabel);

    QComboBox *privacyCombo = new QComboBox(parent);
    privacyCombo->addItems(QStringList() << translate("Public") << translate("Private") << translate("Friends only"));
    privacyCombo->setStyleSheet(
        "QComboBox {"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    border: none;"
        "    border-radius: 8px;"
        "    background: #f5f5f5;"
        "}"
        );
    layout->addWidget(privacyCombo);

    layout->addSpacing(20);

    QCheckBox *hideProfileCheckbox = new QCheckBox(translate("Hide profile from search"), parent);
    hideProfileCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(hideProfileCheckbox);

    QCheckBox *hideActivityCheckbox = new QCheckBox(translate("Hide activity status"), parent);
    hideActivityCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(hideActivityCheckbox);
}

void DetailWindow::setupTimezoneContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *timezoneLabel = new QLabel(translate("Select time zone"), parent);
    timezoneLabel->setStyleSheet("font-size: 16px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(timezoneLabel);

    QComboBox *timezoneCombo = new QComboBox(parent);
    timezoneCombo->addItems(QStringList() << "UTC" << "GMT" << "EST" << "CST" << "PST" << "Beijing" << "Tokyo");
    timezoneCombo->setStyleSheet(
        "QComboBox {"
        "    padding: 10px;"
        "    font-size: 16px;"
        "    border: none;"
        "    border-radius: 8px;"
        "    background: #f5f5f5;"
        "}"
        );
    layout->addWidget(timezoneCombo);

    layout->addSpacing(20);

    QCheckBox *autoTimezoneCheckbox = new QCheckBox(translate("Auto-detect time zone"), parent);
    autoTimezoneCheckbox->setChecked(true);
    autoTimezoneCheckbox->setStyleSheet("QCheckBox { font-size: 16px; color: #0b0b0b; }");
    layout->addWidget(autoTimezoneCheckbox);
}

void DetailWindow::setupOtherContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QPushButton *clearCacheButton = new QPushButton(translate("Clear Cache"), parent);
    clearCacheButton->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(clearCacheButton);

    QPushButton *dataUsageButton = new QPushButton(translate("Data Usage"), parent);
    dataUsageButton->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(dataUsageButton);

    QToolButton *languageBtn = new QToolButton(this);
    languageBtn->setText(translate("Language"));
    languageBtn->setStyleSheet(
        "QToolButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QToolButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(languageBtn);

    QMenu *languageMenu = new QMenu(languageBtn);
    QAction *englishAction = languageMenu->addAction("English");
    QAction *chineseAction = languageMenu->addAction("中文");

    languageBtn->setMenu(languageMenu);
    languageBtn->setPopupMode(QToolButton::InstantPopup);

    connect(englishAction, &QAction::triggered, this, [this]() {
        emit languageSelected("en");
    });

    connect(chineseAction, &QAction::triggered, this, [this]() {
        emit languageSelected("zh");
    });
}

void DetailWindow::setupShareContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *description = new QLabel(translate("Share FeeL with your friends and family!"), parent);
    description->setWordWrap(true);
    description->setStyleSheet("font-size: 15px; color: #4d4d4d; line-height: 1.5;");
    layout->addWidget(description);

    layout->addSpacing(30);

    QPushButton *shareButton = new QPushButton(translate("Share Now"), parent);
    shareButton->setStyleSheet(
        "QPushButton {"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(shareButton);
}

void DetailWindow::setupRateContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *description = new QLabel(translate("If you enjoy using FeeL, please take a moment to rate us. Your feedback helps us improve!"), parent);
    description->setWordWrap(true);
    description->setStyleSheet("font-size: 15px; color: #4d4d4d; line-height: 1.5;");
    layout->addWidget(description);

    layout->addSpacing(30);

    QPushButton *rateButton = new QPushButton(translate("Rate on App Store"), parent);
    rateButton->setStyleSheet(
        "QPushButton {"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(rateButton);
}

void DetailWindow::setupHelpContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *title = new QLabel(translate("Help & Support"), parent);
    title->setStyleSheet("font-size: 18px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(title);

    layout->addSpacing(20);

    QPushButton *faqButton = new QPushButton(translate("FAQ"), parent);
    faqButton->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(faqButton);

    QPushButton *contactButton = new QPushButton(translate("Contact Support"), parent);
    contactButton->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(contactButton);

    QPushButton *reportButton = new QPushButton(translate("Report a Problem"), parent);
    reportButton->setStyleSheet(
        "QPushButton {"
        "    text-align: left;"
        "    padding: 15px;"
        "    font-size: 16px;"
        "    color: #0b0b0b;"
        "    background: transparent;"
        "    border: 2px solid #0b0b0b;"
        "    border-radius: 14px;"
        "}"
        "QPushButton:hover {"
        "    background: #f7f7f7;"
        "}"
        );
    layout->addWidget(reportButton);
}

void DetailWindow::setupAboutContent(QVBoxLayout *layout)
{
    QWidget *parent = layout->parentWidget();

    QLabel *title = new QLabel(translate("About FeeL"), parent);
    title->setStyleSheet("font-size: 18px; font-weight: 800; color: #0b0b0b;");
    layout->addWidget(title);

    layout->addSpacing(20);

    QLabel *version = new QLabel(translate("Version: 1.0.0"), parent);
    version->setStyleSheet("font-size: 16px; color: #4d4d4d;");
    layout->addWidget(version);

    QLabel *build = new QLabel(translate("Build: 2025.12.1"), parent);
    build->setStyleSheet("font-size: 16px; color: #4d4d4d;");
    layout->addWidget(build);

    layout->addSpacing(20);

    QLabel *description = new QLabel(translate("FeeL is a social video platform that allows users to share and discover authentic moments with friends and the community."), parent);
    description->setWordWrap(true);
    description->setStyleSheet("font-size: 15px; color: #4d4d4d; line-height: 1.5;");
    layout->addWidget(description);
}
