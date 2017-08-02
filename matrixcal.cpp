#include "matrixcal.h"
#include "ui_matrixcal.h"

#include <QMessageBox>

MatrixCal::MatrixCal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatrixCal)
{
    ui->setupUi(this);

    init();
}

MatrixCal::~MatrixCal()
{
    delete ui;
}

//初始化
void MatrixCal::init()
{
    ui->label->setHidden(true);
    ui->doubleSpinBox->setHidden(true);
    ui->groupBox_B->setHidden(false);
}

//设置矩阵A
void MatrixCal::setTableWidgetA()
{
    ui->tableWidget_A->setRowCount(rowCount);
    ui->tableWidget_A->setColumnCount(colCount);
    ui->tableWidget_A->horizontalHeader()->setVisible(false);
    ui->tableWidget_A->verticalHeader()->setVisible(false);
    ui->tableWidget_A->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int row = 0; row < rowCount; row++)
    {
        for(int col = 0; col < colCount; col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            ui->tableWidget_A->setItem(row,col,item);
            ui->tableWidget_A->item(row,col)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

//设置矩阵B
void MatrixCal::setTableWidgetB()
{
    ui->tableWidget_B->setRowCount(rowCount);
    ui->tableWidget_B->setColumnCount(colCount);
    ui->tableWidget_B->horizontalHeader()->setVisible(false);
    ui->tableWidget_B->verticalHeader()->setVisible(false);
    ui->tableWidget_B->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int row = 0; row < rowCount; row++)
    {
        for(int col = 0; col < colCount; col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            ui->tableWidget_B->setItem(row,col,item);
            ui->tableWidget_B->item(row,col)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

//设置矩阵C
void MatrixCal::setTableWidgetC()
{
    ui->tableWidget_C->setRowCount(rowCount);
    ui->tableWidget_C->setColumnCount(colCount);
    ui->tableWidget_C->horizontalHeader()->setVisible(false);
    ui->tableWidget_C->verticalHeader()->setVisible(false);
    ui->tableWidget_C->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//配置矩阵A、B的行数、例数
void MatrixCal::on_btn_ok_clicked()
{
    rowCount = ui->spinBox_rowCount->value();
    colCount = ui->spinBox_colCount->value();

    if((rowCount == 0) || (colCount == 0))
    {
        QMessageBox::warning(this,tr("警告"),tr("请设置有效行列数！"));
        return;
    }

    setTableWidgetA();
    setTableWidgetB();
}

//计算结果
void MatrixCal::on_btn_equal_clicked()
{
    setTableWidgetC();
    int op = ui->comboBox->currentIndex();
    switch(op)
    {
    case 0:     //+
    {
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 0; j < colCount; j++)
            {
                double A = ui->tableWidget_A->item(i,j)->text().toDouble();
                double B = ui->tableWidget_B->item(i,j)->text().toDouble();
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(A+B));
                ui->tableWidget_C->setItem(i,j,item);
                ui->tableWidget_C->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
    case 1:     //-
    {
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 0; j < colCount; j++)
            {
                double A = ui->tableWidget_A->item(i,j)->text().toDouble();
                double B = ui->tableWidget_B->item(i,j)->text().toDouble();
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(A-B));
                ui->tableWidget_C->setItem(i,j,item);
                ui->tableWidget_C->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
    case 2:     //*
    {
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 0; j < colCount; j++)
            {
                double A = ui->tableWidget_A->item(i,j)->text().toDouble();
                double B = ui->tableWidget_B->item(i,j)->text().toDouble();
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(A*B));
                ui->tableWidget_C->setItem(i,j,item);
                ui->tableWidget_C->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
    case 3:     //矩阵转置
    {
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 0; j < colCount; j++)
            {
                double A = ui->tableWidget_A->item(i,j)->text().toDouble();
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(A));
                ui->tableWidget_C->setItem(j,i,item);
                ui->tableWidget_C->item(j,i)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
    case 4:     //数乘矩阵
    {
        for(int i = 0; i < rowCount; i++)
        {
            for(int j = 0; j < colCount; j++)
            {
                double num = ui->doubleSpinBox->value();
                double A = ui->tableWidget_A->item(i,j)->text().toDouble();
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(num*A));
                ui->tableWidget_C->setItem(i,j,item);
                ui->tableWidget_C->item(i,j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        break;
    }
    }
}

void MatrixCal::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->label->setHidden(true);
        ui->doubleSpinBox->setHidden(true);
        ui->groupBox_B->setHidden(false);
    }else if(index == 1)
    {
        ui->label->setHidden(true);
        ui->doubleSpinBox->setHidden(true);
        ui->groupBox_B->setHidden(false);
    }else if(index == 2)
    {
        ui->label->setHidden(true);
        ui->doubleSpinBox->setHidden(true);
        ui->groupBox_B->setHidden(false);
    }else if(index == 3)
    {
        ui->label->setHidden(true);
        ui->doubleSpinBox->setHidden(true);
        ui->groupBox_B->setHidden(true);
    }else if(index == 4)
    {
        ui->label->setHidden(false);
        ui->doubleSpinBox->setHidden(false);
        ui->groupBox_B->setHidden(true);
    }
}
