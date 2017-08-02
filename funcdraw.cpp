#include "funcdraw.h"
#include "ui_funcdraw.h"

FuncDraw::FuncDraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuncDraw)
{
    ui->setupUi(this);

    //m_pPainter = new Painter(ui->widget);
    m_pPlotter = new Plotter(ui->widget);
    m_pPlotter->setWindowTitle("函数绘图");
    m_PHBoxLayout = new QHBoxLayout;
    m_PHBoxLayout->addWidget(m_pPlotter);

    ui->widget->setLayout(m_PHBoxLayout);

    ui->doubleSpinBox_a->setMinimum(-1000);
    ui->doubleSpinBox_a->setValue(1);
    ui->doubleSpinBox_b->setMinimum(-1000);
    ui->doubleSpinBox_b->setValue(2);
    ui->doubleSpinBox_c->setMinimum(-1000);
    ui->doubleSpinBox_c->setValue(1);
    ui->spinBox->setMinimum(5);
}

FuncDraw::~FuncDraw()
{
    delete ui;
}

void FuncDraw::on_btn_FuncDraw_clicked()
{

    float a = ui->doubleSpinBox_a->value();
    float b = ui->doubleSpinBox_b->value();
    float c = ui->doubleSpinBox_c->value();

    int num = ui->spinBox->value();
    QString line=ui->lineEdit->text();
    QStringList fields=line.split(',');

    int numOfList = fields.length();
    if(numOfList != num)
    {
        QMessageBox::warning(this, tr("My Application"),
                             tr("X个数和实际输入的X个数不一致"),
                             QMessageBox::Save | QMessageBox::Discard
                             | QMessageBox::Cancel,
                             QMessageBox::Save);
    }else
    {
        float* xBuf = new float[num];
        float* yBuf = new float[num];


        for(int i = 0 ; i < num ; i++)
        {
            //qDebug()<<fields.at(i)<<endl;
            xBuf[i]=fields.at(i).toFloat();
            yBuf[i]=a*xBuf[i]*xBuf[i]+b*xBuf[i]+c;
        }

        Draw myDrawCurve(600,400);
        myDrawCurve.drawPoint(xBuf,yBuf,num,xBuf,yBuf,num);
        myDrawCurve.exec();
    }
}
