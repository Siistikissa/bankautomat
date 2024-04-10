QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kuitti.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    kuitti.h \
    mainwindow.h

FORMS += \
    kuitti.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Pin/build-PinUI-qmaketesti-Debug/release/ -lPinUI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Pin/build-PinUI-qmaketesti-Debug/debug/ -lPinUI

INCLUDEPATH += $$PWD/Pin/PinUI
DEPENDPATH += $$PWD/Pin/PinUI

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/restapi/build-restapi-qmaketesti-Debug/release/ -lrestapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/restapi/build-restapi-qmaketesti-Debug/debug/ -lrestapi

INCLUDEPATH += $$PWD/restapi/restapi
DEPENDPATH += $$PWD/restapi/restapi
