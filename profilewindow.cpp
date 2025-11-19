#include "profilewindow.h"

Profilewindow::Profilewindow(QWidget *parent)
    : QWidget{parent}
{
   // the window size is the same as    Friends
    resize(375, 667);
    setWindowTitle("personal profile");

    // main window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(40);

    // return button style
    QPushButton *backBtn = new QPushButton("返回", this);
    backBtn->setStyleSheet("padding: 8px 16px; background: #e0e0e0; border: none; border-radius: 4px;");
    mainLayout->addWidget(backBtn, 0, Qt::AlignLeft);

    // display of name
    m_nameLabel = new QLabel(this);
    m_nameLabel->setStyleSheet("font-size: 22px; font-weight: bold; text-align: center;");
    mainLayout->addWidget(m_nameLabel, 0, Qt::AlignCenter);

    // display of profile
    m_bioLabel = new QLabel(this);
    m_bioLabel->setStyleSheet("font-size: 15px; color: #666; text-align: center;");
    mainLayout->addWidget(m_bioLabel, 0, Qt::AlignCenter);

    // back single
    connect(backBtn, &QPushButton::clicked, this, &Profilewindow::BackToFriends);
}

// set individual data
void Profilewindow::setProfileInfo(const FriendData& data) {
    m_nameLabel->setText(data.name);
    m_bioLabel->setText(data.bio.isEmpty() ? "no profile" : data.bio);
}
