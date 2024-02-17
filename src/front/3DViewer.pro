QT       += core gui opengl openglwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(qtgifimage/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    ../backend/backend.c \
    ../backend/validation.c \
    ../backend/affin.c \
    settings.cpp

HEADERS += \
    mainwindow.h \
    glwidget.h \
    ../backend/backend.h \
    ../backend/validation.h \
    ../backend/affin.h

FORMS += \
    mainwindow.ui

ICON = assets/Viewer.icns


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc