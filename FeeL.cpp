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
#include <QHash>
#include <functional>
#include <QtCore/QString>
#include <QEvent>
#include <QMouseEvent>
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
        const int result = QMessageBox::information(
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

    for (const auto &f : friends) friendLookup.insert(f.handle, f);
    currentFriends = friends.mid(0, 3);
    currentPopular = friends.mid(3);
    for (const auto &f : currentFriends) followState.insert(f.handle, true);

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

<<<<<<< Updated upstream
=======
    QLabel *profileHandleLabel = nullptr;
    QLabel *profileFollowStatusLabel = nullptr;
    QLineEdit *searchField = nullptr;
    ChatWindow *chatPage = nullptr;

    QList<FriendData> currentFriends;
    QList<FriendData> currentPopular;
    QHash<QString, FriendData> friendLookup;

    // global follow state registry
    QHash<QString, bool> followState;
    QHash<QString, QList<QPushButton*>> followButtons;
    auto setFollowVisual = [&](QPushButton *btn, bool followed) {
        if (!btn) return;
        if (followed) {
            btn->setText("Followed");
            btn->setEnabled(false);
            btn->setStyleSheet("padding:6px 14px; border:1px solid #101010; border-radius:16px; background:#e9e9e9; font-weight:600; color:#5a5a5a;");
        } else {
            btn->setText("Follow");
            btn->setEnabled(true);
            btn->setStyleSheet("padding:6px 14px; border:1px solid #101010; border-radius:16px; background:#ffffff; font-weight:600; color:#0b0b0b;");
        }
    };

    auto syncFollowButtons = [&](const QString &handle) {
        const bool followed = followState.value(handle, false);
        if (followButtons.contains(handle)) {
            for (QPushButton *b : followButtons.value(handle)) {
                setFollowVisual(b, followed);
            }
        }
        if (profileHandleLabel && profileHandleLabel->text() == handle && profileFollowStatusLabel) {
            if (handle == myProfile.handle) {
                profileFollowStatusLabel->setVisible(false);
            } else {
                profileFollowStatusLabel->setVisible(true);
                profileFollowStatusLabel->setText(followed ? "Followed" : "Follow");
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

>>>>>>> Stashed changes
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
    profileHandleLabel = profileHandle;
    profileHandle->setStyleSheet("font-size:14px; color:#666;");
    profileLayout->addWidget(profileHandle, 0, Qt::AlignHCenter);

<<<<<<< Updated upstream
=======
    QLabel *profileFollowStatus = new QLabel();
    profileFollowStatusLabel = profileFollowStatus;
    profileFollowStatus->setStyleSheet("font-size:13px; color:#444; border:2px solid #0b0b0b; border-radius:12px; padding:6px 10px; background:#ffffff;");
    profileLayout->addWidget(profileFollowStatus, 0, Qt::AlignHCenter);

>>>>>>> Stashed changes
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

    QLabel *privacyNote = new QLabel("Your Posts are private and ephemeral unless shared.");
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
<<<<<<< Updated upstream
=======
        if (f.name == myProfile.name) {
            profileFollowStatus->setText("This is you");
            profileFollowStatus->setVisible(false);
        } else {
            const bool followed = followState.value(f.handle, false);
            profileFollowStatus->setVisible(true);
            profileFollowStatus->setText(followed ? "Followed" : "Follow");
        }
>>>>>>> Stashed changes
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
    };

    // home page cards showing friend accounts as publishers
    auto createPhoneCard = [&](TheButtonInfo* info, const FriendData &account, bool autoPlay) -> FeedCard {
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
            cardVideo->setStyleSheet("border:2px solid #101010; border-radius:16px; background:#050505;");
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
                cardPlayer->setPosition(0); // force first frame for preview
            }
            mediaSurface = cardVideo;
        } else {
            QFrame *placeholder = new QFrame();
            placeholder->setMinimumHeight(260);
            placeholder->setStyleSheet("border:2px solid #101010; border-radius:16px; background:#f7f7f7;");
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
        avatarBtn->setStyleSheet("border:2px solid #101010; border-radius:22px; background:#fdfdfd;");
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
<<<<<<< Updated upstream
        QPushButton *followButton = new QPushButton("FOLLOW");
        followButton->setStyleSheet("QPushButton { border:2px solid #101010; border-radius:16px; padding:4px 16px; background:#ffffff; font-weight:600; }");
=======
        QPushButton *followButton = new QPushButton();
        followButtons[account.handle].append(followButton);
        setFollowVisual(followButton, followState.value(account.handle, false));
        QObject::connect(followButton, &QPushButton::clicked, &window, [=]() {
            handleFollowClick(account.handle);
        });
>>>>>>> Stashed changes
        profileRow->addWidget(avatarBtn);
        profileRow->addLayout(profileText);
        profileRow->addStretch();
        profileRow->addWidget(followButton);
        cardLayout->addLayout(profileRow);

        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setStyleSheet("color:#cfcfcf;");
        cardLayout->addWidget(line);

        QHBoxLayout *statsRow = new QHBoxLayout();
        statsRow->setSpacing(16);
        statsRow->addWidget(new QLabel("LIKE 123"));
        statsRow->addWidget(new QLabel("CHAT 45"));
        statsRow->addStretch();
        QLabel *shareIcon = new QLabel("SHARE");
        statsRow->addWidget(shareIcon);
        cardLayout->addLayout(statsRow);

        QFrame *commentLine = new QFrame();
        commentLine->setFrameShape(QFrame::HLine);
        commentLine->setStyleSheet("color:#cfcfcf;");
        cardLayout->addWidget(commentLine);

        QVBoxLayout *commentSection = new QVBoxLayout();
        commentSection->setSpacing(8);
        QLabel *commentLabel = new QLabel("Comments");
<<<<<<< Updated upstream
        commentLabel->setStyleSheet("font-weight:600; color:#0b0b0b;");
=======
        commentLabel->setStyleSheet("font-weight:700; color:#0b0b0b;");
        QFrame *commentLine = new QFrame();
        commentLine->setFrameShape(QFrame::HLine);
        commentLine->setStyleSheet("color:#e4e4e4;");
        commentSection->addWidget(commentLine);
>>>>>>> Stashed changes
        commentSection->addWidget(commentLabel);

        QVBoxLayout *commentsList = new QVBoxLayout();
        commentsList->setContentsMargins(0, 0, 0, 0);
        commentsList->setSpacing(8);
        commentSection->addLayout(commentsList);

        QLineEdit *commentInput = new QLineEdit();
        commentInput->setPlaceholderText("Add a comment...");
        commentInput->setStyleSheet("padding:8px 10px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff;");
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
            avatarLbl->setStyleSheet("border:2px solid #0b0b0b; border-radius:14px;");
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
        };
        QObject::connect(commentInput, &QLineEdit::returnPressed, &window, addComment);

        cardLayout->addLayout(commentSection);

        FeedCard fc;
        fc.widget = card;
        fc.player = cardPlayer;
        fc.video = cardVideo;
        return fc;
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
    if (videos.size() > 0) {
        for (size_t i = 0; i < videos.size(); ++i) {
            const FriendData &publisher = friends.isEmpty() ? myProfile : friends.at(i % friends.size());
            bool autoPlay = (i == 0);
            feedCards.append(createPhoneCard(&videos.at(i), publisher, autoPlay));
        }
    } else {
        feedCards.append(createPhoneCard(nullptr, myProfile, true));
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

    // add play handlers for toggling playback on click
    for (int i = 0; i < feedCards.size(); ++i) {
        FeedCard &fc = feedCards[i];
        if (fc.video) {
            PlayTapFilter *tap = new PlayTapFilter(fc.video);
            tap->onClick = [=]() { playCard(i); };
            fc.video->installEventFilter(tap);
        }
    }
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

<<<<<<< Updated upstream
    QList<FriendData> friendSubset = friends.mid(0, 3);
    QList<FriendData> popularSubset = friends.mid(3); // disjoint from friends
=======
    ChatWindow *chatPageInst = new ChatWindow();
    chatPage = chatPageInst;
    chatPageInst->setThreads(currentFriends);
    QObject::connect(chatPageInst, &ChatWindow::showProfile, &window, [=](const FriendData &f) {
        applyProfile(f);
        contentStack->setCurrentWidget(profilePage);
    });
>>>>>>> Stashed changes

    auto renderCards = [&](const QList<FriendData> &list, QVBoxLayout *targetLayout, const QString &filter, bool isFriendList) {
        clearLayoutWithWidgets(targetLayout);
        const bool hasFilter = !filter.trimmed().isEmpty();
        int added = 0;
        for (const auto &f : list) {
            if (hasFilter) {
                const QString text = filter.trimmed();
                if (!f.name.contains(text, Qt::CaseInsensitive) &&
                    !f.handle.contains(text, Qt::CaseInsensitive)) {
                    continue;
                }
            }
            ++added;
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
            infoColumn->setSpacing(2);
            QPushButton *nameBtn = new QPushButton(f.name);
            nameBtn->setFlat(true);
            nameBtn->setStyleSheet("text-align:left; font-weight:700; font-size:16px; color:#0b0b0b;");
            infoColumn->addWidget(nameBtn);
            QLabel *handleLbl = new QLabel(f.handle);
            handleLbl->setStyleSheet("font-size:13px; color:#5a5a5a;");
            infoColumn->addWidget(handleLbl);
<<<<<<< Updated upstream
            QLabel *followersLbl = new QLabel(f.followers);
            followersLbl->setStyleSheet("font-size:12px; color:#7a7a7a;");
            infoColumn->addWidget(followersLbl);
=======
>>>>>>> Stashed changes
            cardLayout->addLayout(infoColumn);
            cardLayout->addStretch();

            QPushButton *followBtn = new QPushButton();
            followButtons[f.handle].append(followBtn);
            setFollowVisual(followBtn, followState.value(f.handle, isFriendList));
            if (isFriendList) followState.insert(f.handle, true);
            QObject::connect(followBtn, &QPushButton::clicked, &window, [=]() {
                handleFollowClick(f.handle);
            });
            cardLayout->addWidget(followBtn);
<<<<<<< Updated upstream
=======
            if (isFriendList) {
                QPushButton *chatBtn = new QPushButton("Chat");
                chatBtn->setStyleSheet("padding:6px 12px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:600;");
                cardLayout->addWidget(chatBtn);
                QObject::connect(chatBtn, &QPushButton::clicked, &window, [=]() {
                    if (chatPage) chatPage->openThreadByIndex(idx);
                    contentStack->setCurrentWidget(chatPage);
                });
            }
>>>>>>> Stashed changes

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
