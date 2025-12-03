// #include <iostream>
// #include <algorithm>
#include <algorithm>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMap>
#include <QString>
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
#include <QHash>
#include <QPointer>
#include <memory>
#include <functional>
#include <QtCore/QString>
#include <QEvent>
#include <QMouseEvent>
#include <QSlider>
#include <QComboBox>
#include <QtCore/QObject>
#include "chatwindow.h"
#include "the_button.h"
#include "friends_data.h"
#include "postpage.h"
#include <QLocale>
#include <QLibraryInfo>
#include <QTextCodec>
#include <QTranslator>
#include <QTransform>
#include <QAction>
#include <QMenu>
#include <QDialog>
#include <QSettings>
#include <QMessageBox>
#include <QProcess>
#include <QApplication>
#include "postpage.h"
#include "settingwindow.h"
#include "detailwindow.h"

// translator pointer
QTranslator* g_translator = nullptr;
QString g_currentLang = "en";



QMap<QString, QMap<QString, QString>> translationDictionary = {
    {"en",  {
            {"Friend List", "Friend List"},
            {"Friends", "Friends"},
            {"Profile", "Profile"},
            {"Language", "Language"},
            {"Back", "Back"},
            {"Publish", "Publish"},
            {"Publish captured photo?", "Publish captured photo?"},
            {"Publish captured video?", "Publish captured video?"},
            {"Photo", "Photo"},
            {"Video", "Video"},
            {"Open album? (mock)", "Open album? (mock)"},
            {"Open", "Open"},
            {"Cancel", "Cancel"},
            {"No bio", "No bio"},
            {"Chat", "Chat"},
            {"Message", "Message"},
            {"Send", "Send"},
            {"Tap to open chat", "Tap to open chat"},
            {"Home", "Home"},
            {"Post", "Post"},
            {"Search friends...", "Search friends..."},
            {"Suggested", "Suggested"},
            {"Add comment...", "Add comment..."},
            {"Share Profile", "Share Profile"},
            {"Posts are private by default", "Posts are private by default"},
            {"Video", "Video"},
            {"Comments", "Comments"},
            {"Copy Link", "Copy Link"},
            {"Save", "Save"},
            {"Close", "Close"},
            {"Share", "Share"},
            {"Follow", "Follow"},
            {"Followed", "Followed"},
            {"Full screen", "Full screen"},
            {"New Post", "New Post"},
            {"Hello!", "Hello!"},
            {"Hi there!", "Hi there!"},
            {"How are you?", "How are you?"},
            {"I'm good, thanks!", "I'm good, thanks!"}
           }},
    {"zh",  {
            {"Friend List", "好友列表"},
            {"Friends", "好友"},
            {"Profile", "个人资料"},
            {"Language", "语言"},
            {"Back", "返回"},
            {"Publish", "发布"},
            {"Publish captured photo?", "发布拍摄的照片？"},
            {"Publish captured video?", "发布拍摄的视频？"},
            {"Photo", "照片"},
            {"Video", "视频"},
            {"Open album? (mock)", "打开相册？（演示）"},
            {"Open", "打开"},
            {"Cancel", "取消"},
            {"No bio", "暂无简介"},
            {"Chat", "聊天"},
            {"Message", "消息"},
            {"Send", "发送"},
            {"Tap to open chat", "点击开始聊天"},
            {"Home", "首页"},
            {"Post", "发布"},
            {"Search friends...", "搜索好友..."},
            {"Suggested", "推荐"},
            {"Add comment...", "添加评论..."},
            {"Share Profile", "分享资料"},
            {"Posts are private by default", "帖子默认设为私密"},
            {"Instagram", "分享"},
            {"Messages", "信息"},
            {"Video", "视频"},
            {"Send to apps or drop inside friends.", "发送到应用程序或发送给好友"},
            {"Comments", "评论"},
            {"Live chat", "在线聊天"},
            {"Add a comment...", "添加评论"},
            {"Copy Link", "复制链接"},
            {"Save", "保存"},
            {"Close", "关闭"},
            {"Share", "分享"},
            {"Follow", "关注"},
            {"Followed", "已关注"},
            {"Full screen", "全屏"},
            {"New Post", "新帖子"},
            {"Hello!", "你好！"},
            {"Hi there!", "嗨！"},
            {"How are you?", "你好吗？"},
            {"No video", "无视频"},
            {"I'm good, thanks!", "我很好，谢谢！"},
            {"Recommend Accounts", "推荐账号"},
            {"Add or search friends", "添加或搜索好友"},

            {"Audio", "音频"},{"FEATURES", "特点"},
            {"Settings", "设置"},{"SETTINGS", "设置"},{"Notifications", "通知"},
            {"Privacy", "隐私"},{"Time Zone", "时区"},
            {"Other", "其他"},{"ABOUT", "关于"},
            {"Share FeeL", "分享FeeL"},{"Rate FeeL", "评价Feel"},
            {"Help", "帮助"},{"About", "更多"},{"Log Out", "退出登录"},
            {"This is the detailed view for: ","此页为："},
            {"Are you sure you want to log out?","你确定要退出登录吗？"},
            {"Volume", "音量"},{"Mute audio", "静音"},{"Auto-play videos", "自动播放视频"},
            {"Sound", "声音"},{"Push notifications", "音频推送通知"},{"Vibrate", "振动"},
            {"Notification types", "通知类型"},{"Likes", "喜欢"},{"Comments", "评论"},
            {"New followers", "新关注的人"},

            {"Private", "私人"},{"Friends only", "仅朋友"},{"Public", "公共"},
            {"Account privacy", "账户隐私"},{"Hide profile from search", "在搜索中隐藏个人资料"},{"Hide activity status", "隐藏活动状态"},
            {"Select time zone", "选择时区"},{"Auto-detect time zone", "自动检测时区"},
            {"Clear Cache", "清除缓存"},{"Data Usage", "数据使用"},{"Language", "语言"},
            {"Share FeeL with your friends and family!", "把FeeL分享给你的朋友和家人吧！"},{"Share Now", "分享"},
            {"If you enjoy using FeeL, please take a moment to rate us. Your feedback helps us improve!", "如果您喜欢使用FeeL，请花点时间给我们评分。您的反馈有助于我们改进！"},
            {"Rate on App Store", "应用商店评分"},
            {"Help & Support", "帮助与支持"},{"Contact Support", "联系客服"},{"FAQ","常见问题解答"},
            {"Report a Problem", "报告问题"},{"About FeeL", "关于FeeL"},{"Version: 1.0.0", "版本:1.0.0"},
            {"Build: 2024.12.1", "开发于：2024.12.1"},
            {"FeeL is a social video platform that allows users to share and discover authentic moments with friends and the community.", "FeeL是一个社交视频平台，允许用户与朋友及社区分享和发现真实的瞬间。"},
            {"Your Posts are private and ephemeral unless shared.", "除非进行分享，否则你的帖子是私密且短暂的。"}

        }}
};

// current language
QString currentLanguage = "en";
void saveLanguageSetting(const QString& lang) {
    QSettings settings("XJCO2811", "FeeL");
    settings.setValue("language", lang);
    qDebug() << "保存语言设置:" << lang;
}

// loding language
QString loadLanguageSetting() {
    QSettings settings("XJCO2811", "FeeL");
    QString lang = settings.value("language", "en").toString();
    qDebug() << "加载语言设置:" << lang;
    return lang;
}

// restart app
void restartApplication() {
    qDebug() << "重启应用...";
    QProcess::startDetached(QApplication::applicationFilePath(), QStringList());
    QApplication::quit();
}

// translate
QString translate(const QString& text) {
    if (translationDictionary.contains(currentLanguage) &&
        translationDictionary[currentLanguage].contains(text)) {
        return translationDictionary[currentLanguage][text];
    }
    return text;
}

// refresh the interface
void refreshUITexts() {

    QMessageBox::information(nullptr,
                             translate("Language Changed"),
                             translate("Please restart the application to apply language changes."));
}
// language switching function

void switchLanguage(const QString& lang) {
    if (lang == "zh" || lang == "en") {
        currentLanguage = lang;
        saveLanguageSetting(lang);

        //restart prompt
        QMessageBox msgBox;
        msgBox.setWindowTitle(translate("Language Changed"));
        msgBox.setText(translate("Language changed successfully!"));
        msgBox.setInformativeText(translate("The application needs to restart to apply the changes. Restart now?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes) {
            restartApplication();
        }
    }
}



// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );

    if (!dir.exists()) {
        qDebug() << "Video directory not found:" << QString::fromStdString(loc);
        return out;
    }
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

// draw heart outline/fill for like buttons
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

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

    // set application information
    app.setApplicationName("FeeL - Video Social App");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("XJCO2811");
    app.setOrganizationDomain("leeds.ac.uk");

    currentLanguage = loadLanguageSetting();
    qDebug() << "当前语言:" << currentLanguage;
    // initialize the translator
    g_translator = new QTranslator;

    // create the main window
    QWidget window;
    window.setWindowTitle("FeeL");
    window.setMinimumSize(520, 900);

    QHBoxLayout *root = new QHBoxLayout();
    root->setContentsMargins(40, 50, 40, 30);
    root->addStretch();
    window.setLayout(root);

    QFrame *phone = new QFrame();


    //improve the appearance
    app.setStyle("Fusion");

    qDebug() << "Qt version: " << QT_VERSION_STR;
    qDebug() << "Starting FeeL application...";

    // collect all the videos in the folder (prompt if not provided)
    std::vector<TheButtonInfo> videos;
    QString folder;
    if (argc == 2) {
        folder = QString::fromLocal8Bit(argv[1]);
    }
    if (folder.isEmpty()) {
        folder = QFileDialog::getExistingDirectory(nullptr, translate("Select video folder"), QDir::homePath());
    }
    if (!folder.isEmpty()) {
        videos = getInfoIn(folder.toStdString());
    }

    if (videos.size() == 0) {
        qDebug() << "No videos found, using demo mode";
    }


    // create the main window with a centered phone mock
    // QWidget window;
    window.setWindowTitle("FeeL");
    window.setMinimumSize(520, 900);

    // QHBoxLayout *root = new QHBoxLayout();
    root->setContentsMargins(40, 30, 40, 30);
    root->addStretch();
    window.setLayout(root);
    window.setStyleSheet("QWidget { font-family: 'Segoe UI'; }");

    // QFrame *phone = new QFrame();
    phone->setObjectName(translate("phoneFrame"));
    phone->setMinimumWidth(360);
    phone->setStyleSheet("#phoneFrame { background:#ffffff; border-radius:46px; }");
    QVBoxLayout *phoneLayout = new QVBoxLayout(phone);
    phoneLayout->setSpacing(12);
    phoneLayout->setContentsMargins(28, 28, 28, 20);

    QWidget *header = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *logo = new QLabel();
    QPixmap logoPm(":/assets/logo.png");
    if (!logoPm.isNull()) {
        logoPm = logoPm.scaled(90, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        logo->setPixmap(logoPm);
    } else {
        logo->setText("FeeL");
        logo->setStyleSheet("font-weight:800; letter-spacing:4px; font-size:20px;");
    }
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
        if (src.isNull()) {
            // if the avatar fails to load, create a simple default avatar.
            QPixmap defaultPixmap(size, size);
            defaultPixmap.fill(QColor("#e0e0e0"));
            return defaultPixmap;
        }

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

    auto showToast = [&](const QString &msg) {
        QWidget *toast = new QWidget(&window);
        toast->setObjectName("toast");
        toast->setStyleSheet("#toast { background:rgba(0,0,0,170); border-radius:12px; } QLabel { color:#ffffff; }");
        QHBoxLayout *l = new QHBoxLayout(toast);
        l->setContentsMargins(14, 8, 14, 8);
        QLabel *lbl = new QLabel(msg);
        lbl->setStyleSheet("font-weight:600;");
        l->addWidget(lbl);
        toast->adjustSize();
        const QSize winSize = window.size();
        toast->setGeometry((winSize.width() - toast->sizeHint().width())/2,
                           winSize.height() - 120,
                           toast->sizeHint().width(),
                           toast->sizeHint().height());
        toast->setAttribute(Qt::WA_ShowWithoutActivating);
        toast->show();
        QTimer::singleShot(1500, toast, [toast]() { toast->deleteLater(); });
    };

    auto showShareSheet = [&](const QString &title, QWidget *parent, ChatWindow *chatPageRef, QWidget *chatContainerRef, const std::function<void()> &refreshFeed) {
        QDialog dialog(parent);
        dialog.setModal(true);
        dialog.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        dialog.setAttribute(Qt::WA_TranslucentBackground);
        QVBoxLayout *outer = new QVBoxLayout(&dialog);
        outer->setContentsMargins(24, 24, 24, 24);

        QFrame *sheet = new QFrame();
        sheet->setObjectName(translate("shareSheet"));
        sheet->setStyleSheet("#shareSheet { background:#ffffff; border:2px solid #0b0b0b; border-radius:22px; }");
        QVBoxLayout *sheetLayout = new QVBoxLayout(sheet);
        sheetLayout->setSpacing(12);
        sheetLayout->setContentsMargins(18, 18, 18, 18);

        QLabel *titleLbl = new QLabel(title);
        titleLbl->setStyleSheet("font-weight:800; font-size:16px;");
        sheetLayout->addWidget(titleLbl);

        QLabel *subtitle = new QLabel(translate("Send to apps or drop inside friends."));
        subtitle->setStyleSheet("color:#6a6a6a;");
        sheetLayout->addWidget(subtitle);

        QStringList apps = {translate("Copy Link"),
                            translate("Instagram"),
                            translate("Messages"),
                            translate("Save")};
        QHBoxLayout *appRow = new QHBoxLayout();
        appRow->setSpacing(8);
        for (int i = 0; i < apps.size(); ++i) {
            const QString app = apps.at(i);
            QPushButton *chip = new QPushButton(app);
            chip->setStyleSheet("padding:8px 12px; border:1px solid #0b0b0b; border-radius:12px; background:#f7f7f7; font-weight:600;");
            appRow->addWidget(chip);
            if (app == translate("Copy Link")) {
                QObject::connect(chip, &QPushButton::clicked, chip, [=]() {
                    chip->setText(translate("Copied"));
                });
            } else if (app == translate("Instagram") || app == translate("Messages")) {
                QObject::connect(chip, &QPushButton::clicked, chip, [=]() {
                    showToast(QStringLiteral("Waiting to launch other apps..."));
                });
            } else if (app == translate("Save")) {
                QObject::connect(chip, &QPushButton::clicked, chip, [=]() {
                    chip->setText(translate("Saved"));
                    showToast(translate("Saved"));
                });
            }
        }
        appRow->addStretch();
        sheetLayout->addLayout(appRow);

        QLabel *friendsTitle = new QLabel(translate("Friends in FeeL"));
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

            QPushButton *send = new QPushButton(translate("Send"));
            send->setStyleSheet("padding:6px 12px; border:1px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:600;");
            rowLayout->addWidget(send);
            QObject::connect(send, &QPushButton::clicked, &dialog, [=]() {
                showToast(QStringLiteral("Sent"));
                if (chatPageRef && chatContainerRef) {
                    chatPageRef->sendShareMessage(i, QStringLiteral("[shared message]"));
                    if (refreshFeed) refreshFeed();
                }
            });
            friendRows->addWidget(row);
        }
        sheetLayout->addLayout(friendRows);

        QPushButton *close = new QPushButton(translate("Close"));
        close->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#fdfdfd; font-weight:700;");
        QObject::connect(close, &QPushButton::clicked, &dialog, &QDialog::accept);
        sheetLayout->addWidget(close, 0, Qt::AlignRight);

        outer->addWidget(sheet);
        dialog.exec();
    };

    QLabel *profileHandleLabel = nullptr;
    QLabel *profileFollowStatusLabel = nullptr;
    QLineEdit *searchField = nullptr;
    ChatWindow *chatPage = nullptr;
    QWidget *chatContainer = nullptr;
    QWidget *postPageWidget = nullptr;
    QWidget *lastPageBeforePost = nullptr;
    QWidget *activeOverlay = nullptr;
    QToolButton *profileSettingsBtn = nullptr;
    QList<FriendData> currentFriends;
    QList<FriendData> currentPopular;
    QHash<QString, FriendData> friendLookup;
    std::function<void()> rebuildFeed = [](){};

    // global follow state registry
    QHash<QString, bool> followState;
    QHash<QString, QList<QPointer<QPushButton>>> followButtons;
    auto setFollowVisual = [&](QPushButton *btn, bool followed) {
        if (!btn) return;
        btn->setEnabled(true);
        if (followed) {
            btn->setText(translate("Followed"));
            btn->setStyleSheet("padding:6px 14px; border:1px solid #101010; border-radius:16px; background:#e9e9e9; font-weight:600; color:#5a5a5a;");
        } else {
            btn->setText(translate("Follow"));
            btn->setStyleSheet("padding:6px 14px; border:1px solid #101010; border-radius:16px; background:#ffffff; font-weight:600; color:#0b0b0b;");
        }
    };

    auto registerFollowButton = [&](const QString &handle, QPushButton *btn) {
        followButtons[handle].append(QPointer<QPushButton>(btn));
    };

    auto syncFollowButtons = [&](const QString &handle) {
        const bool followed = followState.value(handle, false);
        if (followButtons.contains(handle)) {
            QList<QPointer<QPushButton>> list = followButtons.value(handle);
            for (QPointer<QPushButton> b : list) {
                if (b) setFollowVisual(b, followed);
            }
            followButtons[handle] = list;
        }
        if (profileHandleLabel && profileHandleLabel->text() == handle && profileFollowStatusLabel) {
            if (handle == myProfile.handle) {
                profileFollowStatusLabel->setVisible(false);
            } else {
                profileFollowStatusLabel->setVisible(true);
                profileFollowStatusLabel->setText(followed ? translate("Followed") : translate("Follow"));
            }
        }
    };

    std::function<void()> refreshFriendsUI = [](){};

    auto takeByHandle = [](QList<FriendData> &list, const QString &handle, FriendData *out) -> bool {
        for (int i = 0; i < list.size(); ++i) {
            if (list[i].handle == handle) {
                if (out) *out = list.takeAt(i);
                else list.removeAt(i);
                return true;
            }
        }
        return false;
    };

    auto handleFollowClick = [&](const QString &handle) {
        if (handle.isEmpty()) return;
        const bool now = followState.value(handle, false);
        const bool next = !now;
        followState.insert(handle, next);
        FriendData moved;
        if (next) {
            if (takeByHandle(currentPopular, handle, &moved)) {
                currentFriends.prepend(moved);
            } else if (friendLookup.contains(handle) && !takeByHandle(currentFriends, handle, nullptr)) {
                currentFriends.prepend(friendLookup.value(handle));
            }
        } else {
            if (takeByHandle(currentFriends, handle, &moved)) {
                currentPopular.prepend(moved);
            }
        }

        syncFollowButtons(handle);
        refreshFriendsUI();
    };

    for (const auto &f : friends) friendLookup.insert(f.handle, f);
    currentFriends = friends.mid(0, 3);
    currentPopular = friends.mid(3);
    for (const auto &f : currentFriends) followState.insert(f.handle, true);
    // profile page (populated on selection)
    QWidget *profilePage = new QWidget();
    QVBoxLayout *profileLayout = new QVBoxLayout(profilePage);
    profileLayout->setContentsMargins(16, 16, 16, 16);
    profileLayout->setSpacing(16);
    QPushButton *backToFriends = new QPushButton(translate("Friends"));
    backToFriends->setStyleSheet("padding:8px 16px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
    QHBoxLayout *profileTop = new QHBoxLayout();
    profileTop->setContentsMargins(0, 0, 0, 0);
    profileTop->addWidget(backToFriends, 0, Qt::AlignLeft);
    profileTop->addStretch();
    profileSettingsBtn = new QToolButton();
    profileSettingsBtn->setText(QStringLiteral("⚙"));
    profileSettingsBtn->setToolTip(translate("Settings"));
    profileSettingsBtn->setFixedSize(38, 38);
    profileSettingsBtn->setStyleSheet("QToolButton { padding:6px; border:2px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:700; }");
    profileTop->addWidget(profileSettingsBtn, 0, Qt::AlignRight);
    profileLayout->addLayout(profileTop);

    QLabel *profileAvatar = new QLabel();
    profileAvatar->setFixedSize(160, 160);
    profileAvatar->setAlignment(Qt::AlignCenter);
    profileAvatar->setStyleSheet("background:#d7d7d7; border-radius:80px;");
    profileLayout->addWidget(profileAvatar, 0, Qt::AlignHCenter);

    QLabel *profileName = new QLabel(translate("Guest"));
    profileName->setStyleSheet("font-size:24px; font-weight:700; color:#0b0b0b;");
    profileLayout->addWidget(profileName, 0, Qt::AlignHCenter);

    QLabel *profileHandle = new QLabel("@guest");
    profileHandleLabel = profileHandle;
    profileHandle->setStyleSheet("font-size:14px; color:#666;");
    profileLayout->addWidget(profileHandle, 0, Qt::AlignHCenter);

    QLabel *profileFollowStatus = new QLabel();
    profileFollowStatusLabel = profileFollowStatus;
    profileFollowStatus->setStyleSheet("font-size:13px; color:#444; border:none; border-radius:12px; padding:6px 10px; background:transparent;");
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
    QWidget *berealStat = statWidget(&berealValue, translate("Posts"));
    QWidget *friendsStat = statWidget(&friendsValue, translate("Friends"));
    QWidget *followingStat = statWidget(&followingValue, translate("Following"));
    statsRow->addStretch();
    statsRow->addWidget(berealStat);
    statsRow->addWidget(friendsStat);
    statsRow->addWidget(followingStat);
    statsRow->addStretch();
    profileLayout->addLayout(statsRow);

        QPushButton *shareProfile = new QPushButton(translate("Share Profile"));
    shareProfile->setStyleSheet("padding:12px 18px; border-radius:18px; background:#2f2f2f; color:#ffffff; font-weight:700;");
    profileLayout->addWidget(shareProfile, 0, Qt::AlignHCenter);
    QObject::connect(shareProfile, &QPushButton::clicked, &window, [&]() {
        showShareSheet(QStringLiteral("Share %1").arg(myProfile.handle), &window, chatPage, chatContainer, rebuildFeed);
    });

    QLabel *privacyNote = new QLabel(translate("Your Posts are private and ephemeral unless shared."));
    privacyNote->setStyleSheet("font-size:12px; color:#6a6a6a;");
    profileLayout->addWidget(privacyNote, 0, Qt::AlignHCenter);

    // gallery grid
    QWidget *galleryWrap = new QWidget();
    QGridLayout *galleryLayout = new QGridLayout(galleryWrap);
    galleryLayout->setSpacing(10);
    profileLayout->addWidget(galleryWrap);
    profileLayout->addStretch();
    contentStack->addWidget(profilePage);

    auto clearLayout = [](QLayout *layout) {
        if (!layout) return;

        // safe cleaning
        while (QLayoutItem* child = layout->takeAt(0)) {
            if (QWidget* widget = child->widget()) {
                widget->deleteLater();
            }
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
            profileFollowStatus->setText(translate("This is you"));
            profileFollowStatus->setVisible(false);
        } else {
            const bool followed = followState.value(f.handle, false);
            profileFollowStatus->setVisible(true);
            profileFollowStatus->setText(followed ? translate("Followed") : translate("Follow"));
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
            thumb->setStyleSheet("border-radius:24px; background:#f3f3f3;");
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

    class DismissFilter : public QObject {
    public:
        QWidget *panel = nullptr;
        std::function<void()> onDismiss;
        explicit DismissFilter(QObject *parent = nullptr) : QObject(parent) {}
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override {
            if (event->type() == QEvent::MouseButtonPress) {
                if (!panel) return QObject::eventFilter(obj, event);
                auto *me = static_cast<QMouseEvent*>(event);
                if (!panel->geometry().contains(me->pos())) {
                    if (onDismiss) onDismiss();
                    return true;
                }
            }
            return QObject::eventFilter(obj, event);
        }
    };

    class CornerOverlay : public QObject {
    public:
        QPointer<QWidget> host;
        QPointer<QWidget> overlay;
        int margin = 12;
        explicit CornerOverlay(QObject *parent = nullptr) : QObject(parent) {}
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override {
            if (event->type() == QEvent::Resize && host && overlay) {
                const int x = std::max(0, host->width() - overlay->width() - margin);
                const int y = std::max(0, host->height() - overlay->height() - margin);
                overlay->move(x, y);
                overlay->raise();
            }
            return QObject::eventFilter(obj, event);
        }
    };

    struct FeedCard {
        QWidget *widget = nullptr;
        QMediaPlayer *player = nullptr;
        QVideoWidget *video = nullptr;
        QToolButton *likeButton = nullptr;
        QLabel *likeCountLabel = nullptr;
        std::shared_ptr<int> likeValue;
        std::shared_ptr<bool> likedValue;
        TheButtonInfo *info = nullptr;
        FriendData account;
    };

    auto updateLikeUI = [&](FeedCard &fc) {
        if (fc.likeButton) {
            const bool liked = fc.likedValue ? *fc.likedValue : false;
            fc.likeButton->setChecked(liked);
            fc.likeButton->setIcon(makeHeartIcon(liked, 22));
        }
        if (fc.likeCountLabel) {
            const int count = fc.likeValue ? *fc.likeValue : 0;
            fc.likeCountLabel->setText(QString::number(count));
        }
    };

    // home page cards showing friend accounts as publishers
    std::function<void(FeedCard)> openDetailSheet;

    auto createPhoneCard = [&](TheButtonInfo* info, const FriendData &account, bool autoPlay) -> FeedCard {
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background:#ffffff; border:2px solid #0b0b0b; border-radius:28px; }");
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setSpacing(12);
        cardLayout->setContentsMargins(18, 18, 18, 18);

        FeedCard fc;
        fc.info = info;
        fc.account = account;
        fc.likeValue = std::make_shared<int>(120 + account.bereals * 2 + account.friends);
        fc.likedValue = std::make_shared<bool>(false);

        QWidget *mediaSurface = nullptr;
        QMediaPlayer *cardPlayer = nullptr;
        QVideoWidget *cardVideo = nullptr;

        if (info != nullptr && info->url && info->url->isValid()) {
            cardVideo = new QVideoWidget(card);
            cardVideo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            cardVideo->setStyleSheet("border:none; border-radius:16px; background:#050505;");
            cardPlayer = new QMediaPlayer(cardVideo);
            QMediaPlaylist *loop = new QMediaPlaylist(cardPlayer);
            loop->addMedia(*info->url);
            loop->setPlaybackMode(QMediaPlaylist::Loop);
            cardPlayer->setPlaylist(loop);
            cardPlayer->setVideoOutput(cardVideo);

            // Error handling
            QObject::connect(cardPlayer, static_cast<void(QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error),
                             [=](QMediaPlayer::Error error) {
                                 Q_UNUSED(error);
                             });


            if (autoPlay) {
                cardPlayer->play();
            } else {
                cardPlayer->play();
                cardPlayer->pause();
                cardPlayer->setPosition(0); // force first frame for preview
            }
            mediaSurface = cardVideo;
        } else {
            QFrame *placeholder = new QFrame();
            placeholder->setMinimumHeight(200);
            placeholder->setStyleSheet("border-radius:16px; background:#f7f7f7;");
            QLabel *videoText = new QLabel(translate("New Post"), placeholder);
            videoText->setAlignment(Qt::AlignCenter);
            videoText->setStyleSheet("font-size:18px; letter-spacing:2px; color:#7a7a7a; font-weight:700;");
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
        avatarBtn->setStyleSheet("border-radius:22px; background:#fdfdfd;");
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
        QPushButton *followButton = new QPushButton();
        registerFollowButton(account.handle, followButton);
        setFollowVisual(followButton, followState.value(account.handle, false));
        QObject::connect(followButton, &QPushButton::clicked, &window, [=]() {
            handleFollowClick(account.handle);
        });
        profileRow->addWidget(avatarBtn);
        profileRow->addLayout(profileText);
        profileRow->addStretch();
        profileRow->addWidget(followButton);
        cardLayout->addLayout(profileRow);

        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setStyleSheet("color:#e5e5e5;");
        cardLayout->addWidget(line);

        QHBoxLayout *statsRow = new QHBoxLayout();
        statsRow->setSpacing(10);
        QToolButton *likeBtn = new QToolButton();
        likeBtn->setCheckable(true);
        likeBtn->setAutoRaise(true);
        likeBtn->setIcon(makeHeartIcon(false, 22));
        likeBtn->setStyleSheet("QToolButton { border:none; padding:6px; }");
        QLabel *likeCount = new QLabel(QString::number(*fc.likeValue));
        likeCount->setStyleSheet("font-weight:700; color:#0b0b0b; border:none; background:transparent;");
        likeCount->setFrameStyle(QFrame::NoFrame);
        statsRow->addWidget(likeBtn);
        statsRow->addWidget(likeCount);
        statsRow->addStretch();
        QToolButton *shareBtn = new QToolButton();
        shareBtn->setText(translate("Share"));
        shareBtn->setStyleSheet("QToolButton { padding:8px 14px; border:1px solid #101010; border-radius:14px; background:#ffffff; font-weight:700; }");
        statsRow->addWidget(shareBtn);
        cardLayout->addLayout(statsRow);

        QObject::connect(shareBtn, &QToolButton::clicked, &window, [&, account]() {
            showShareSheet(QStringLiteral("Share %1").arg(account.handle), &window, chatPage, chatContainer, rebuildFeed);
        });

        QFrame *commentLine = new QFrame();
        commentLine->setFrameShape(QFrame::HLine);
        commentLine->setStyleSheet("color:#ededed;");
        cardLayout->addWidget(commentLine);

        QVBoxLayout *commentSection = new QVBoxLayout();
        commentSection->setSpacing(8);
        QLabel *commentLabel = new QLabel(translate("Comments"));
        commentLabel->setStyleSheet("font-weight:700; color:#0b0b0b;");
        commentSection->addWidget(commentLabel);

        QVBoxLayout *commentsList = new QVBoxLayout();
        commentsList->setContentsMargins(0, 0, 0, 0);
        commentsList->setSpacing(8);
        commentSection->addLayout(commentsList);

        QLineEdit *commentInput = new QLineEdit();
        commentInput->setPlaceholderText(translate("Add a comment..."));
        commentInput->setStyleSheet("padding:8px 10px; border:none; border-radius:14px; background:#f6f6f6;");
        commentSection->addWidget(commentInput);

        auto addComment = [=]() {
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
            avatarLbl->setStyleSheet("border:none; border-radius:14px;");
            row->addWidget(avatarLbl);

            QVBoxLayout *textCol = new QVBoxLayout();
            textCol->setContentsMargins(0, 0, 0, 0);
            textCol->setSpacing(2);
            QLabel *nameLbl = new QLabel(myProfile.name);
            nameLbl->setStyleSheet("font-weight:700; font-size:13px; border:none;");
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
        };
        QObject::connect(commentInput, &QLineEdit::returnPressed, &window, addComment);

        cardLayout->addLayout(commentSection);

        fc.widget = card;
        fc.player = cardPlayer;
        fc.video = cardVideo;
        fc.likeButton = likeBtn;
        fc.likeCountLabel = likeCount;
        updateLikeUI(fc);

        QObject::connect(likeBtn, &QToolButton::clicked, &window, [=]() mutable {
            FeedCard fcCopy = fc;
            if (fcCopy.likedValue) *fcCopy.likedValue = likeBtn->isChecked();
            if (fcCopy.likeValue) {
                int v = *fcCopy.likeValue;
                v += (*fcCopy.likedValue) ? 1 : (v > 0 ? -1 : 0);
                *fcCopy.likeValue = qMax(0, v);
            }
            updateLikeUI(fcCopy);
        });
        QObject::connect(shareBtn, &QToolButton::clicked, &window, [&, account]() {
            showShareSheet(QStringLiteral("Share %1").arg(account.handle), &window, chatPage, chatContainer, rebuildFeed);
        });

        PlayTapFilter *cardTap = new PlayTapFilter(card);
        cardTap->onClick = [=]() mutable {
            if (!openDetailSheet) return;
            openDetailSheet(fc);
        };
        card->installEventFilter(cardTap);
        if (mediaSurface) {
            PlayTapFilter *mediaTap = new PlayTapFilter(mediaSurface);
            mediaTap->onClick = cardTap->onClick;
            mediaSurface->installEventFilter(mediaTap);
        }
        return fc;
    };

    openDetailSheet = [&](FeedCard fc) {
        if (activeOverlay) {
            activeOverlay->deleteLater();
            activeOverlay = nullptr;
        }
        QWidget *overlay = new QWidget(phone);
        overlay->setObjectName(translate("detailOverlay"));
        overlay->setStyleSheet("#detailOverlay { background: rgba(0,0,0,120); }");
        overlay->setGeometry(phone->rect());
        overlay->raise();
        activeOverlay = overlay;

        const int w = static_cast<int>(phone->width() * 0.92);
        const int h = static_cast<int>(phone->height() * 0.9);

        QVBoxLayout *overlayLayout = new QVBoxLayout(overlay);
        overlayLayout->setContentsMargins(10, 10, 10, 10);

        QFrame *panel = new QFrame();
        panel->setObjectName(translate("detailPanel"));
        panel->setStyleSheet("#detailPanel { background:#ffffff; border-radius:24px; }");
        panel->setFixedSize(w, h);
        QVBoxLayout *panelLayout = new QVBoxLayout(panel);
        panelLayout->setSpacing(16);
        panelLayout->setContentsMargins(16, 20, 16, 16);

        QWidget *videoWrap = nullptr;
        QMediaPlayer *modalPlayer = nullptr;
        bool hasVideo = fc.info != nullptr;
        QHBoxLayout *mediaControls = nullptr;
        QSlider *progressControl = nullptr;
        QSlider *volumeControl = nullptr;
        QComboBox *speedControl = nullptr;
        auto attachVideoControls = [](QMediaPlayer *player, QSlider *progress, QSlider *volume, QComboBox *speed, QToolButton *muteBtn = nullptr) {
            if (!player) return;
            QPointer<QMediaPlayer> p(player);
            if (muteBtn) {
                muteBtn->setCheckable(true);
                auto updateMuteVisual = [p, muteBtn]() {
                    if (!p || !muteBtn) return;
                    const bool muted = p->isMuted();
                    muteBtn->setChecked(muted);
                    muteBtn->setText(muted ? QStringLiteral("🔇") : QStringLiteral("🔊"));
                };
                updateMuteVisual();
                QObject::connect(muteBtn, &QToolButton::toggled, muteBtn, [p](bool on) {
                    if (p) p->setMuted(on);
                });
                QObject::connect(p, &QMediaPlayer::mutedChanged, muteBtn, updateMuteVisual);
            }
            if (progress) {
                const qint64 curDur = p ? p->duration() : 0;
                progress->setRange(0, static_cast<int>(curDur));
                progress->setValue(p ? static_cast<int>(p->position()) : 0);
                progress->setEnabled(curDur > 0);
                auto sliding = std::make_shared<bool>(false);
                QObject::connect(progress, &QSlider::sliderPressed, progress, [sliding]() { *sliding = true; });
                QObject::connect(progress, &QSlider::sliderReleased, progress, [p, progress, sliding]() {
                    *sliding = false;
                    if (p) p->setPosition(progress->value());
                });
                QObject::connect(p, &QMediaPlayer::durationChanged, progress, [progress](qint64 dur) {
                    progress->setRange(0, static_cast<int>(dur));
                });
                QObject::connect(p, &QMediaPlayer::positionChanged, progress, [p, progress, sliding](qint64 pos) {
                    if (!p) return;
                    if (!*sliding) progress->setValue(static_cast<int>(pos));
                    progress->setEnabled(progress->maximum() > 0);
                });
            }
            if (volume) {
                volume->setRange(0, 100);
                volume->setValue(p ? p->volume() : 0);
                QObject::connect(volume, &QSlider::valueChanged, volume, [p](int v) { if (p) p->setVolume(v); });
            }
            if (speed) {
                QObject::connect(speed, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), speed, [p, speed](int idx) {
                    if (!p) return;
                    const QVariant val = speed->itemData(idx);
                    p->setPlaybackRate(val.isValid() ? val.toFloat() : 1.0f);
                });
            }
        };
        struct FullscreenState {
            QPointer<QWidget> overlayLayer;
            QPointer<QWidget> videoContainer;
            QPointer<QWidget> videoWidget;
            QPointer<QVBoxLayout> hostLayout;
            QPointer<QWidget> hostPanel;
            QPointer<QMediaPlayer> player;
        };
        std::shared_ptr<FullscreenState> fullscreenState;
        std::function<void()> exitFullScreen = [](){};
        std::function<void()> enterFullScreen = [](){};
        if (hasVideo) {
            QWidget *videoContainer = new QWidget(panel);
            const int videoHeight = static_cast<int>(h * 0.35); // shrink video viewport
            videoContainer->setFixedHeight(videoHeight);
            QVBoxLayout *videoLayout = new QVBoxLayout(videoContainer);
            videoLayout->setContentsMargins(0, 0, 0, 0);
            QVideoWidget *modalVideo = new QVideoWidget(videoContainer);
            modalVideo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            modalVideo->setStyleSheet("border:none; border-radius:14px; background:#050505;");
            videoLayout->addWidget(modalVideo);
            modalPlayer = new QMediaPlayer(modalVideo);
            modalPlayer->setNotifyInterval(200);
            QMediaPlaylist *loop = new QMediaPlaylist(modalPlayer);
            loop->addMedia(*fc.info->url);
            loop->setPlaybackMode(QMediaPlaylist::Loop);
            modalPlayer->setPlaylist(loop);
            modalPlayer->setVideoOutput(modalVideo);
            modalPlayer->play();
            videoWrap = videoContainer;

            mediaControls = new QHBoxLayout();
            mediaControls->setContentsMargins(0, 0, 0, 0);
            mediaControls->setSpacing(8);
            progressControl = new QSlider(Qt::Horizontal);
            progressControl->setStyleSheet("QSlider::groove:horizontal { height:4px; background:#e0e0e0; border-radius:2px; }"
                                           "QSlider::handle:horizontal { background:#0b0b0b; width:12px; margin:-6px 0; border-radius:6px; }");
            QLabel *volIcon = new QLabel(QStringLiteral("🔊"));
            volIcon->setStyleSheet("font-weight:800; color:#0b0b0b;");
            QToolButton *volBtn = new QToolButton();
            volBtn->setText(QStringLiteral("🔊"));
            volBtn->setStyleSheet("QToolButton { border:none; padding:4px; font-size:14px; }");
            volumeControl = new QSlider(Qt::Horizontal);
            volumeControl->setFixedWidth(60);
            volumeControl->setStyleSheet("QSlider::groove:horizontal { height:4px; background:#e0e0e0; border-radius:2px; }"
                                         "QSlider::handle:horizontal { background:#0b0b0b; width:10px; margin:-6px 0; border-radius:5px; }");
            speedControl = new QComboBox();
            speedControl->addItem("0.5x", 0.5);
            speedControl->addItem("1.0x", 1.0);
            speedControl->addItem("1.25x", 1.25);
            speedControl->addItem("1.5x", 1.5);
            speedControl->setCurrentIndex(1);
            speedControl->setStyleSheet("QComboBox { padding:6px 10px; border:2px solid #0b0b0b; border-radius:10px; background:#ffffff; }");
            mediaControls->addWidget(progressControl, 1);
            mediaControls->addWidget(volBtn, 0, Qt::AlignVCenter);
            mediaControls->addWidget(volumeControl, 0, Qt::AlignVCenter);
            attachVideoControls(modalPlayer, progressControl, volumeControl, speedControl, volBtn);
            mediaControls->addWidget(speedControl, 0, Qt::AlignVCenter);

            fullscreenState = std::make_shared<FullscreenState>();
            fullscreenState->videoContainer = videoContainer;
            fullscreenState->videoWidget = modalVideo;
            fullscreenState->hostLayout = panelLayout;
            fullscreenState->hostPanel = panel;
            fullscreenState->player = modalPlayer;
            fullscreenState->videoContainer->setProperty("originalHeight", videoHeight);

            exitFullScreen = [fullscreenState]() {
                if (fullscreenState->overlayLayer) {
                    fullscreenState->overlayLayer->deleteLater();
                    fullscreenState->overlayLayer = nullptr;
                }
                if (fullscreenState->videoContainer && fullscreenState->hostPanel && fullscreenState->hostLayout) {
                    // restore original sizing
                    bool ok = false;
                    int hStored = fullscreenState->videoContainer->property("originalHeight").toInt(&ok);
                    if (ok && hStored > 0) fullscreenState->videoContainer->setFixedHeight(hStored);
                    fullscreenState->videoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                    fullscreenState->videoContainer->setParent(fullscreenState->hostPanel);
                    fullscreenState->hostLayout->insertWidget(0, fullscreenState->videoContainer);
                }
                if (fullscreenState->player) fullscreenState->player->play();
            };

            enterFullScreen = [fullscreenState, overlay, exitFullScreen, attachVideoControls]() {
                if (!fullscreenState->videoContainer || !fullscreenState->hostPanel || !fullscreenState->hostLayout) return;
                if (fullscreenState->overlayLayer) return;

                QWidget *layer = new QWidget(overlay);
                layer->setObjectName("fsLayer");
                layer->setStyleSheet("#fsLayer { background:rgba(0,0,0,220); }");
                layer->setGeometry(overlay->rect());
                layer->raise();
                QVBoxLayout *layout = new QVBoxLayout(layer);
                layout->setContentsMargins(12, 12, 12, 12);
                // allow full expansion in fullscreen
                fullscreenState->videoContainer->setParent(layer);
                fullscreenState->videoContainer->setMinimumHeight(0);
                fullscreenState->videoContainer->setMaximumHeight(QWIDGETSIZE_MAX);
                fullscreenState->videoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                fullscreenState->videoWidget->setMinimumHeight(0);
                fullscreenState->videoWidget->setMaximumHeight(QWIDGETSIZE_MAX);
                fullscreenState->videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                fullscreenState->videoContainer->setParent(layer);
                fullscreenState->videoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                layout->addWidget(fullscreenState->videoContainer, 1);
                QHBoxLayout *controlBar = new QHBoxLayout();
                controlBar->setContentsMargins(0, 0, 0, 0);
                controlBar->setSpacing(10);
                QSlider *fsProgress = new QSlider(Qt::Horizontal);
                fsProgress->setStyleSheet("QSlider::groove:horizontal { height:4px; background:#555; border-radius:2px; }"
                                          "QSlider::handle:horizontal { background:#ffffff; width:14px; margin:-6px 0; border-radius:7px; }");
                QToolButton *fsVolBtn = new QToolButton();
                fsVolBtn->setText(QStringLiteral("🔊"));
                fsVolBtn->setStyleSheet("QToolButton { border: none; padding:4px; font-size:14px; color:#ffffff; }");
                QSlider *fsVolume = new QSlider(Qt::Horizontal);
                fsVolume->setFixedWidth(80);
                fsVolume->setStyleSheet("QSlider::groove:horizontal { height:4px; background:#555; border-radius:2px; }"
                                        "QSlider::handle:horizontal { background:#ffffff; width:12px; margin:-6px 0; border-radius:6px; }");
                QComboBox *fsSpeed = new QComboBox();
                fsSpeed->addItem("0.5x", 0.5);
                fsSpeed->addItem("1.0x", 1.0);
                fsSpeed->addItem("1.25x", 1.25);
                fsSpeed->addItem("1.5x", 1.5);
                fsSpeed->setCurrentIndex(1);
                fsSpeed->setStyleSheet("QComboBox { padding:6px 10px; border:2px solid #ffffff; border-radius:10px; background:rgba(0,0,0,140); color:#ffffff; }");
                controlBar->addWidget(fsProgress, 1);
                controlBar->addWidget(fsVolBtn, 0, Qt::AlignVCenter);
                controlBar->addWidget(fsVolume, 0, Qt::AlignVCenter);
                controlBar->addWidget(fsSpeed, 0, Qt::AlignVCenter);
                QHBoxLayout *bottom = new QHBoxLayout();
                bottom->setContentsMargins(0, 0, 0, 0);
                bottom->addLayout(controlBar, 1);
                bottom->addStretch();
                QPushButton *exitBtn = new QPushButton(translate("Back"), layer);
                exitBtn->setStyleSheet("padding:10px 14px; border:2px solid #ffffff; border-radius:14px; background:rgba(0,0,0,160); color:#ffffff; font-weight:700;");
                bottom->addWidget(exitBtn, 0, Qt::AlignRight | Qt::AlignBottom);
                layout->addLayout(bottom);
                attachVideoControls(fullscreenState->player, fsProgress, fsVolume, fsSpeed, fsVolBtn);
                QObject::connect(exitBtn, &QPushButton::clicked, layer, [=]() {
                    exitFullScreen();
                });
                fullscreenState->overlayLayer = layer;
                layer->show();
                fullscreenState->videoContainer->raise();
                if (fullscreenState->player) fullscreenState->player->play();
            };

        } else {
            QFrame *ph = new QFrame();
            ph->setMinimumHeight(static_cast<int>(h * 0.4));
            ph->setStyleSheet("border:none; border-radius:14px; background:#f5f5f5;");
            QLabel *txt = new QLabel(translate("No video"), ph);
            txt->setAlignment(Qt::AlignCenter);
            txt->setStyleSheet("color:#7a7a7a; font-weight:700;");
            videoWrap = ph;
        }
        panelLayout->addWidget(videoWrap);
        attachVideoControls(modalPlayer, progressControl, volumeControl, speedControl);

        QHBoxLayout *userRow = new QHBoxLayout();
        userRow->setSpacing(10);
        userRow->setContentsMargins(0, 10, 0, 0);
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
        QHBoxLayout *infoAndControls = new QHBoxLayout();
        infoAndControls->setContentsMargins(0, 0, 0, 0);
        infoAndControls->setSpacing(12);
        infoAndControls->addLayout(userRow);
        infoAndControls->addStretch();
        if (mediaControls) {
            infoAndControls->addLayout(mediaControls, 1);
        }
        panelLayout->addLayout(infoAndControls);

        QHBoxLayout *actionRow = new QHBoxLayout();
        actionRow->setSpacing(12);
        QToolButton *likeBtn = new QToolButton();
        likeBtn->setCheckable(true);
        likeBtn->setChecked(fc.likedValue ? *fc.likedValue : false);
        likeBtn->setIcon(makeHeartIcon(fc.likedValue ? *fc.likedValue : false, 22));
        likeBtn->setStyleSheet("QToolButton { border:none; padding:8px; }");
        QLabel *likeCount = new QLabel(QString::number(fc.likeValue ? *fc.likeValue : 0));
        likeCount->setStyleSheet("font-weight:700; border:none; background:transparent;");
        likeCount->setFrameStyle(QFrame::NoFrame);
        actionRow->addWidget(likeBtn);
        actionRow->addWidget(likeCount);
        actionRow->addStretch();
        QToolButton *fullBtn = new QToolButton();
        fullBtn->setText("⛶");
        fullBtn->setStyleSheet("QToolButton { padding:8px 10px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:700; }");
        fullBtn->setEnabled(hasVideo);
        QObject::connect(fullBtn, &QToolButton::clicked, overlay, [enterFullScreen]() {
            enterFullScreen();
        });
        actionRow->addWidget(fullBtn);
        QToolButton *shareBtn = new QToolButton();
        shareBtn->setText(translate("Share"));
        shareBtn->setStyleSheet("QToolButton { padding:8px 14px; border:1px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:700; }");
        actionRow->addWidget(shareBtn);
        panelLayout->addLayout(actionRow);

        QLabel *chatTitle = new QLabel(translate("Live chat"));
        chatTitle->setStyleSheet("font-weight:800; font-size:14px;");
        panelLayout->addWidget(chatTitle);

        QVBoxLayout *chatList = new QVBoxLayout();
        chatList->setSpacing(10);
        QStringList sampleTexts = {
            translate("This angle looks fire."),
            translate("Where was this shot?"),
            translate("Drop the playlist please."),
            translate("I need this energy today.")
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

        QHBoxLayout *closeRow = new QHBoxLayout();
        closeRow->addStretch();
        QPushButton *closeBtn = new QPushButton(translate("Close"));
        closeBtn->setStyleSheet("padding:10px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#fdfdfd; font-weight:700;");
        closeRow->addWidget(closeBtn);
        panelLayout->addLayout(closeRow);

        overlayLayout->addWidget(panel, 0, Qt::AlignCenter);

        auto closeOverlay = [overlay, modalPlayer, &activeOverlay, exitFullScreen]() {
            exitFullScreen();
            if (modalPlayer) modalPlayer->stop();
            overlay->deleteLater();
            if (activeOverlay == overlay) activeOverlay = nullptr;
        };
        QObject::connect(closeBtn, &QPushButton::clicked, overlay, closeOverlay);
        DismissFilter *overlayTap = new DismissFilter(overlay);
        overlayTap->panel = panel;
        overlayTap->onDismiss = closeOverlay;
        overlay->installEventFilter(overlayTap);

        QObject::connect(likeBtn, &QToolButton::clicked, overlay, [=]() mutable {
            FeedCard fcCopy = fc;
            if (fcCopy.likedValue) *fcCopy.likedValue = likeBtn->isChecked();
            if (fcCopy.likeValue) {
                int v = *fcCopy.likeValue;
                v += (*fcCopy.likedValue) ? 1 : (v > 0 ? -1 : 0);
                *fcCopy.likeValue = qMax(0, v);
            }
            updateLikeUI(fcCopy);
            likeBtn->setIcon(makeHeartIcon(fcCopy.likedValue ? *fcCopy.likedValue : false, 22));
            likeCount->setText(QString::number(fcCopy.likeValue ? *fcCopy.likeValue : 0));
        });
        QObject::connect(shareBtn, &QToolButton::clicked, overlay, [fc, &showShareSheet, overlay, chatPage, chatContainer, rebuildFeed]() {
            showShareSheet(QStringLiteral("Share %1").arg(fc.account.handle), overlay, chatPage, chatContainer, rebuildFeed);
        });

        overlay->show();
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
    auto appendFeedCard = [&](TheButtonInfo *info, const FriendData &account, bool autoPlay) {
        FeedCard fc = createPhoneCard(info, account, autoPlay);
        feedCards.append(fc);
    };
    if (videos.size() > 0) {
        for (size_t i = 0; i < videos.size(); ++i) {
            const FriendData &publisher = friends.isEmpty() ? myProfile : friends.at(i % friends.size());
            bool autoPlay = (i == 0);
            appendFeedCard(&videos.at(i), publisher, autoPlay);
        }
    } else {
        appendFeedCard(nullptr, myProfile, true);
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

    auto playCard = [&](int idx) {
        for (int i = 0; i < feedCards.size(); ++i) {
            if (feedCards[i].player) {
                if (i == idx)
                    feedCards[i].player->play();
                else
                    feedCards[i].player->pause();
            }
        }
    };

    int lastColumns = -1;
    int lastWidth = -1;

    std::function<void()> rebuildPlayTaps = [&]() {
        for (int i = 0; i < feedCards.size(); ++i) {
            FeedCard &fc = feedCards[i];
            if (fc.video) {
                PlayTapFilter *tap = new PlayTapFilter(fc.video);
                tap->onClick = [=]() { playCard(i); };
                fc.video->installEventFilter(tap);
            }
        }
    };

    rebuildFeed = [&]() {
        clearGrid(feedLayout);
        int viewportWidth = feedArea->viewport()->width();

        // ensure that viewportWidth is valid
        if (viewportWidth <= 0) {
            viewportWidth = 360; // default width
        }

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
        rebuildPlayTaps();
    };

    ResizeWatcher *feedWatcher = new ResizeWatcher(feedArea);
    feedWatcher->onResize = rebuildFeed;
    feedArea->viewport()->installEventFilter(feedWatcher);
    rebuildFeed();

    auto prependFeedCard = [&](FeedCard fc) {
        feedCards.prepend(fc);
        rebuildFeed();
    };

    auto addUserPost = [&](bool isVideo) {
        (void)isVideo;
        FeedCard fc = createPhoneCard(nullptr, myProfile, false);
        if (fc.likeValue) *fc.likeValue = 0;
        if (fc.likedValue) *fc.likedValue = false;
        updateLikeUI(fc);
        prependFeedCard(fc);
        rebuildFeed();
        feedArea->viewport()->update();
        feedContent->updateGeometry();
        feedContent->adjustSize();
    };

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
    searchField = search;
    search->setPlaceholderText(translate("Add or search friends"));
    search->setStyleSheet("padding:10px 12px; border:none; border-radius:16px; background:#f2f2f2;");

    // static headers and containers
    QLabel *friendsTitle = new QLabel(translate("Friends"));
    friendsTitle->setStyleSheet("font-size:18px; font-weight:700;");
    QWidget *friendsCardsWrap = new QWidget();
    QVBoxLayout *friendsCardsLayout = new QVBoxLayout(friendsCardsWrap);
    friendsCardsLayout->setContentsMargins(0, 0, 0, 0);
    friendsCardsLayout->setSpacing(10);

    QLabel *popularTitle = new QLabel(translate("Recommend Accounts"));
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
        // safe cleaning
        while (QLayoutItem* child = layout->takeAt(0)) {
            if (QWidget* widget = child->widget()) {
                widget->deleteLater();
            }
            delete child;
        }
    };

    ChatWindow *chatPageInst = new ChatWindow();
    chatPage = chatPageInst;
    chatPageInst->setThreads(currentFriends);
    QObject::connect(chatPageInst, &ChatWindow::showProfile, &window, [=](const FriendData &f) {
        applyProfile(f);
        contentStack->setCurrentWidget(profilePage);
    });
    chatContainer = new QWidget();
    QVBoxLayout *chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setContentsMargins(12, 12, 12, 12);
    chatLayout->setSpacing(8);
    chatLayout->addWidget(chatPageInst);

    PostPage *postPage = new PostPage();
    postPageWidget = new QWidget();
    QVBoxLayout *postLayout = new QVBoxLayout(postPageWidget);
    postLayout->setContentsMargins(12, 12, 12, 12);
    postLayout->setSpacing(8);
    postLayout->addWidget(postPage);

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
            card->setStyleSheet("QFrame { background:#ffffff; border-radius:18px; }");
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
            avatarBtn->setStyleSheet("border:none; border-radius:28px; background:#fdfdfd;");
            cardLayout->addWidget(avatarBtn);

            QVBoxLayout *infoColumn = new QVBoxLayout();
            infoColumn->setContentsMargins(0, 0, 0, 0);
            infoColumn->setSpacing(2);
            QPushButton *nameBtn = new QPushButton(f.name);
            nameBtn->setFlat(true);
            nameBtn->setStyleSheet("text-align:left; font-weight:700; font-size:16px; color:#0b0b0b;");
            infoColumn->addWidget(nameBtn);
            QLabel *handleLbl = new QLabel(f.handle);
            handleLbl->setStyleSheet("font-size:13px; color:#5a5a5a;");
            infoColumn->addWidget(handleLbl);
            cardLayout->addLayout(infoColumn);
            cardLayout->addStretch();

            QPushButton *followBtn = new QPushButton();
            registerFollowButton(f.handle, followBtn);
            setFollowVisual(followBtn, followState.value(f.handle, isFriendList));
            if (isFriendList) followState.insert(f.handle, true);
            QObject::connect(followBtn, &QPushButton::clicked, &window, [=]() {
                handleFollowClick(f.handle);
            });
            cardLayout->addWidget(followBtn);
            if (isFriendList) {
                QPushButton *chatBtn = new QPushButton(translate("Chat"));
                chatBtn->setStyleSheet("padding:6px 12px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
                cardLayout->addWidget(chatBtn);
                QObject::connect(chatBtn, &QPushButton::clicked, &window, [=]() {
                    if (chatPage) chatPage->openThreadByIndex(idx);
                    contentStack->setCurrentWidget(chatContainer);
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
            QLabel *empty = new QLabel(translate("No results"));
            empty->setStyleSheet("color:#7a7a7a;");
            targetLayout->addWidget(empty);
        }
    };

    std::function<void(const QString&)> rebuildFriendsList = [&](const QString &filter) {
        renderCards(currentFriends, friendsCardsLayout, filter, true);
        renderCards(currentPopular, popularCardsLayout, filter, false);
    };

    refreshFriendsUI = [&]() {
        const QString filter = searchField ? searchField->text() : QString();
        rebuildFriendsList(filter);
        if (chatPage) chatPage->setThreads(currentFriends);
    };

    rebuildFriendsList(QString());
    friendsArea->setWidget(friendsListWrap);
    friendsLayout->addWidget(friendsArea);
    contentStack->addWidget(friendsPage);
    contentStack->addWidget(chatContainer);
    contentStack->addWidget(postPageWidget);

    // setting page
    SettingWindow *settingPage = new SettingWindow();
    contentStack->addWidget(settingPage);
    if (profileSettingsBtn) {
        QObject::connect(profileSettingsBtn, &QToolButton::clicked, &window, [=]() {
            settingPage->setUserProfile(myProfile);
            contentStack->setCurrentWidget(settingPage);
        });
    }
    QObject::connect(settingPage, &SettingWindow::shareProfileRequested, &window, [&]() {
        showShareSheet(QStringLiteral("Share %1").arg(myProfile.handle), &window, chatPage, chatContainer, rebuildFeed);
    });

    DetailWindow *detailPage = new DetailWindow();
    contentStack->addWidget(detailPage);

    QObject::connect(search, &QLineEdit::textChanged, &window, rebuildFriendsList);

    QObject::connect(postPage, &PostPage::backRequested, &window, [&]() {
        QWidget *target = lastPageBeforePost ? lastPageBeforePost : homePage;
        contentStack->setCurrentWidget(target);
    });
    QObject::connect(postPage, &PostPage::publishPhoto, &window, [&]() {
        addUserPost(false);
        contentStack->setCurrentWidget(homePage);
    });
    QObject::connect(postPage, &PostPage::publishVideo, &window, [&](int) {
        addUserPost(true);
        contentStack->setCurrentWidget(homePage);
    });

    // default profile content shows self
    applyProfile(myProfile);
    phoneLayout->addWidget(contentStack);

    
QWidget *navBar = new QWidget();
    QHBoxLayout *navLayout = new QHBoxLayout(navBar);
    navLayout->setSpacing(18);
    navLayout->setContentsMargins(0, 0, 0, 0);
    struct NavEntry {
        QString key;
        QString iconPath;
        QString iconPathDark;
        QPushButton *button = nullptr;
        std::function<void()> handler;
    };
    auto makeIcon = [](const QString &res, const QString &resDark, bool selected) -> QIcon {
        const QString path = selected ? resDark : res;
        QPixmap pm(path);
        if (pm.isNull()) return QIcon();
        return QIcon(pm);
    };
    QList<NavEntry> navItems;
    auto addNav = [&](const QString &key, const QString &icon, const QString &iconDark, const std::function<void()> &fn) {
        NavEntry e;
        e.key = key;
        e.iconPath = icon;
        e.iconPathDark = iconDark;
        e.handler = fn;
        navItems.append(e);
    };
    addNav("home", ":/assets/UIHome.png", ":/assets/UIHome_dark.png", [&]() { rebuildFeed(); contentStack->setCurrentWidget(homePage); });
    addNav("friends", ":/assets/UIFriends.png", ":/assets/UIFriends_dark.png", [&]() { contentStack->setCurrentWidget(friendsPage); });
    addNav("post", ":/assets/UIPost.png", ":/assets/UIPost_dark.png", [&]() { lastPageBeforePost = contentStack->currentWidget(); contentStack->setCurrentWidget(postPageWidget); });
    addNav("chat", ":/assets/UIChat.png", ":/assets/UIChat_dark.png", [&]() { contentStack->setCurrentWidget(chatContainer); });
    addNav("profile", ":/assets/UIProfile.png", ":/assets/UIProfile_dark.png", [&]() { applyProfile(myProfile); contentStack->setCurrentWidget(profilePage); });
    auto syncNavState = [&](const QString &activeKey) {
        for (NavEntry &entry : navItems) {
            if (!entry.button) continue;
            const bool active = (entry.key == activeKey);
            entry.button->setIcon(makeIcon(entry.iconPath, entry.iconPathDark, active));
        }
    };
    for (NavEntry &entry : navItems) {
        QPushButton *navButton = new QPushButton();
        navButton->setFlat(true);
        navButton->setCheckable(false);
        navButton->setIcon(makeIcon(entry.iconPath, entry.iconPathDark, false));
        navButton->setIconSize(QSize(34, 34));
        navButton->setStyleSheet("QPushButton { border: none; padding: 6px; }");
        entry.button = navButton;
        navLayout->addWidget(navButton);
        QObject::connect(navButton, &QPushButton::clicked, &window, [&, entry]() {
            if (entry.handler) entry.handler();
            syncNavState(entry.key);
        });
    }
    syncNavState("home");
QObject::connect(settingPage, &SettingWindow::backToHome, &window, [=]() {
        contentStack->setCurrentWidget(profilePage);
    });

    QObject::connect(settingPage, &SettingWindow::openDetail, &window, [=](const QString& title, const QString& category) {
        Q_UNUSED(category);
        detailPage->setupContent(title);
        contentStack->setCurrentWidget(detailPage);
    });

    QObject::connect(detailPage, &DetailWindow::backClicked, &window, [=]() {
        contentStack->setCurrentWidget(settingPage);
    });

    // back from profile to friends
    QObject::connect(backToFriends, &QPushButton::clicked, &window, [=]() {
        contentStack->setCurrentWidget(friendsPage);
    });

    QObject::connect(detailPage, &DetailWindow::languageSelected, &window, [&](const QString& lang) {
        switchLanguage(lang);
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
