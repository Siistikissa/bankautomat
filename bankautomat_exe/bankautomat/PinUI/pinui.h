#ifndef PINUI_H
#define PINUI_H

#include <QWidget>
#include <QSoundEffect>
#include <stdbool.h>
#include <QDebug>

namespace Ui {
class PinUI;
}

class PinUI : public QWidget
{
    Q_OBJECT

public:
    explicit PinUI(QWidget *parent = nullptr);
    ~PinUI();

private slots:
    void on_pushButton_clicked();
    void on_btnEnter_clicked();
    void on_btnClear_clicked();
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

signals:
    void sendPin(QString);

private:
    QSoundEffect beep;
    QSoundEffect lowbeep;
    std::string input;
    int state=1;
    bool playingSound=true;
    Ui::PinUI *ui;
};

#endif // PINUI_H
