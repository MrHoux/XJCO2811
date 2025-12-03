#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QWidget>

class QVBoxLayout;
class QLabel;
class QPushButton;
class QScrollArea;

class DetailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWindow(QWidget *parent = nullptr);
    void setupContent(const QString& title);
signals:
    void backClicked();
    void languageSelected(const QString& langCode);
private:
    QString m_title;

    void setupAudioContent(QVBoxLayout *layout);
    void setupNotificationsContent(QVBoxLayout *layout);
    void setupPrivacyContent(QVBoxLayout *layout);
    void setupTimezoneContent(QVBoxLayout *layout);
    void setupOtherContent(QVBoxLayout *layout);
    void setupShareContent(QVBoxLayout *layout);
    void setupRateContent(QVBoxLayout *layout);
    void setupHelpContent(QVBoxLayout *layout);
    void setupAboutContent(QVBoxLayout *layout);
};

#endif // DETAILWINDOW_H
