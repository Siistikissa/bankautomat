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

    std::unordered_map<QString, std::vector<QString>> dictionary = {
        {"Test", std::vector<QString>() = {"Test", "Testi", "Testa"}},
        {"ATM NUMBER",std::vector<QString>() = {"ATM NUMBER", "PANKKIAUTOMAATTI NUMERO","ATM NUMMER"}},
        {"CLOCK",std::vector<QString>() = {"CLOCK", "KELLO", "KLOCKA"}},
        {"CUSTOMER",std::vector<QString>() = {"CUSTOMER", "ASIAKAS", "KUND"}},
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
