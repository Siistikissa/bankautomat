#ifndef RFID_DLL_H
#define RFID_DLL_H

#include <QDebug>
#include <QObject>
#include <Qstring>
#include "rfid_dll_global.h"
#include <QSerialPort>
class RFID_DLL_EXPORT Rfid_dll : public QObject
{
public:
    Rfid_dll();
    QByteArray rfid;
    void rfidDataReceived();

private slots:
    void onReadyRead();


private:
    QSerialPort *PORT;

};

#endif // RFID_DLL_H
