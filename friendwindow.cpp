#include "friendwindow.h"

Friendwindow::Friendwindow(QWidget *parent)
    : QWidget{parent}
{
    // window size
    resize(375, 667);
    setWindowTitle("friend list");

    // main window width and length
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // label , title
    QLabel *title = new QLabel("friends", this);
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
    m_friends.append({"Tom", "like hunting"});
    m_friends.append({"Aile", "like swimming"});
    m_friends.append({"Charlie", "No hobbies"});
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
