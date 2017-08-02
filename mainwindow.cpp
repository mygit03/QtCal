#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_standard_triggered();        //初始化为标准型计算器

    init();

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(display()));
    timer->start(1);

    connect(ui->btn_equal,SIGNAL(clicked()),this,SLOT(equal()));        //"="
    connect(ui->aboutQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));      //关于Qt

//    webView = new QWebView;

    ui->menuOnLine_L->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    op = 0;
    flag = 0;
    zflag = 0;
    sumInMemory = 0.0;

    ui->paste->setEnabled(false);

    //    str = "0";
    ui->lineEdit->setReadOnly(true);                    //设为只读
    ui->lineEdit->setAlignment(Qt::AlignRight);         //设为右对齐
    ui->lineEdit->setText("0");

    ui->rBtn_10->setChecked(true);
    ui->btn_10->setEnabled(false);
    ui->btn_11->setEnabled(false);
    ui->btn_12->setEnabled(false);
    ui->btn_13->setEnabled(false);
    ui->btn_14->setEnabled(false);
    ui->btn_15->setEnabled(false);
    ui->btn_and->setEnabled(false);
    ui->btn_or->setEnabled(false);
    ui->btn_tongHuo->setEnabled(false);
    ui->btn_yiHuo->setEnabled(false);

    ui->label_time->setAlignment(Qt::AlignRight);

    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height);
}

//二进制转十进制
int MainWindow::f2to10(QString str)
{
    int dec = 0;
    int i=0;

    for( i=0 ; i<str.size() ; i++)
    {
        if(str.at(i) == '1')
        {
            dec += pow(2,(str.size() - 1 - i));
        }
    }
    //qDebug()<<dec;
    return dec;
}

//八进制转十进制
int MainWindow::f8to10(QString str)
{
    int dec = 0;
    int i=0;

    for( i=0 ; i<str.size() ; i++)
    {
        if((str.at(i) >= '0') && (str.at(i) <= '7'))
        {
            QString tmp = QString(str.at(i));
            dec += tmp.toInt() * pow(8,(str.size() - 1 - i));
        }
    }
    //qDebug()<<dec;
    return dec;
}

//十六进制转十进制
int MainWindow::f16to10(QString str)
{
//    long dec=0;
//    int i=0;

//    for( i=0 ; i<str.size() ; i++)
//    {
//        if ((str.at(i)>='A') && (str.at(i)<='F'))
//        {
//            //            dec*=16;
//            //            dec+=str.at(i).unicode() - 70+15;

//            QString tmp = QString(str.at(i));
//            dec += (tmp.toInt() - 65 + 10) * pow(16,(str.size() - 1 - i));
//        }
//        else if((str.at(i)>='0')&&(str.at(i)<='9'))
//        {
//            //            dec*=16;
//            //            dec+=str.at(i).unicode() - 48;

//            QString tmp = QString(str.at(i));
//            dec += tmp.toInt() * pow(16,(str.size() - 1 - i));
//        }
//    }
//    //qDebug()<<dec;
//    return dec;

    long decvalue=0;
    int i=0;

    for( i=0 ; i<str.size() ; i++)
    {
        if((str.at(i)>= 'a')&&(str.at(i)<='f'))
        {
            decvalue*=16;
            decvalue+= str.at(i).unicode() - 102+15;            //f对应的十进制是102
        }
        else if ((str.at(i)>='A') && (str.at(i)<='F'))
        {
            decvalue*=16;
            decvalue+=str.at(i).unicode() - 70+15;              //F对应的十进制是70
        }
        else if((str.at(i)>='0')&&(str.at(i)<='9'))
        {
            decvalue*=16;
            decvalue+=str.at(i).unicode() - 48;
        }
    }
    //qDebug()<<decvalue;
    return decvalue;
}

//十进制转二进制
QString MainWindow::f10to2(int num)
{
    QString val;
    while(num / 2)
    {
        if(num % 2)
            val.insert(0,'1');
        else
            val.insert(0,'0');
        num /= 2;
        qDebug() << "num:::" << num;
    }
    if(num)
        val.insert(0,'1');
    else
        val.insert(0,'0');
    return val;
}

void MainWindow::set10()
{
    ui->btn_2->setEnabled(true);
    ui->btn_3->setEnabled(true);
    ui->btn_4->setEnabled(true);
    ui->btn_5->setEnabled(true);
    ui->btn_6->setEnabled(true);
    ui->btn_7->setEnabled(true);
    ui->btn_8->setEnabled(true);
    ui->btn_9->setEnabled(true);
    ui->btn_10->setEnabled(false);
    ui->btn_11->setEnabled(false);
    ui->btn_12->setEnabled(false);
    ui->btn_13->setEnabled(false);
    ui->btn_14->setEnabled(false);
    ui->btn_15->setEnabled(false);
    ui->btn_x->setEnabled(true);
    ui->btn_nx->setEnabled(true);
    ui->btn_sqrt->setEnabled(true);
    ui->btn_pow->setEnabled(true);
    ui->btn_mod->setEnabled(true);
    ui->btn_int->setEnabled(true);
    ui->btn_tongHuo->setEnabled(false);
    ui->btn_yiHuo->setEnabled(false);
    ui->btn_and->setEnabled(false);
    ui->btn_or->setEnabled(false);
    ui->btn_10x->setEnabled(true);
    ui->btn_log->setEnabled(true);
    ui->btn_sin->setEnabled(true);
    ui->btn_cos->setEnabled(true);
    ui->btn_tan->setEnabled(true);
    ui->btn_n->setEnabled(true);
    ui->btn_PI->setEnabled(true);
    ui->btn_exp->setEnabled(true);
    ui->btn_ln->setEnabled(true);
}

//定时器槽函数
void MainWindow::display()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->label_time->setText(dateTime.toString("yyyy/MM/dd  ddd  hh:mm:ss"));
}

void MainWindow::on_rBtn_2_clicked(bool checked)
{
    if(checked == true)
    {
        ui->btn_2->setEnabled(false);
        ui->btn_3->setEnabled(false);
        ui->btn_4->setEnabled(false);
        ui->btn_5->setEnabled(false);
        ui->btn_6->setEnabled(false);
        ui->btn_7->setEnabled(false);
        ui->btn_8->setEnabled(false);
        ui->btn_9->setEnabled(false);
        ui->btn_10->setEnabled(false);
        ui->btn_11->setEnabled(false);
        ui->btn_12->setEnabled(false);
        ui->btn_13->setEnabled(false);
        ui->btn_14->setEnabled(false);
        ui->btn_15->setEnabled(false);
        ui->btn_x->setEnabled(false);
        ui->btn_nx->setEnabled(false);
        ui->btn_sqrt->setEnabled(false);
        ui->btn_pow->setEnabled(false);
        ui->btn_mod->setEnabled(false);
        ui->btn_int->setEnabled(false);
        ui->btn_10x->setEnabled(false);
        ui->btn_log->setEnabled(false);
        ui->btn_sin->setEnabled(false);
        ui->btn_cos->setEnabled(false);
        ui->btn_tan->setEnabled(false);
        ui->btn_n->setEnabled(false);
        ui->btn_PI->setEnabled(false);
        ui->btn_tongHuo->setEnabled(true);
        ui->btn_yiHuo->setEnabled(true);
        ui->btn_and->setEnabled(true);
        ui->btn_or->setEnabled(true);
        ui->btn_exp->setEnabled(false);
        ui->btn_ln->setEnabled(false);

        QString value;
        int realValue;
        value1 = ui->lineEdit->text();

        switch(zflag)
        {
        case 0: realValue = value1.toLong();break;
        case 2: realValue = f2to10(value1);break;
        case 8: realValue = f8to10(value1);break;
        case 16: realValue = f16to10(value1);break;
        }
        //qDebug() << loo;
        value = QString::number(realValue,2);
        ui->lineEdit->setText(value);
        zflag = 2;
    }
}

void MainWindow::on_rBtn_8_clicked(bool checked)
{
    if(checked == true)
    {
        ui->btn_2->setEnabled(true);
        ui->btn_3->setEnabled(true);
        ui->btn_4->setEnabled(true);
        ui->btn_5->setEnabled(true);
        ui->btn_6->setEnabled(true);
        ui->btn_7->setEnabled(true);
        ui->btn_8->setEnabled(false);
        ui->btn_9->setEnabled(false);
        ui->btn_10->setEnabled(false);
        ui->btn_11->setEnabled(false);
        ui->btn_12->setEnabled(false);
        ui->btn_13->setEnabled(false);
        ui->btn_14->setEnabled(false);
        ui->btn_15->setEnabled(false);
        ui->btn_x->setEnabled(false);
        ui->btn_nx->setEnabled(false);
        ui->btn_sqrt->setEnabled(false);
        ui->btn_pow->setEnabled(false);
        ui->btn_mod->setEnabled(false);
        ui->btn_int->setEnabled(false);
        ui->btn_tongHuo->setEnabled(false);
        ui->btn_yiHuo->setEnabled(false);
        ui->btn_and->setEnabled(false);
        ui->btn_or->setEnabled(false);
        ui->btn_10x->setEnabled(false);
        ui->btn_log->setEnabled(false);
        ui->btn_sin->setEnabled(false);
        ui->btn_cos->setEnabled(false);
        ui->btn_tan->setEnabled(false);
        ui->btn_n->setEnabled(false);
        ui->btn_PI->setEnabled(false);
        ui->btn_exp->setEnabled(false);
        ui->btn_ln->setEnabled(false);

        QString value;
        int realValue;
        value1 = ui->lineEdit->text();

        switch(zflag)
        {
        case 0: realValue = value1.toLong();break;
        case 2: realValue = f2to10(value1);break;
        case 8: realValue = f8to10(value1);break;
        case 16: realValue = f16to10(value1);break;
        }
        //qDebug() << loo;
        value = QString::number(realValue,8);
        ui->lineEdit->setText(value);
        zflag = 8;
    }
}

void MainWindow::on_rBtn_10_clicked(bool checked)
{
    if(checked == true)
    {
        set10();

        QString value;
        int realValue;
        value1 = ui->lineEdit->text();

        switch(zflag)
        {
        case 0: realValue = value1.toLong();break;
        case 2: realValue = f2to10(value1);break;
        case 8: realValue = f8to10(value1);break;
        case 16: realValue = f16to10(value1);break;
        }
        //qDebug() << loo;
        value = QString::number(realValue);
        ui->lineEdit->setText(value);
        zflag = 0;
    }
}

void MainWindow::on_rBtn_16_clicked(bool checked)
{
    if(checked == true)
    {
        ui->btn_2->setEnabled(true);
        ui->btn_3->setEnabled(true);
        ui->btn_4->setEnabled(true);
        ui->btn_5->setEnabled(true);
        ui->btn_6->setEnabled(true);
        ui->btn_7->setEnabled(true);
        ui->btn_8->setEnabled(true);
        ui->btn_9->setEnabled(true);
        ui->btn_10->setEnabled(true);
        ui->btn_11->setEnabled(true);
        ui->btn_12->setEnabled(true);
        ui->btn_13->setEnabled(true);
        ui->btn_14->setEnabled(true);
        ui->btn_15->setEnabled(true);
        ui->btn_x->setEnabled(false);
        ui->btn_nx->setEnabled(false);
        ui->btn_sqrt->setEnabled(false);
        ui->btn_pow->setEnabled(false);
        ui->btn_mod->setEnabled(false);
        ui->btn_int->setEnabled(false);
        ui->btn_tongHuo->setEnabled(true);
        ui->btn_yiHuo->setEnabled(true);
        ui->btn_and->setEnabled(true);
        ui->btn_or->setEnabled(true);
        ui->btn_10x->setEnabled(false);
        ui->btn_log->setEnabled(false);
        ui->btn_sin->setEnabled(false);
        ui->btn_cos->setEnabled(false);
        ui->btn_tan->setEnabled(false);
        ui->btn_n->setEnabled(false);
        ui->btn_PI->setEnabled(false);
        ui->btn_exp->setEnabled(false);
        ui->btn_ln->setEnabled(false);

        QString value;
        int realValue;
        value1 = ui->lineEdit->text();

        switch(zflag)
        {
        case 0: realValue = value1.toLong();break;
        case 2: realValue = f2to10(value1);break;
        case 8: realValue = f8to10(value1);break;
        case 16: realValue = f16to10(value1);break;
        }
        //qDebug() << loo;
        value = QString::number(realValue,16).toUpper();
        ui->lineEdit->setText("0x"+value);
        zflag = 16;
    }
}

void MainWindow::on_btn_0_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    //    if(str == "0")
    //        str.clear();
    //    str.append("0");
    //    ui->lineEdit->setText(str);

    //    zh = 0;
    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "0";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x0";
        }else{
            value = "0";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_1_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "1";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x1";
        }else{
            value = "1";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_2_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "2";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x2";
        }else{
            value = "2";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_3_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "3";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x3";
        }else{
            value = "3";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_4_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "4";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x4";
        }else{
            value = "4";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_5_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "5";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x5";
        }else{
            value = "5";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_6_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "6";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x6";
        }else{
            value = "6";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_7_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "7";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x7";
        }else{
            value = "7";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_8_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "8";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x8";
        }else{
            value = "8";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_9_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "9";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0x9";
        }else{
            value = "9";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_10_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "A";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xA";
        }else{
            value = "A";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_11_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "B";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xB";
        }else{
            value = "B";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_12_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "C";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xC";
        }else{
            value = "C";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_13_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "D";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xD";
        }else{
            value = "D";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_14_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "E";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xE";
        }else{
            value = "E";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_15_clicked()
{
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }

    QString val,value;
    val = ui->lineEdit->text();
    if((val != "0")&&(val != "0x0")&&(val != "-inf") && (val != "nan"))
        value = val + "F";
    else
    {
        if(ui->rBtn_16->isChecked())
        {
            value = "0xF";
        }else{
            value = "F";
        }
    }
    ui->lineEdit->setText(value);
}

void MainWindow::on_btn_point_clicked()
{
    //    str.append(".");
    //    ui->lineEdit->setText(str);
    if(flag == 1)
    {
        ui->lineEdit->setText("0");
        flag = 0;
    }
    if (!ui->lineEdit->text().contains("."))
    {
        ui->lineEdit->setText(ui->lineEdit->text() + tr("."));
    }
}

//求相反数
void MainWindow::on_btn_symbol_clicked()
{
    //    if(flag == 1)
    //    {
    //        ui->lineEdit->setText("0");
    //        flag = 0;
    //    }

    QString text = ui->lineEdit->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    ui->lineEdit->setText(text);
}

void MainWindow::on_btn_add_clicked()
{
    //    equal();

    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    ui->lineEdit->setText("+");
    op = 1;
    qDebug()<<"op"<<op<<"+";
    flag = 1;
}

void MainWindow::on_btn_sub_clicked()
{
    //    equal();

    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    ui->lineEdit->setText("-");
    op = 2;
    qDebug()<<"op"<<op<<"-";
    flag = 1;
}

void MainWindow::on_btn_mul_clicked()
{
    //    equal();

    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    ui->lineEdit->setText("*");
    op = 3;
    qDebug()<<"op"<<op<<"*";
    flag = 1;
}

void MainWindow::on_btn_div_clicked()
{
    //    equal();

    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    ui->lineEdit->setText("/");
    op = 4;
    qDebug()<<"op"<<op<<"/";
    flag = 1;
}

//计算结果
void MainWindow::equal()
{
    long llo1 = 0,llo2 = 0;
    int l;

    value2 = ui->lineEdit->text();
    qDebug()<<"value2:::"<<value2;

    flag = 1;
    switch(zflag)
    {
    case 0: //十进制
    {
        switch(op)
        {
        case 1: ui->lineEdit->setText(QString::number(value1.toDouble() + value2.toDouble()));break;
        case 2: ui->lineEdit->setText(QString::number(value1.toDouble() - value2.toDouble()));break;
        case 3: ui->lineEdit->setText(QString::number(value1.toDouble() * value2.toDouble()));break;
        case 4:
        {
            int num = value2.toDouble();
            if(num == 0)
            {
                QMessageBox::warning(this,tr("警告"),tr("0不能为除数！"));
                return;
            }
            ui->lineEdit->setText(QString::number(value1.toDouble() / value2.toDouble()));
            break;
        }
        case 5://求模
        {
            QString tmp = QString::number(value1.toDouble() / value2.toDouble()).section('.',1,1);
            if(tmp.isEmpty())
            {
                tmp.prepend(tr("0.0"));
            }
            else
            {
                tmp.prepend(tr("0."));
            }
            double value = tmp.toDouble() * value2.toDouble();
            while(value < 0.0)
            {
                value = tmp.toDouble() * value2.toDouble();
            }
            ui->lineEdit->setText(QString::number(value));
            break;
        }
        case 6: ui->lineEdit->setText(QString::number(pow(value1.toDouble() , value2.toDouble())));break;
        default : flag = 0; break;
        }
    }break;

    case 2: //二进制
    {
        llo1 = f2to10(value1);
        llo2 = f2to10(value2);
        switch(op)
        {
        case 1: //'+'
        {
            ui->lineEdit->setText(QString::number((llo1 + llo2) ,2));
        }break;
        case 2: //'-'
        {
            ui->lineEdit->setText(QString::number((llo1 - llo2) ,2));
        }break;
        case 3: //'*'
        {
            ui->lineEdit->setText(QString::number((llo1 * llo2) ,2));
        }break;
        case 4: //'/'
        {
            if(llo2 == 0)
            {
                QMessageBox::warning(this,tr("警告"),tr("0不能为除数！"));
                return;
            }
            ui->lineEdit->setText(QString::number((llo1 / llo2) ,2));
        }break;
        case 5: //'与'
        {
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }

            QString zrest(value1.size(),'1');
            qDebug()<<"zrest:"<<zrest;
            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == '0' || value2.at(l) == '0')
                {
                    zrest.replace(l,1,"0");
                    //qDebug()<<zrest;
                }
            }

            ui->lineEdit->setText(zrest);
        }break;
        case 6: //'或'
        {
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');
            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == '1' || value2.at(l) == '1')
                {
                    zrest.replace(l,1,"1");
                    //qDebug()<<zrest;
                }
            }
            ui->lineEdit->setText(zrest);
        }break;
        case 7: //'同或'
        {
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');

            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) != value2.at(l))
                {
                    zrest.replace(l,1,"1");
                    // qDebug()<<zrest;
                }
            }
            ui->lineEdit->setText(zrest);
        }break;
        case 8: //'异或'
        {
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');

            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == value2.at(l))
                {
                    zrest.replace(l,1,"1");
                }
            }
            ui->lineEdit->setText(zrest);
        }break;
        default : flag = 0; break;
        }
    }break;

    case 8: //八进制
    {
        llo1 = f8to10(value1);
        llo2 = f8to10(value2);
        switch(op)
        {
        case 1: ui->lineEdit->setText(QString::number((llo1 + llo2) ,8));break;
        case 2: ui->lineEdit->setText(QString::number((llo1 - llo2) ,8));break;
        case 3: ui->lineEdit->setText(QString::number((llo1 * llo2) ,8));break;
        case 4:
        {
            if(llo2 == 0)
            {
                QMessageBox::warning(this,tr("警告"),tr("0不能为除数！"));
                return;
            }
            ui->lineEdit->setText(QString::number((llo1 / llo2) ,8));
            break;
        }
        default : flag = 0; break;
        }
    }break;

    case 16:    //十六进制
    {
        llo1 = f16to10(value1);
        llo2 = f16to10(value2);
        switch(op)
        {
        case 1: ui->lineEdit->setText("0x"+QString::number((llo1 + llo2) ,16).toUpper());break;
        case 2: ui->lineEdit->setText("0x"+QString::number((llo1 - llo2) ,16).toUpper());break;
        case 3: ui->lineEdit->setText("0x"+QString::number((llo1 * llo2) ,16).toUpper());break;
        case 4:
        {
            if(llo2 == 0)
            {
                QMessageBox::warning(this,tr("警告"),tr("0不能为除数！"));
                return;
            }
            ui->lineEdit->setText("0x"+QString::number((llo1 / llo2) ,16).toUpper());
            break;
        }
        case 5: //'与'
        {
            value1 = f10to2(llo1);
            value2 = f10to2(llo2);
            //qDebug()<<value1;
            //qDebug()<<value2;
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }

            QString zrest(value1.size(),'1');
            // qDebug()<<value1;
            //qDebug()<<value2;
            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == '0' || value2.at(l) == '0')
                {
                    zrest.replace(l,1,"0");
                    //qDebug()<<zrest;
                }
            }
            long rr = f2to10(zrest);
            zrest = QString::number(rr,16).toUpper();
            ui->lineEdit->setText("0x"+zrest);
        }break;
        case 6: //'或'
        {
            value1 = f10to2(llo1);
            value2 = f10to2(llo2);
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');
            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == '1' || value2.at(l) == '1')
                {
                    zrest.replace(l,1,"1");
                    //qDebug()<<zrest;
                }
            }
            long rr = f2to10(zrest);
            zrest = QString::number(rr,16).toUpper();
            ui->lineEdit->setText("0x"+zrest);
        }break;
        case 7: //'同或'
        {
            value1 = f10to2(llo1);
            value2 = f10to2(llo2);
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');

            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) != value2.at(l))
                {
                    zrest.replace(l,1,"1");
                    // qDebug()<<zrest;
                }
            }
            long rr = f2to10(zrest);
            zrest = QString::number(rr,16).toUpper();
            ui->lineEdit->setText("0x"+zrest);
        }break;
        case 8: //'异或'
        {
            value1 = f10to2(llo1);
            value2 = f10to2(llo2);
            if(value1.size()>=value2.size())
            {
                value2 = value2.rightJustified(value1.size(),'0');
            }
            else
            {
                value1 = value1.rightJustified(value2.size(),'0');
            }
            QString zrest(value1.size(),'0');

            for(l=0; l<value1.size(); l++)
            {
                if(value1.at(l) == value2.at(l))
                {
                    zrest.replace(l,1,"1");
                }
            }
            long rr = f2to10(zrest);
            zrest = QString::number(rr,16).toUpper();
            ui->lineEdit->setText("0x"+zrest);
        }break;
        }
    default : flag = 0; break;
        }break;
    }
    value1 = ui->lineEdit->text();
    op = 0;
    //    qDebug()<<"result:::"<<result;
    //    str.clear();
}

//求模
void MainWindow::on_btn_mod_clicked()
{
    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    op = 5;
    qDebug()<<"op"<<op<<"%";
    flag = 1;
}

//求倒数
void MainWindow::on_btn_x_clicked()
{
    value1 = ui->lineEdit->text();
    ui->lineEdit->setText(QString::number(1.0 / value1.toDouble()));
    flag = 1;
}

//开方
void MainWindow::on_btn_sqrt_clicked()
{
    value1 = ui->lineEdit->text();
    ui->lineEdit->setText(QString::number(sqrt(value1.toDouble())));
    flag = 1;
}

//x2
void MainWindow::on_btn_pow_clicked()
{
    value1 = ui->lineEdit->text();
    ui->lineEdit->setText(QString::number(pow(value1.toDouble(), 2)));
    flag = 1;
}

//x^y
void MainWindow::on_btn_nx_clicked()
{
    value1 = ui->lineEdit->text();
    qDebug()<<"value1:::"<<value1;
    //    str.clear();
    op = 6;
    qDebug()<<"op"<<op;
    flag = 1;
}

//取整
void MainWindow::on_btn_int_clicked()
{
    value1 = ui->lineEdit->text();
    ui->lineEdit->setText(value1.split(".").at(0));
    flag = 1;
}

//与
void MainWindow::on_btn_and_clicked()
{
    value1 = ui->lineEdit->text();
    op = 5;
    qDebug()<<"op:::"<<op<<"&";
    flag = 1;
}

//或
void MainWindow::on_btn_or_clicked()
{
    value1 = ui->lineEdit->text();
    op = 6;
    qDebug()<<"op:::"<<op<<"|";
    flag = 1;
}

//同或
void MainWindow::on_btn_tongHuo_clicked()
{
    value1 = ui->lineEdit->text();
    op = 7;
    qDebug()<<"op:::"<<op<<"&&";
    flag = 1;
}

//异或
void MainWindow::on_btn_yiHuo_clicked()
{
    value1 = ui->lineEdit->text();
    op = 8;
    qDebug()<<"op:::"<<op<<"^";
    flag = 1;
}

//矩阵运算槽函数
void MainWindow::on_btn_matrixCal_clicked()
{
    MatrixCal matrixCal;
    matrixCal.exec();
}

//方程计算槽函数
void MainWindow::on_btn_equCal_clicked()
{
    EquCal equCal;
    equCal.exec();
}

//以自然数e为底的对数
void MainWindow::on_btn_ln_clicked()
{
    double value = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(log(value)));
    flag = 1;
}

//画图板
void MainWindow::on_btn_draw_clicked()
{
    Painter *m_pPainter = new Painter;        //画图板的对象m_pPainter;
    m_pPainter->show();
}

//函数绘图
void MainWindow::on_btn_funcDraw_clicked()
{
    FuncDraw funcDraw;
    funcDraw.exec();
}

//以自然数e为底的指数
void MainWindow::on_btn_exp_clicked()
{
    double value = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(exp(value)));
    flag = 1;
}

//退格键
void MainWindow::on_btn_del_clicked()
{
    //    QString val,value;
    //    val = ui->lineEdit->text();
    //    if(val != "0")
    //    {
    //        int size = val.size();
    //        value = val.left(size-1);
    //        if(value.isEmpty())
    //        {
    //            ui->lineEdit->setText("0");
    //        }
    //        else
    //        {
    //            ui->lineEdit->setText(value);
    //        }
    //    }

    QString text = ui->lineEdit->text();
    if(!text.isEmpty())
    {
        text.chop(1);
        if (text.isEmpty())
        {
            text = "0";
        }
        ui->lineEdit->setText(text);
    }
}

//清除输入CE
//键入数字时，按下相应的数字键，如果按错可用（CE）键消去一次数值，再重新输入正确的数字如你要输9*7，
//但你输入了9*8，显示屏显示8（输错了）时，按一下CE键，那么就只是清除了8（显示屏则显示"0"），
//然后你再按7，再按=（显示屏上就会显示63）
void MainWindow::on_btn_CE_clicked()
{
    ui->lineEdit->setText("0");
}

void MainWindow::on_btn_C_clicked()
{
    //    str.clear();
    //    str.append("0");
    if(ui->rBtn_16->isChecked())
    {
        ui->lineEdit->setText("0x0");
    }else{
        ui->lineEdit->setText("0");
    }
    value1 = "0";
    value2 = "0";
}

void MainWindow::on_btn_MC_clicked()
{
    sumInMemory = 0.0;
}

void MainWindow::on_btn_MR_clicked()
{
    ui->lineEdit->setText(QString::number(sumInMemory));
}

void MainWindow::on_btn_MS_clicked()
{
    ui->lineEdit->setText(QString::number(sumInMemory));
}

void MainWindow::on_btn_addM_clicked()
{
    memory = sumInMemory;
    sumInMemory += ui->lineEdit->text().toDouble();
}

void MainWindow::on_btn_subM_clicked()
{
    sumInMemory = memory;
}

//n!
void MainWindow::on_btn_n_clicked()
{
    int value = 1;
    value1 = ui->lineEdit->text();
    if(value1.toDouble() == 0.0)
    {
        ui->lineEdit->setText("1");
    }
    else
    {
        for(int i=1; i<=value1.toDouble(); i++)
        {
            value *= i;
        }
        ui->lineEdit->setText(QString::number(value));
    }
    flag = 1;
}

//π
void MainWindow::on_btn_PI_clicked()
{
    //    QString value = "3.1415926535897932384626433832795";
    QString value = "3.14159";
    ui->lineEdit->setText(value);
}

//关于计算器
void MainWindow::on_aboutCalculate_triggered()
{
    AboutCalculate aboutCal;
    aboutCal.exec();
}

//复制
void MainWindow::on_copy_triggered()
{
    text = ui->lineEdit->text();
    ui->paste->setEnabled(true);
}

//粘贴
void MainWindow::on_paste_triggered()
{
    QString value = ui->lineEdit->text();
    if(value == "0")
    {
        value = text;
    }
    else
    {
        value = value + text;
    }
    ui->lineEdit->setText(value);
}

//剪切
void MainWindow::on_cut_triggered()
{
    text = ui->lineEdit->text();
    ui->lineEdit->setText("0");
    ui->paste->setEnabled(true);
}

//标准型
void MainWindow::on_standard_triggered()
{
    setWindowTitle(tr("标准型"));
    setWindowIcon(QIcon(":/images/standard.png"));
//    ui->rBtn_2->setHidden(true);
//    ui->rBtn_8->setHidden(true);
//    ui->rBtn_10->setHidden(true);
//    ui->rBtn_16->setHidden(true);
    ui->rBtn_10->setChecked(true);
    set10();
    ui->btn_0->setEnabled(true);
    ui->btn_1->setEnabled(true);
    ui->btn_2->setEnabled(true);
    ui->btn_3->setEnabled(true);
    ui->btn_4->setEnabled(true);
    ui->btn_5->setEnabled(true);
    ui->btn_6->setEnabled(true);
    ui->btn_7->setEnabled(true);
    ui->btn_8->setEnabled(true);
    ui->btn_9->setEnabled(true);
    ui->btn_sqrt->setEnabled(true);
    ui->btn_mod->setEnabled(true);
    ui->btn_x->setEnabled(true);
//    ui->btn_10->setHidden(true);
//    ui->btn_11->setHidden(true);
//    ui->btn_12->setHidden(true);
//    ui->btn_13->setHidden(true);
//    ui->btn_14->setHidden(true);
//    ui->btn_15->setHidden(true);
    ui->btn_int->setHidden(true);
    ui->btn_and->setHidden(true);
    ui->btn_or->setHidden(true);
    ui->btn_tongHuo->setHidden(true);
    ui->btn_yiHuo->setHidden(true);
    ui->btn_draw->setHidden(true);
    ui->btn_equCal->setHidden(true);
    ui->btn_matrixCal->setHidden(true);
    ui->btn_exp->setHidden(true);
    ui->btn_ln->setHidden(true);
    ui->btn_PI->setHidden(true);
    ui->btn_pow->setHidden(true);
    ui->btn_nx->setHidden(true);
    ui->btn_n->setHidden(true);
    ui->btn_draw->setHidden(true);
    ui->btn_funcDraw->setHidden(true);
    ui->btn_10x->setHidden(true);
    ui->btn_log->setHidden(true);
    ui->btn_sin->setHidden(true);
    ui->btn_cos->setHidden(true);
    ui->btn_tan->setHidden(true);

    ui->lineEdit->setText("0");
}

//多功能型
void MainWindow::on_multiFunc_triggered()
{
    setWindowTitle(tr("多功能型"));
    setWindowIcon(QIcon(":/images/cal.png"));
//    ui->rBtn_2->setHidden(false);
//    ui->rBtn_8->setHidden(false);
//    ui->rBtn_10->setHidden(false);
    ui->rBtn_10->setChecked(true);
//    ui->rBtn_16->setHidden(false);
//    set10();
    on_rBtn_10_clicked(true);
//    ui->btn_10->setHidden(false);
//    ui->btn_11->setHidden(false);
//    ui->btn_12->setHidden(false);
//    ui->btn_13->setHidden(false);
//    ui->btn_14->setHidden(false);
//    ui->btn_15->setHidden(false);
    ui->btn_int->setHidden(false);
    ui->btn_and->setHidden(false);
    ui->btn_or->setHidden(false);
    ui->btn_tongHuo->setHidden(false);
    ui->btn_yiHuo->setHidden(false);
    ui->btn_draw->setHidden(false);
    ui->btn_equCal->setHidden(false);
    ui->btn_matrixCal->setHidden(false);
    ui->btn_exp->setHidden(false);
    ui->btn_ln->setHidden(false);
    ui->btn_PI->setHidden(false);
    ui->btn_pow->setHidden(false);
    ui->btn_nx->setHidden(false);
    ui->btn_n->setHidden(false);
    ui->btn_draw->setHidden(false);
    ui->btn_funcDraw->setHidden(false);
    ui->btn_10x->setHidden(false);
    ui->btn_log->setHidden(false);
    ui->btn_sin->setHidden(false);
    ui->btn_cos->setHidden(false);
    ui->btn_tan->setHidden(false);

    ui->lineEdit->setText("0");
}

//正弦函数
void MainWindow::on_btn_sin_clicked()
{
    double num = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(sin(num/180.0*3.14159)));     //sin里面的数值需转换成弧度
    flag = 1;
}

//余弦函数
void MainWindow::on_btn_cos_clicked()
{
    double num = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(cos(num/180.0*3.14159)));
    flag = 1;
}

//正切函数
void MainWindow::on_btn_tan_clicked()
{
    double num = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(tan(num/180.0*3.14159)));
    flag = 1;
}

//以10为底的对数
void MainWindow::on_btn_log_clicked()
{
    double num = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(log10(num)));
    flag = 1;
}

//10^x
void MainWindow::on_btn_10x_clicked()
{
    double num = ui->lineEdit->text().toDouble();
    ui->lineEdit->setText(QString::number(pow(10,num)));
    flag = 1;
}

//帮助(help)
void MainWindow::on_Help_triggered()
{
    Help help;
    help.exec();
}

void MainWindow::on_calOnLine_triggered()
{
//    webView->load(QUrl(tr("http://cal.supfree.net/")));
//    webView->show();
}

void MainWindow::on_Browser_triggered()
{
//    Browser *browser = new Browser;
//    browser->show();
}
