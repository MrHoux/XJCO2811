#include "friendwindow.h"
#include <QApplication>

extern QString currentLanguage;
extern QString translate(const QString& text);

Friendwindow::Friendwindow(QWidget *parent)
    : QWidget{parent}
{
    // window size
    resize(375, 667);
    setWindowTitle(translate("friend list"));

    // main window width and length
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // label , title
    QLabel *title = new QLabel(translate("friends"), this);
    title->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center; background: #f0f0f0; height: 40px; line-height: 40px;");
    mainLayout->addWidget(title);

    // friend list     (name)
    m_friendList = new QListWidget(this);
    m_friendList->setStyleSheet("font-size: 16px; padding: 10px;");
    mainLayout->addWidget(m_friendList);

    // new profile window
    m_profilewindow = new Profilewindow();

    // from Profile to Friends   single
    connect(m_profilewindow, &Profilewindow::BackToFriends, this, [=]() {
        m_profilewindow->hide();
        this->show();
    });

    // add the testing friend
    m_friends.append(FriendData(QStringLiteral("Tom"),
                                QStringLiteral("@tom"),
                                QStringLiteral("like hunting"),
                                QStringLiteral("Followed by 2k people"),
                                QStringLiteral(":/avatars/avatar1.jpg"),
                                5, 12, 18));
    m_friends.append(FriendData(QStringLiteral("Aile"),
                                QStringLiteral("@aile"),
                                QStringLiteral("like swimming"),
                                QStringLiteral("Followed by 3k people"),
                                QStringLiteral(":/avatars/avatar2.jpg"),
                                8, 20, 24));
    m_friends.append(FriendData(QStringLiteral("Charlie"),
                                QStringLiteral("@charlie"),
                                QStringLiteral("No hobbies"),
                                QStringLiteral("Followed by 1k people"),
                                QStringLiteral(":/avatars/avatar3.jpg"),
                                2, 7, 10));
    for (const auto& friendData : m_friends) {
        new QListWidgetItem(friendData.name, m_friendList);
    }

    // when click the friend
    connect(m_friendList, &QListWidget::itemClicked, this, &Friendwindow::onFriendClicked);
}

// click friend ：hide the friend window，show the profile window
void Friendwindow::onFriendClicked(QListWidgetItem *item) {
    int index = m_friendList->row(item);
    if (index >= 0 && index < m_friends.size()) {
        m_profilewindow->setProfileInfo(m_friends[index]);
        this->hide();
        m_profilewindow->show();
    }
}
