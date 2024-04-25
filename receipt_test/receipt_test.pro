QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C://projektit//pankkiautomaatti//SPL_Group8//receipt_test//Receipt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Receipt/build/release/ -lReceipt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Receipt/build/debug/ -lReceipt

INCLUDEPATH += $$PWD/Receipt/build
DEPENDPATH += $$PWD/Receipt/build
