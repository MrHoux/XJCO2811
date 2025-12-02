//
// Chat window for quick messaging mock
//

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QList>
#include "friends_data.h"

class ChatWindow : public QWidget {
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    void setThreads(const QList<FriendData> &friends);
    void openThreadByIndex(int index);
    void sendShareMessage(int index, const QString &text = QStringLiteral("share message"));

signals:
    void showProfile(const FriendData &f);

private:
    struct Message {
        bool outgoing;
        QString text;
    };

    QStackedWidget *stack;
    QWidget *listPage;
    QWidget *threadPage;
    QVBoxLayout *threadLayout;
    QLabel *threadTitle;
    QLabel *threadHandle;
    QLabel *threadAvatar;
    QLineEdit *input;
    QVBoxLayout *listWrapLayout = nullptr;

    QList<FriendData> threads;
    QHash<int, QList<Message>> threadHistories;
    int currentThreadIndex = -1;

    QWidget* buildThreadBubble(const Message &m);
    void rebuildThreadView();
    void openThread(int index);
    QPixmap makeAvatarPixmap(const QString &path, int size);

    QPixmap createDefaultAvatar(int size);
};

#endif // CHATWINDOW_H
