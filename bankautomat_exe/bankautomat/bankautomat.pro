QT       += core gui
QT       += multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kuitti.cpp \
    rfid.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    kuitti.h \
    rfid.h \
    mainwindow.h

FORMS += \
    kuitti.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/restApi/restapi/build/release/ -lrestapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/restApi/restapi/build/debug/ -lrestapi

INCLUDEPATH += $$PWD/restApi/restapi
DEPENDPATH += $$PWD/restApi/restapi

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PinUI/build/release/ -lPinUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PinUI/build/debug/ -lPinUI

INCLUDEPATH += $$PWD/PinUI
DEPENDPATH += $$PWD/PinUI
