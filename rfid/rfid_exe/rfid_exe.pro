QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    rfid.cpp \
    rfid_m.cpp

HEADERS += \
    rfid.h

FORMS += \
    rfid.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-rfid_dll-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/release/ -lrfid_dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-rfid_dll-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/debug/ -lrfid_dll
else:unix: LIBS += -L$$PWD/../build-rfid_dll-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/ -lrfid_dll

INCLUDEPATH += $$PWD/../rfid_dll
DEPENDPATH += $$PWD/../rfid_dll
