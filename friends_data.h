#ifndef FRIENDS_DATA_H
#define FRIENDS_DATA_H


#include <QString>
#include <QList>


struct FriendData {
    QString name;       // display name
    QString handle;     // @handle
    QString bio;        // profile bio
    QString followers;  // follower text
    QString avatar;     // qrc path to avatar image
    int bereals = 0;
    int friends = 0;
    int following = 0;
    QList<QString> gallery; // optional gallery image paths

    FriendData() = default;
    FriendData(const QString &n,
               const QString &h,
               const QString &b,
               const QString &followerText,
               const QString &avatarPath,
               int berealCount,
               int friendsCount,
               int followingCount,
               const QList<QString> &galleryPaths = {})
        : name(n),
          handle(h),
          bio(b),
          followers(followerText),
          avatar(avatarPath),
          bereals(berealCount),
          friends(friendsCount),
          following(followingCount),
          gallery(galleryPaths) {}
};

#endif // FRIENDS_DATA_H
