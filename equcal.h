#ifndef EQUCAL_H
#define EQUCAL_H

#include <QDialog>

namespace Ui {
class EquCal;
}

class EquCal : public QDialog
{
    Q_OBJECT

public:
    explicit EquCal(QWidget *parent = 0);
    ~EquCal();

    void init();                                //初始化

private slots:
    void on_btn_answer1_clicked();              //解一元二次方程

    void on_btn_answer2_clicked();              //解二元一次方程

private:
    Ui::EquCal *ui;
};

#endif // EQUCAL_H
