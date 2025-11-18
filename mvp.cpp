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
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_button.h"

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
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::information(
                    NULL,
                    QString("MVP"),
                    QString("no videos found! Add command line argument to \"quoted\" file location."));
        exit(-1);
    }

    // helper lambdas to recreate the phone-style mock
    auto createPhoneCard = [&](TheButtonInfo* info) -> QWidget* {
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background:#ffffff; border:2px solid #101010; border-radius:28px; }");
        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setSpacing(12);
        cardLayout->setContentsMargins(18, 18, 18, 18);

        QWidget *mediaSurface = nullptr;
        if (info != nullptr) {
            QVideoWidget *cardVideo = new QVideoWidget(card);
            cardVideo->setMinimumHeight(260);
            cardVideo->setStyleSheet("border:2px solid #101010; border-radius:16px; background:#050505;");
            QMediaPlayer *cardPlayer = new QMediaPlayer(cardVideo);
            QMediaPlaylist *loop = new QMediaPlaylist(cardPlayer);
            loop->addMedia(*info->url);
            loop->setPlaybackMode(QMediaPlaylist::Loop);
            cardPlayer->setPlaylist(loop);
            cardPlayer->setVideoOutput(cardVideo);
            cardPlayer->play();
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

        QHBoxLayout *profileRow = new QHBoxLayout();
        profileRow->setSpacing(10);
        QFrame *avatar = new QFrame();
        avatar->setFixedSize(44, 44);
        avatar->setStyleSheet("border:2px solid #101010; border-radius:22px;");
        QVBoxLayout *profileText = new QVBoxLayout();
        profileText->setContentsMargins(0, 0, 0, 0);
        profileText->setSpacing(2);
        QString handleText = "@Creator";
        QString titleText = "Video Title";
        if (info != nullptr) {
            QFileInfo fileInfo(info->url->toLocalFile());
            handleText = QString("@%1").arg(fileInfo.completeBaseName());
            titleText = fileInfo.completeBaseName();
        }
        profileText->addWidget(new QLabel(handleText));
        QLabel *title = new QLabel(titleText);
        profileText->addWidget(title);
        QPushButton *followButton = new QPushButton("FOLLOW");
        followButton->setStyleSheet("QPushButton { border:2px solid #101010; border-radius:16px; padding:4px 16px; background:#ffffff; }");
        profileRow->addWidget(avatar);
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

        QLabel *commentSlot = new QLabel("Comment thread");
        commentSlot->setStyleSheet("color:#6a6a6a;");
        cardLayout->addWidget(commentSlot);

        return card;
    };

    // create the main window with a centered phone mock
    QWidget window;
    window.setWindowTitle("MVP");
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
    QLabel *logo = new QLabel("MVP");
    logo->setStyleSheet("font-weight:700; letter-spacing:4px;");
    headerLayout->addWidget(logo);
    headerLayout->addStretch();
    QFrame *square = new QFrame();
    square->setFixedSize(30, 30);
    square->setStyleSheet("border:2px solid #0b0b0b; border-radius:8px;");
    headerLayout->addWidget(square);
    phoneLayout->addWidget(header);

    QScrollArea *feedArea = new QScrollArea();
    feedArea->setFrameShape(QFrame::NoFrame);
    feedArea->setWidgetResizable(true);
    QWidget *feedContent = new QWidget();
    QVBoxLayout *feedLayout = new QVBoxLayout(feedContent);
    feedLayout->setSpacing(18);
    if (videos.size() > 0) {
        for (size_t i = 0; i < videos.size(); ++i) {
            feedLayout->addWidget(createPhoneCard(&videos.at(i)));
        }
    } else {
        feedLayout->addWidget(createPhoneCard(nullptr));
    }
    feedLayout->addStretch();
    feedArea->setWidget(feedContent);
    phoneLayout->addWidget(feedArea);

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
    }
    phoneLayout->addWidget(navBar);

    root->addWidget(phone);
    root->addStretch();

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
