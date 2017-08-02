#include "equcal.h"
#include "ui_equcal.h"

#include <math.h>
#include <stdio.h>
#include <QDebug>

EquCal::EquCal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquCal)
{
    ui->setupUi(this);

    init();
}

EquCal::~EquCal()
{
    delete ui;
}

void EquCal::init()
{
    ui->lineEdit_x1->setEnabled(false);
    ui->lineEdit_x2->setEnabled(false);
    ui->lineEdit_x->setEnabled(false);
    ui->lineEdit_y->setEnabled(false);
}

void EquCal::on_btn_answer1_clicked()
{
    int a = ui->spinBox_a->value();
    int b = ui->spinBox_b->value();
    int c = ui->spinBox_c->value();
    float d, e, x1, x2;

    if((a==0)&&(b==0)&&(c!=0))
    {
        ui->lineEdit_x1->setText("No Root");
        ui->lineEdit_x2->setHidden(true);
        ui->label_x2->setHidden(true);
    }
    else if((a==0)&&(b!=0))     //一元一次方程
    {
        x1 = x2 = -c/b;
        ui->lineEdit_x1->setText(QString::number(x1));
        ui->lineEdit_x2->setEnabled(true);
        ui->lineEdit_x2->setHidden(true);
        ui->label_x2->setHidden(true);
    }
    else if(a!=0)               //一元二次方程
    {
        ui->lineEdit_x2->setHidden(false);
        ui->label_x2->setHidden(false);
        ui->lineEdit_x2->setEnabled(false);

        d = b*b - 4*a*c;
        e = 2*a;
        x1 = -b/e;
        if(d>=0)
        {
            x2 = sqrt(d)/e;
            ui->lineEdit_x1->setText(QString("%1").arg(x1+x2));
            ui->lineEdit_x2->setText(QString("%1").arg(x1-x2));
        }else{
            x2 = sqrt(-d)/e;

#if 1
            ui->lineEdit_x1->setText(QString("%1%2%3%4").arg(x1).arg("+").arg(x2).arg("i"));
            ui->lineEdit_x2->setText(QString("%1%2%3%4").arg(x1).arg("+").arg(x2).arg("i"));
#else
            char root1[100]={0};
            char root2[100]={0};
            sprintf(root1,"%f+%fi",x1,x2);
            sprintf(root2,"%f-%fi",x1,x2);
            ui->lineEdit_x1->setText(QString::fromAscii(root1));
            ui->lineEdit_x2->setText(QString::fromAscii(root2));
#endif
        }
    }
}

//解二元一次方程
void EquCal::on_btn_answer2_clicked()
{
    int a1 = ui->spinBox_a1->value();
    int b1 = ui->spinBox_b1->value();
    int c1 = ui->spinBox_c1->value();
    int a2 = ui->spinBox_a2->value();
    int b2 = ui->spinBox_b2->value();
    int c2 = ui->spinBox_c2->value();
    float x,y;
    if(a1*b2 == a2*b1)
    {
        QString text = "-";
        ui->lineEdit_x->setText(text);
        ui->lineEdit_y->setText(text);
        qDebug()<<"text:::"<<text;
    }else{
        x = (b1*c2-b2*c1)/(a1*b2-a2*b1);
        y = (a1*c2-a2*c1)/(a2*b1-a1*b2);
        ui->lineEdit_x->setText(QString::number(x));
        ui->lineEdit_y->setText(QString::number(y));
    }

    ui->lineEdit_x->setText(QString::number(x));
    ui->lineEdit_y->setText(QString::number(y));
}
