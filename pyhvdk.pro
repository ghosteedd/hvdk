TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle qt

PYTHON_VERSION = 310

MODULE_NAME = "pyhvdk"$${PYTHON_VERSION}

contains(QT_ARCH, x86_64) {
    MODULE_NAME = $${MODULE_NAME}_64
} else {
    MODULE_NAME = $${MODULE_NAME}_86
}

TARGET = $${MODULE_NAME}

DEFINES += MODULE_NAME=$${MODULE_NAME}

DEFINES += BOOST_PYTHON_STATIC_LIB

LIBS += \
        -lhid \
        -lsetupapi

contains(QT_ARCH, x86_64) {
    PYTHON_PATH = "C:/DevTools/Python/"$${PYTHON_VERSION}"0-64"
    BOOST_PATH = "C:/DevTools/boost-1-79-0-x64"
} else {
    PYTHON_PATH = "C:/DevTools/Python/"$${PYTHON_VERSION}"0-32"
    BOOST_PATH = "C:/DevTools/boost-1-79-0-x86"
}

INCLUDEPATH += $${PYTHON_PATH}/include
LIBS += -L$${PYTHON_PATH}/libs

INCLUDEPATH += $${BOOST_PATH}
LIBS += -L$${BOOST_PATH}/libs
LIBS += -L$${BOOST_PATH}/stage/lib

SOURCES += \
        src/base.cpp \
        src/keyboard.cpp \
        src/mouseabs.cpp \
        src/mouserel.cpp \
        python-warp/pyhvdk.cpp

HEADERS += \
        src/base.h \
        src/keyboard.h \
        src/mouseabs.h \
        src/mouserel.h \
        src/keybdkeys.h
