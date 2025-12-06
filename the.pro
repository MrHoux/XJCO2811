QT += core gui widgets multimedia multimediawidgets
QT += axcontainer

TARGET = FeeL

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


QMAKE_CXXFLAGS += -finput-charset=UTF-8
QMAKE_CXXFLAGS += -fexec-charset=UTF-8
QMAKE_CXXFLAGS += -fwide-exec-charset=UTF-8
TRANSLATIONS += feel_en.ts feel_zh.ts
# set the source file encoding
CODECFORSRC = UTF-8

SOURCES += \
        detailwindow.cpp \
        settingwindow.cpp \
        the_button.cpp \
        the_player.cpp \
        friendwindow.cpp \
        profilewindow.cpp \
        chatwindow.cpp \
        postpage.cpp \
        FeeL.cpp

HEADERS += \
    detailwindow.h \
    settingwindow.h \
    the_button.h \
    the_player.h \
    friendwindow.h \
    profilewindow.h \
    chatwindow.h \
    postpage.h \
    friends_data.h

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
