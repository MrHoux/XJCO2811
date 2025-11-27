#include "profilewindow.h"

Profilewindow::Profilewindow(QWidget *parent)
    : QWidget{parent}
{
    // match the friends window size
    resize(375, 667);
    setWindowTitle("personal profile");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(40);

    QPushButton *backBtn = new QPushButton("返回", this);
    backBtn->setStyleSheet("padding: 8px 16px; background: #e0e0e0; border: none; border-radius: 4px;");
    mainLayout->addWidget(backBtn, 0, Qt::AlignLeft);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setStyleSheet("font-size: 22px; font-weight: bold; text-align: center;");
    mainLayout->addWidget(m_nameLabel, 0, Qt::AlignCenter);

    m_bioLabel = new QLabel(this);
    m_bioLabel->setStyleSheet("font-size: 15px; color: #666; text-align: center;");
    mainLayout->addWidget(m_bioLabel, 0, Qt::AlignCenter);

    connect(backBtn, &QPushButton::clicked, this, &Profilewindow::BackToFriends);
}

void Profilewindow::setProfileInfo(const FriendData& data) {
    m_nameLabel->setText(data.name);
    m_bioLabel->setText(data.bio.isEmpty() ? "no profile" : data.bio);
}
