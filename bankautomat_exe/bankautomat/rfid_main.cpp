#include "rfid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rfid w;
    w.show();
    return a.exec();
}
