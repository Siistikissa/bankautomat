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
        {"ATM NUMBER",std::vector<QString>() = {"ATM NUMBER", "AUTOMAATTINUMERO", "ATM-NUMMER"}},
        {"DATE",std::vector<QString>() = {"DATE", "PVM", "DATUM"}},
        {"REFERENCE",std::vector<QString>() = {"REFERENCE", "VIITE", "REFERENS"}},
        {"CARD NUMBER",std::vector<QString>() = {"CARD NUMBER", "KORTIN NUMERO", "KORTNUMMER"}},
        {"REFERENCE NUMBER",std::vector<QString>() = {"REFERENCE NUMBER", "VIITENUMERO", "REFERENSNUMMER"}},
        {"WITHDRAWAL",std::vector<QString>() = {"WITHDRAWAL", "SUMMA", "UTTAG"}},
        {"AMOUNT",std::vector<QString>() = {"AMOUNT", "SUMMA", "BELOPP"}},
        {"THANK YOU FOR STOPPING BY",std::vector<QString>() = {"THANK YOU FOR STOPPING BY", "KIITOS KÄYNNISTÄ", "TACK FÖR BESÖKET"}},
        {"WELCOME AGAIN!",std::vector<QString>() = {"WELCOME AGAIN!", "TERVETULOA UUDELLEEN!", "VÄLKOMMEN TILLBAKA!"}},
        {"",std::vector<QString>() = {"", "", ""}},
        {"",std::vector<QString>() = {"", "", ""}}

        };

};

#endif // KUITTI_H
