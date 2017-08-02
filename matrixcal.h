#ifndef MATRIXCAL_H
#define MATRIXCAL_H

#include <QDialog>

namespace Ui {
class MatrixCal;
}

class MatrixCal : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixCal(QWidget *parent = 0);
    ~MatrixCal();

    void init();                            //初始化
    void setTableWidgetA();                 //设置矩阵A
    void setTableWidgetB();                 //设置矩阵B
    void setTableWidgetC();                 //设置矩阵C

private slots:
    void on_btn_ok_clicked();

    void on_btn_equal_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MatrixCal *ui;

    int rowCount,colCount;          //行数，列数
};

#endif // MATRIXCAL_H
