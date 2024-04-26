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

    void setParameters(QString serial, QString type, int transaction, std::vector<QString> transactionsVector);

private:
    Ui::Kuitti *ui;
    QSoundEffect printtaus;
    QImage img;

    std::unordered_map<QString, std::vector<QString>> dictionary =
        {
        {"Test", std::vector<QString>() = {"Test", "Testi", "Testa"}},
        {"ATM NUMBER",std::vector<QString>() = {"ATM NUMBER", "PANKKIAUTOMAATTI NUMERO","ATM NUMMER"}},
        {"CLOCK",std::vector<QString>() = {"CLOCK", "KELLO", "KLOCKA"}},
        {"CARD NUMBER",std::vector<QString>() = {"CARD NUMBER", "KORTIN NUMERO", "KORTNUMMER"}},
        {"TRANSACTION",std::vector<QString>() = {"TRANSACTION", "TAPAHTUMA", "TRANSAKTION"}},
        {"TOTAL",std::vector<QString>() = {"TOTAL", "YHTEENSÄ", "SAMMANLAGT"}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}}

        };

};

#endif // KUITTI_H
