//
//
//

#include "the_button.h"


void TheButton::init(TheButtonInfo* i) {
    if (!i) return;

    if (i->icon) {
        setIcon(*(i->icon));
    }
    info =  i;
}


void TheButton::clicked() {
    emit jumpTo(info);
}
