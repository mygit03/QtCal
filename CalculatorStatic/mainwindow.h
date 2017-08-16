#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QClipboard>
#include <QTimer>
#include <QLabel>

#include "include/plus.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_btn0();
    void slot_btn1();
    void slot_btn2();
    void slot_btn3();
    void slot_btn4();
    void slot_btn5();
    void slot_btn6();
    void slot_btn7();
    void slot_btn8();
    void slot_btn9();
    void slot_btnPoint();
    void slot_btnSymBol();
    void slot_btnBack();
    void slot_btnCE();
    void slot_btnC();
    void slot_btnX();
    void slot_btnPow();
    void slot_btnAdd();
    void slot_btnSub();
    void slot_btnMul();
    void slot_btnDiv();
    void slot_btnMod();
    void slot_btnEqual();
    void slot_about();
    void slot_copy();
    void slot_paste();
    void slot_showTime();

private:
    Ui::MainWindow *ui;

    QLineEdit *lineEdit;
    QPushButton *btn_0;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QPushButton *btn_3;
    QPushButton *btn_4;
    QPushButton *btn_5;
    QPushButton *btn_6;
    QPushButton *btn_7;
    QPushButton *btn_8;
    QPushButton *btn_9;
    QPushButton *btn_point;
    QPushButton *btn_div;
    QPushButton *btn_mul;
    QPushButton *btn_sub;
    QPushButton *btn_add;
    QPushButton *btn_mod;
    QPushButton *btn_x;
    QPushButton *btn_equal;
    QPushButton *btn_back;
    QPushButton *btn_CE;
    QPushButton *btn_C;
    QPushButton *btn_symbol;
    QPushButton *btn_sqrt;

    Plus m_plus;
    bool flag;                          //计算标识
    double value, value1, value2;
    int op;                             //运算符

    QClipboard *board;                   //剪切板
    QTimer m_timer;
    QLabel *label;
};

#endif // MAINWINDOW_H
