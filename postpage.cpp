#include "postpage.h"
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>

extern QString translate(const QString& text);

// Construct the post creation UI with camera controls.
PostPage::PostPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(10);

    QHBoxLayout *top = new QHBoxLayout();
    QPushButton *back = new QPushButton(QStringLiteral("ˇ"));
    back->setFixedSize(36, 28);
    back->setStyleSheet("padding:6px 8px; border:2px solid #0b0b0b; border-radius:10px; background:#ffffff; font-size:16px; font-weight:700;");
    connect(back, &QPushButton::clicked, this, &PostPage::backRequested);
    QLabel *title = new QLabel(QStringLiteral("FeeL."));
    title->setStyleSheet("font-size:18px; font-weight:700;");
    top->addWidget(back, 0, Qt::AlignLeft);
    top->addStretch();
    top->addWidget(title, 0, Qt::AlignCenter);
    top->addStretch();
    root->addLayout(top);

    QFrame *preview = new QFrame();
    preview->setMinimumHeight(260);
    preview->setStyleSheet("background:#cfcfcf; border-radius:20px;");
    QVBoxLayout *previewLayout = new QVBoxLayout(preview);
    previewLayout->setContentsMargins(0, 0, 0, 0);
    previewLayout->addStretch();
    QLabel *zoom = new QLabel(QStringLiteral("1.0x"));
    zoom->setStyleSheet("background:#0b0b0b; color:#ffffff; padding:6px 10px; border-radius:14px; font-weight:700;");
    previewLayout->addWidget(zoom, 0, Qt::AlignCenter | Qt::AlignBottom);
    root->addWidget(preview);

    QHBoxLayout *modeRow = new QHBoxLayout();
    modeRow->setSpacing(12);
    modeRow->addStretch();
    videoBtn = new QPushButton(translate("Video"));
    photoBtn = new QPushButton(translate("Photo"));
    videoBtn->setCheckable(true);
    photoBtn->setCheckable(true);
    connect(videoBtn, &QPushButton::clicked, this, &PostPage::onToggleVideo);
    connect(photoBtn, &QPushButton::clicked, this, &PostPage::onTogglePhoto);
    modeRow->addWidget(videoBtn);
    modeRow->addWidget(photoBtn);
    modeRow->addStretch();
    root->addLayout(modeRow);

    QHBoxLayout *controls = new QHBoxLayout();
    controls->setSpacing(20);
    QPushButton *albumBtn = new QPushButton();
    albumBtn->setFixedSize(42, 42);
    albumBtn->setStyleSheet("background:#e0e0e0; border:2px solid #0b0b0b; border-radius:8px;");
    connect(albumBtn, &QPushButton::clicked, this, &PostPage::onOpenAlbum);
    controls->addWidget(albumBtn, 0, Qt::AlignCenter);

    QVBoxLayout *captureCol = new QVBoxLayout();
    captureCol->setSpacing(6);
    modeLabel = new QLabel(translate("Photo"));
    modeLabel->setStyleSheet("font-size:12px; color:#444;");
    modeLabel->setAlignment(Qt::AlignCenter);
    captureCol->addWidget(modeLabel, 0, Qt::AlignCenter);
    captureBtn = new QPushButton();
    captureBtn->setFixedSize(72, 72);
    captureBtn->setStyleSheet("background:#ffffff; border:6px solid #0b0b0b; border-radius:36px;");
    connect(captureBtn, &QPushButton::clicked, this, &PostPage::onCapturePressed);
    captureCol->addWidget(captureBtn, 0, Qt::AlignCenter);
    timerLabel = new QLabel("00:00");
    timerLabel->setStyleSheet("font-size:12px; color:#666;");
    timerLabel->setAlignment(Qt::AlignCenter);
    captureCol->addWidget(timerLabel, 0, Qt::AlignCenter);
    controls->addLayout(captureCol);

    QLabel *refresh = new QLabel(QStringLiteral("↻"));
    refresh->setStyleSheet("font-size:20px; font-weight:800;");
    controls->addWidget(refresh, 0, Qt::AlignCenter);
    root->addLayout(controls);

    timer.setInterval(200);
    connect(&timer, &QTimer::timeout, this, [=]() {
        if (!recording) return;
        const qint64 ms = elapsed.elapsed();
        const int secs = static_cast<int>(ms / 1000);
        timerLabel->setText(QString("%1:%2")
                            .arg(secs / 60, 2, 10, QChar('0'))
                            .arg(secs % 60, 2, 10, QChar('0')));
    });

    onTogglePhoto();
}

// Update button visuals based on current capture mode.
void PostPage::updateModeStyles() {
    auto styleBtn = [](QPushButton *btn, bool active) {
        if (!btn) return;
        btn->setChecked(active);
        btn->setStyleSheet(active
                           ? "padding:6px 14px; border:2px solid #0b0b0b; border-radius:14px; background:#ffffff; font-weight:700;"
                           : "padding:6px 14px; border:2px solid #c7c7c7; border-radius:14px; background:#f7f7f7; color:#555;");
    };
    styleBtn(photoBtn, currentMode == Mode::Photo);
    styleBtn(videoBtn, currentMode == Mode::Video);
    if (modeLabel) modeLabel->setText(currentMode == Mode::Photo ? translate("Photo") : translate("Video"));
}

// Reset recording timers and flags.
void PostPage::resetRecording() {
    recording = false;
    timer.stop();
    timerLabel->setText("00:00");
}

// Show a mock album picker overlay.
void PostPage::showAlbumOverlay() {
    if (albumOverlay) {
        albumOverlay->deleteLater();
        albumOverlay = nullptr;
    }
    albumOverlay = new QWidget(this);
    albumOverlay->setObjectName("albumOverlay");
    albumOverlay->setStyleSheet("#albumOverlay { background:rgba(0,0,0,120); }");
    albumOverlay->setGeometry(rect());
    albumOverlay->raise();
    QVBoxLayout *outer = new QVBoxLayout(albumOverlay);
    outer->setContentsMargins(16, 16, 16, 16);
    QFrame *panel = new QFrame();
    panel->setStyleSheet("background:#ffffff; border-radius:16px;");
    QVBoxLayout *p = new QVBoxLayout(panel);
    p->setSpacing(10);
    p->setContentsMargins(16, 16, 16, 16);
    QLabel *title = new QLabel(translate("Photo"));
    title->setStyleSheet("font-weight:800; font-size:16px;");
    p->addWidget(title);
    QLabel *body = new QLabel(translate("Open album? (mock)"));
    body->setWordWrap(true);
    body->setStyleSheet("color:#444;");
    p->addWidget(body);
    QHBoxLayout *btns = new QHBoxLayout();
    btns->addStretch();
    QPushButton *cancel = new QPushButton(translate("Cancel"));
    cancel->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:700;");
    QPushButton *ok = new QPushButton(translate("Open"));
    ok->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:12px; background:#f0f0f0; font-weight:700;");
    btns->addWidget(cancel);
    btns->addWidget(ok);
    p->addLayout(btns);
    outer->addWidget(panel, 0, Qt::AlignCenter);
    connect(cancel, &QPushButton::clicked, albumOverlay, [=]() {
        albumOverlay->deleteLater();
        albumOverlay = nullptr;
    });
    connect(ok, &QPushButton::clicked, albumOverlay, [=]() {
        albumOverlay->deleteLater();
        albumOverlay = nullptr;
    });
    albumOverlay->show();
}

// Show the publish confirmation overlay for photo/video.
void PostPage::showPublishOverlay(bool isVideo) {
    if (confirmOverlay) {
        confirmOverlay->deleteLater();
        confirmOverlay = nullptr;
    }
    confirmOverlay = new QWidget(this);
    confirmOverlay->setObjectName("publishOverlay");
    confirmOverlay->setStyleSheet("#publishOverlay { background:rgba(0,0,0,120); }");
    confirmOverlay->setGeometry(rect());
    confirmOverlay->raise();
    QVBoxLayout *outer = new QVBoxLayout(confirmOverlay);
    outer->setContentsMargins(16, 16, 16, 16);
    QFrame *panel = new QFrame();
    panel->setStyleSheet("background:#ffffff; border-radius:18px;");
    QVBoxLayout *p = new QVBoxLayout(panel);
    p->setSpacing(12);
    p->setContentsMargins(16, 16, 16, 16);
    QLabel *title = new QLabel(translate("Publish"));
    title->setStyleSheet("font-weight:800; font-size:16px;");
    p->addWidget(title);
    QLabel *preview = new QLabel();
    preview->setMinimumHeight(200);
    preview->setStyleSheet("background:#cfcfcf; border-radius:16px;");
    preview->setAlignment(Qt::AlignCenter);
    preview->setText(isVideo ? translate("Video") : translate("Photo"));
    p->addWidget(preview);
    QLabel *body = new QLabel(isVideo ? translate("Publish captured video?") : translate("Publish captured photo?"));
    body->setWordWrap(true);
    body->setStyleSheet("color:#444;");
    p->addWidget(body);
    QHBoxLayout *btns = new QHBoxLayout();
    btns->addStretch();
    QPushButton *cancel = new QPushButton(translate("Cancel"));
    cancel->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:12px; background:#ffffff; font-weight:700;");
    QPushButton *ok = new QPushButton(translate("Publish"));
    ok->setStyleSheet("padding:8px 14px; border:2px solid #0b0b0b; border-radius:12px; background:#2f2f2f; color:#ffffff; font-weight:700;");
    btns->addWidget(cancel);
    btns->addWidget(ok);
    p->addLayout(btns);
    outer->addWidget(panel, 0, Qt::AlignCenter);
    connect(cancel, &QPushButton::clicked, confirmOverlay, [=]() {
        confirmOverlay->deleteLater();
        confirmOverlay = nullptr;
    });
    connect(ok, &QPushButton::clicked, confirmOverlay, [=]() {
        confirmOverlay->deleteLater();
        confirmOverlay = nullptr;
        if (isVideo) {
            emit publishVideo(static_cast<int>(elapsed.elapsed()));
        } else {
            emit publishPhoto();
        }
    });
    confirmOverlay->show();
}

// Switch to photo mode and refresh styles.
void PostPage::onTogglePhoto() {
    resetRecording();
    currentMode = Mode::Photo;
    updateModeStyles();
}

// Switch to video mode and refresh styles.
void PostPage::onToggleVideo() {
    resetRecording();
    currentMode = Mode::Video;
    updateModeStyles();
}

// Handle capture button: take photo or start/stop recording.
void PostPage::onCapturePressed() {
    if (currentMode == Mode::Photo) {
        showPublishOverlay(false);
        return;
    }

    // video mode: toggle recording
    if (!recording) {
        recording = true;
        elapsed.restart();
        timer.start();
        return;
    }

    // stop recording
    recording = false;
    timer.stop();
    showPublishOverlay(true);
    resetRecording();
}

// Open the mock album overlay.
void PostPage::onOpenAlbum() {
    showAlbumOverlay();
}
