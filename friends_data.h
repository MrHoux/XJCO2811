#ifndef FRIENDS_DATA_H
#define FRIENDS_DATA_H


#include <QString>


struct FriendData {
    QString name; // friends'name
    QString bio;  // friends' individual profile

    explicit FriendData(const QString &n, const QString &b)
        : name(n), bio(b) {}       // avoid the error
};

#endif // FRIENDS_DATA_H
