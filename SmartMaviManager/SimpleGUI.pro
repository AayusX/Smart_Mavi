QT += core widgets printsupport

TARGET = SmartMaviGUI
TEMPLATE = app

CONFIG += c++17

SOURCES += simple_gui.cpp
HEADERS += simple_gui.h

# Copy logo to build directory
QMAKE_POST_LINK += cp $$PWD/logo.png $$OUT_PWD/

# Linux specific settings
unix:!macx {
    QMAKE_LFLAGS += -Wl,--rpath=\\\\\\$\\$ORIGIN
}
