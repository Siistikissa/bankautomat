#ifndef KUITTI_H
#define KUITTI_H

#include <QWidget>
#include <QSoundEffect>
#include <QDir>

namespace Ui {
class Kuitti;
}

class Kuitti : public QWidget
{
    Q_OBJECT

public:
    explicit Kuitti(QWidget *parent = nullptr);
    ~Kuitti();

private:
    Ui::Kuitti *ui;
    QSoundEffect printtaus;
};

#endif // KUITTI_H
