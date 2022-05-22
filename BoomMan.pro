QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QMAKE_LFLAGS_WINDOWS += -Wl,--stack,64000000

#QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

LIBS += -lDbgHelp


#加入调试信息
QMAKE_CFLAGS_RELEASE += -g
QMAKE_CXXFLAGS_RELEASE += -g
#禁止优化
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
#release在最后link时默认有"-s”参数，表示"Omit all symbol information from the output file"，因此要去掉该参数
QMAKE_LFLAGS_RELEASE = -mthreads

# QMAKE_LFLAGS += /STACK:128000000

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AI.cpp \
    boom.cpp \
    ccrashstack.cpp \
    client.cpp \
    gameboard.cpp \
    gamepara.cpp \
    gamewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    people.cpp \
    server.cpp \
    setting.cpp \
    tool.cpp

HEADERS += \
    AI.h \
    boom.h \
    ccrashstack.h \
    client.h \
    gameboard.h \
    gamepara.h \
    gamewidget.h \
    mainwindow.h \
    people.h \
    server.h \
    setting.h \
    tool.h

FORMS += \
    gamepara.ui \
    gamewidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
