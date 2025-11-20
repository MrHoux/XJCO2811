#ifndef FRIENDSWIDGET_H
#define FRIENDSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include "friends_data.h"
#include "profilewindow.h"

class Friendwindow : public QWidget {
    Q_OBJECT
public:
    explicit Friendwindow(QWidget *parent = nullptr);

private slots:
    void onFriendClicked(QListWidgetItem *item); // click the friend button
private:
    QListWidget *m_friendList; // friend list
    QList<FriendData> m_friends; // friend data
    Profilewindow *m_profilewindow; // relative friend's profilewindow
};

#endif // FRIENDSWIDGET_H
