#ifndef BANKUI_H
#define BANKUI_H

#include <QWidget>

namespace Ui {
class bankUI;
}

class bankUI : public QWidget
{
    Q_OBJECT

public:
    explicit bankUI(QWidget *parent = nullptr);
    ~bankUI();

private:
    Ui::bankUI *ui;
};

#endif // BANKUI_H
