#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include "friends_data.h"

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    void setUserProfile(const FriendData& profile);

signals:
    void backToHome();
    void openDetail(const QString& title, const QString& category);
    void languageSelected(const QString& langCode);
    void shareProfileRequested();
// private slots:
//     void onButtonClicked();

private:
    void setupUI();
    // QPushButton* createSettingButton(const QString& text, const QString& objectName);

    FriendData m_profile;
    QLabel *m_avatarLabel = nullptr;
    QLabel *m_nameLabel = nullptr;
    QLabel *m_handleLabel = nullptr;

};

#endif
