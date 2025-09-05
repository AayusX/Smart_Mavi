QT += core widgets printsupport

TARGET = SmartMaviManager
TEMPLATE = app

CONFIG += c++17

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/surveydialog.cpp \
    src/teacher.cpp \
    src/subject.cpp \
    src/classinfo.cpp \
    src/timeslot.cpp \
    src/schedule.cpp \
    src/schedulegenerator.cpp \
    src/scheduleview.cpp

HEADERS += \
    include/mainwindow.h \
    include/surveydialog.h \
    include/teacher.h \
    include/subject.h \
    include/classinfo.h \
    include/timeslot.h \
    include/schedule.h \
    include/schedulegenerator.h \
    include/scheduleview.h

RESOURCES += resources.qrc

# Copy logo to build directory
QMAKE_POST_LINK += cp $$PWD/resources/logo.png $$OUT_PWD/

# Windows specific settings
win32 {
    CONFIG += windows
    RC_ICONS = resources/logo.png
}

# Linux specific settings
unix:!macx {
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
}
