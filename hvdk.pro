TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle qt

CONFIG(release, debug|release) {
    TARGET = hvdk
} else {
    TARGET = hvdkd
}

LIBS += \
        -lhid \
        -lsetupapi

SOURCES += \
        src/hvdkbase.cpp \
        src/keyboard.cpp \
        src/mouseabs.cpp \
        src/mouserel.cpp

HEADERS += \
        src/hvdkbase.h \
        src/keybdkeys.h \
        src/keyboard.h \
        src/mouseabs.h \
        src/mouserel.h
