#ifndef POSTPAGE_H
#define POSTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QTimer>
#include <QElapsedTimer>

class PostPage : public QWidget {
    Q_OBJECT
public:
    explicit PostPage(QWidget *parent = nullptr);

signals:
    void backRequested();
    void publishPhoto();
    void publishVideo(int durationMs);

private slots:
    void onCapturePressed();
    void onTogglePhoto();
    void onToggleVideo();
    void onOpenAlbum();

private:
    enum class Mode { Photo, Video };
    Mode currentMode = Mode::Photo;
    bool recording = false;
    QTimer timer;
    QElapsedTimer elapsed;

    QLabel *modeLabel = nullptr;
    QLabel *timerLabel = nullptr;
    QPushButton *photoBtn = nullptr;
    QPushButton *videoBtn = nullptr;
    QPushButton *captureBtn = nullptr;
    QWidget *confirmOverlay = nullptr;
    QWidget *albumOverlay = nullptr;

    void updateModeStyles();
    void showPublishOverlay(bool isVideo);
    void showAlbumOverlay();
    void resetRecording();
};

#endif // POSTPAGE_H
