QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    build/bankui.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    build/bankui.h \
    mainwindow.h

FORMS += \
    build/bankui.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PinUI/build/release/ -lPinUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PinUI/build/debug/ -lPinUI

INCLUDEPATH += C:/projektit/pankkiautomaatti/SPL_Group8/bankautomat_exe/bankautomat/PinUI
INCLUDEPATH += $$PWD/PinUI/build
DEPENDPATH += $$PWD/PinUI/build
