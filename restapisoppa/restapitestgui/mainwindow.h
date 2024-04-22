#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <restapi.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void setUiText(QString lastReply);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    std::string tempToken;
    Ui::MainWindow *ui;
    Restapi *api = new Restapi;
    bool coolThing = false;
};
#endif // MAINWINDOW_H
