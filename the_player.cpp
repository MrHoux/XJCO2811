//
//
//

#include "the_player.h"
#include <QDebug>
#include <QTimer>

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    if (buttons && !buttons->empty() && buttons->at(0)) {
        jumpTo(buttons->at(0)->info); // start with the first clip
    }
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    if (!infos || infos->empty()) return;

    TheButtonInfo* i = &infos->at(rand() % infos->size());
    if (buttons && !buttons->empty() && i && i->icon) {
        buttons->at(updateCount++ % buttons->size())->init(i);
    }
}

void ThePlayer::playStateChanged(QMediaPlayer::State ms) {
    switch (ms) {
    case QMediaPlayer::StoppedState:
        play();
        break;
    default:
        break;
    }

}

void ThePlayer::jumpTo(TheButtonInfo* button) {
    // Null pointer check
    if (button && button->url) return;

        setMedia( * button -> url);
        play(); // immediate playback after selection

}
