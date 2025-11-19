#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "friends_data.h"

class Profilewindow : public QWidget {
    Q_OBJECT
public:
    explicit Profilewindow(QWidget *parent = nullptr);
    void setProfileInfo(const FriendData& data); // set individual data

signals:
    void BackToFriends(); // return to friend window

    //display of name and biofile
private:
    QLabel *m_nameLabel; // name
    QLabel *m_bioLabel;  // individual biofile
};

#endif // PROFILEWIDGET_H
