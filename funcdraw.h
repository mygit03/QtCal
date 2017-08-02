#ifndef FUNCDRAW_H
#define FUNCDRAW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QMessageBox>

#include "plotter.h"
#include "draw.h"

namespace Ui {
class FuncDraw;
}

class FuncDraw : public QDialog
{
    Q_OBJECT

public:
    explicit FuncDraw(QWidget *parent = 0);
    ~FuncDraw();

private slots:
    void on_btn_FuncDraw_clicked();

private:
    Ui::FuncDraw *ui;

    Plotter* m_pPlotter;  //创建一个窗口部件，用于显示从记事本中读出数据的曲线
    QHBoxLayout* m_PHBoxLayout;
};

#endif // FUNCDRAW_H
