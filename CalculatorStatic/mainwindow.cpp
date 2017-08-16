#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QDateTime>

#include "aboutcalculate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *menu1 = new QMenu(tr("查看"),this);
    QAction *act_0 = new QAction(tr("aaa"),this);
    QAction *act_1 = new QAction(tr("bbb"),this);
    QActionGroup *actGrp = new QActionGroup(this);
    QList<QAction*> actList1;
    actList1.clear();
    actList1 << act_0 << act_1;
    menu1->addActions(actList1);
    ui->menuBar->addMenu(menu1);

    QMenu *menu2 = new QMenu(tr("编辑"),this);
    QAction *act_copy = new QAction(QIcon(":/images/copy.png"),tr("copy"),this);
    connect(act_copy, SIGNAL(triggered(bool)), this, SLOT(slot_copy()));
    QAction *act_paste = new QAction(QIcon(":/images/paste.png"),tr("paste"),this);
    connect(act_paste, SIGNAL(triggered(bool)), this, SLOT(slot_paste()));
    QList<QAction*> actList2;
    actList2.clear();
    actList2 << act_copy << act_paste;
    menu2->addActions(actList2);
    ui->menuBar->addMenu(menu2);

    QMenu *menu3 = new QMenu(tr("关于"),this);
    QAction *act_about = new QAction(QIcon(":/images/help.png"),tr("About"),this);
    connect(act_about, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
    QAction *act_qt = new QAction(QIcon(":/images/standard.png"),tr("Qt"),this);
    connect(act_qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    QList<QAction*> actList3;
    actList3.clear();
    actList3 << act_about << act_qt;
    menu3->addActions(actList3);
    ui->menuBar->addMenu(menu3);

    ui->mainToolBar->hide();

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    setMaximumSize(widget->size());

    QGridLayout *gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(5);

    lineEdit = new QLineEdit(tr("0"), widget);
    lineEdit->setMinimumHeight(30);
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignRight);

    btn_0 = new QPushButton(tr("0"), widget);
    btn_0->setMaximumSize(75,35);
    btn_0->setMinimumSize(75,35);
    btn_1 = new QPushButton(tr("1"), widget);
    btn_1->setMaximumSize(35,35);
    btn_1->setMinimumSize(35,35);
    btn_2 = new QPushButton(tr("2"), widget);
    btn_2->setMaximumSize(35,35);
    btn_2->setMinimumSize(35,35);
    btn_3 = new QPushButton(tr("3"), widget);
    btn_3->setMaximumSize(35,35);
    btn_3->setMinimumSize(35,35);
    btn_4 = new QPushButton(tr("4"), widget);
    btn_4->setMaximumSize(35,35);
    btn_4->setMinimumSize(35,35);
    btn_5 = new QPushButton(tr("5"), widget);
    btn_5->setMaximumSize(35,35);
    btn_5->setMinimumSize(35,35);
    btn_6 = new QPushButton(tr("6"), widget);
    btn_6->setMaximumSize(35,35);
    btn_6->setMinimumSize(35,35);
    btn_7 = new QPushButton(tr("7"), widget);
    btn_7->setMaximumSize(35,35);
    btn_7->setMinimumSize(35,35);
    btn_8 = new QPushButton(tr("8"), widget);
    btn_8->setMaximumSize(35,35);
    btn_8->setMinimumSize(35,35);
    btn_9 = new QPushButton(tr("9"), widget);
    btn_9->setMaximumSize(35,35);
    btn_9->setMinimumSize(35,35);
    btn_point = new QPushButton(tr("·"), widget);
    btn_point->setMaximumSize(35,35);
    btn_point->setMinimumSize(35,35);
    btn_div = new QPushButton(tr("/"), widget);
    btn_div->setMaximumSize(35,35);
    btn_div->setMinimumSize(35,35);
    btn_mul = new QPushButton(tr("*"), widget);
    btn_mul->setMaximumSize(35,35);
    btn_mul->setMinimumSize(35,35);
    btn_sub = new QPushButton(tr("-"), widget);
    btn_sub->setMaximumSize(35,35);
    btn_sub->setMinimumSize(35,35);
    btn_add = new QPushButton(tr("+"), widget);
    btn_add->setMaximumSize(35,35);
    btn_add->setMinimumSize(35,35);
    btn_mod = new QPushButton(tr("%"), widget);
    btn_mod->setMaximumSize(35,35);
    btn_mod->setMinimumSize(35,35);
    btn_x = new QPushButton(tr("1/x"), widget);
    btn_x->setMaximumSize(35,35);
    btn_x->setMinimumSize(35,35);
    btn_equal = new QPushButton(tr("="), widget);
    btn_equal->setMaximumSize(35,75);
    btn_equal->setMinimumSize(35,75);
    btn_back = new QPushButton(tr("Back"), widget);
    btn_back->setMaximumSize(35,35);
    btn_back->setMinimumSize(35,35);
    btn_CE = new QPushButton(tr("CE"), widget);
    btn_CE->setMaximumSize(35,35);
    btn_CE->setMinimumSize(35,35);
    btn_C = new QPushButton(tr("C"), widget);
    btn_C->setMaximumSize(35,35);
    btn_C->setMinimumSize(35,35);
    btn_symbol = new QPushButton(tr("±"), widget);
    btn_symbol->setMaximumSize(35,35);
    btn_symbol->setMinimumSize(35,35);
    btn_sqrt = new QPushButton(tr("x²"), widget);
    btn_sqrt->setMaximumSize(35,35);
    btn_sqrt->setMinimumSize(35,35);

    gridLayout->addWidget(lineEdit,0,0,1,5);
    gridLayout->addWidget(btn_back,1,0,1,1);
    gridLayout->addWidget(btn_CE,1,1,1,1);
    gridLayout->addWidget(btn_C,1,2,1,1);
    gridLayout->addWidget(btn_symbol,1,3,1,1);
    gridLayout->addWidget(btn_sqrt,1,4,1,1);
    gridLayout->addWidget(btn_7,2,0,1,1);
    gridLayout->addWidget(btn_8,2,1,1,1);
    gridLayout->addWidget(btn_9,2,2,1,1);
    gridLayout->addWidget(btn_div,2,3,1,1);
    gridLayout->addWidget(btn_mod,2,4,1,1);
    gridLayout->addWidget(btn_4,3,0,1,1);
    gridLayout->addWidget(btn_5,3,1,1,1);
    gridLayout->addWidget(btn_6,3,2,1,1);
    gridLayout->addWidget(btn_mul,3,3,1,1);
    gridLayout->addWidget(btn_x,3,4,1,1);
    gridLayout->addWidget(btn_1,4,0,1,1);
    gridLayout->addWidget(btn_2,4,1,1,1);
    gridLayout->addWidget(btn_3,4,2,1,1);
    gridLayout->addWidget(btn_sub,4,3,1,1);
    gridLayout->addWidget(btn_equal,4,4,2,1);
    gridLayout->addWidget(btn_0,5,0,1,2);
    gridLayout->addWidget(btn_point,5,2,1,1);
    gridLayout->addWidget(btn_add,5,3,1,1);

    connect(btn_0, SIGNAL(clicked(bool)), this, SLOT(slot_btn0()));
    connect(btn_1, SIGNAL(clicked(bool)), this, SLOT(slot_btn1()));
    connect(btn_2, SIGNAL(clicked(bool)), this, SLOT(slot_btn2()));
    connect(btn_3, SIGNAL(clicked(bool)), this, SLOT(slot_btn3()));
    connect(btn_4, SIGNAL(clicked(bool)), this, SLOT(slot_btn4()));
    connect(btn_5, SIGNAL(clicked(bool)), this, SLOT(slot_btn5()));
    connect(btn_6, SIGNAL(clicked(bool)), this, SLOT(slot_btn6()));
    connect(btn_7, SIGNAL(clicked(bool)), this, SLOT(slot_btn7()));
    connect(btn_8, SIGNAL(clicked(bool)), this, SLOT(slot_btn8()));
    connect(btn_9, SIGNAL(clicked(bool)), this, SLOT(slot_btn9()));
    connect(btn_point, SIGNAL(clicked(bool)), this, SLOT(slot_btnPoint()));
    connect(btn_symbol, SIGNAL(clicked(bool)), this, SLOT(slot_btnSymBol()));
    connect(btn_back, SIGNAL(clicked(bool)), this, SLOT(slot_btnBack()));
    connect(btn_CE, SIGNAL(clicked(bool)), this, SLOT(slot_btnCE()));
    connect(btn_C, SIGNAL(clicked(bool)), this, SLOT(slot_btnC()));
    connect(btn_x, SIGNAL(clicked(bool)), this, SLOT(slot_btnX()));
    connect(btn_sqrt, SIGNAL(clicked(bool)), this, SLOT(slot_btnPow()));
    connect(btn_add, SIGNAL(clicked(bool)), this, SLOT(slot_btnAdd()));
    connect(btn_sub, SIGNAL(clicked(bool)), this, SLOT(slot_btnSub()));
    connect(btn_mul, SIGNAL(clicked(bool)), this, SLOT(slot_btnMul()));
    connect(btn_div, SIGNAL(clicked(bool)), this, SLOT(slot_btnDiv()));
    connect(btn_mod, SIGNAL(clicked(bool)), this, SLOT(slot_btnMod()));
    connect(btn_equal, SIGNAL(clicked(bool)), this, SLOT(slot_btnEqual()));

    flag = false;
    board = QApplication::clipboard();
    m_timer.start(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_showTime()));

    label = new QLabel(ui->statusBar);
    label->setAlignment(Qt::AlignRight);
    label->setMinimumWidth(200);
    label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_btn0()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("0");
        lineEdit->setText(value);
    }
}

void MainWindow::slot_btn1()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("1");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("1");
    }
}

void MainWindow::slot_btn2()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("2");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("2");
    }
}

void MainWindow::slot_btn3()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("3");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("3");
    }
}

void MainWindow::slot_btn4()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("4");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("4");
    }
}

void MainWindow::slot_btn5()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("5");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("5");
    }
}

void MainWindow::slot_btn6()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("6");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("6");
    }
}

void MainWindow::slot_btn7()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("7");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("7");
    }
}

void MainWindow::slot_btn8()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("8");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("8");
    }
}

void MainWindow::slot_btn9()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(value.compare("0") != 0){
        value.append("9");
        lineEdit->setText(value);
    }else{
        lineEdit->setText("9");
    }
}

void MainWindow::slot_btnPoint()
{
    if(flag){
        lineEdit->setText("0");
        flag = false;
    }
    QString value = lineEdit->text();
    if(!value.contains(".")){
        value.append(".");
        lineEdit->setText(value);
    }
}

void MainWindow::slot_btnSymBol()
{
    QString text = lineEdit->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    lineEdit->setText(text);
}

void MainWindow::slot_btnBack()
{
    QString value = lineEdit->text();
    if(value.length()>1){
        value.chop(1);
        lineEdit->setText(value);
    }
}

void MainWindow::slot_btnCE()
{
    lineEdit->setText("0");
}

void MainWindow::slot_btnC()
{
    lineEdit->setText("0");
}

void MainWindow::slot_btnX()
{
    double value = lineEdit->text().toDouble();
    if(value != 0){
        value = 1.0 / value;
        lineEdit->setText(QString::number(value));
    }
}

void MainWindow::slot_btnPow()
{
    double value = lineEdit->text().toDouble();
    value = pow(value, 2);
    lineEdit->setText(QString::number(value));
}

void MainWindow::slot_btnAdd()
{
    flag = true;
    op = 1;
    value1 = lineEdit->text().toDouble();
    lineEdit->setText("+");
}

void MainWindow::slot_btnSub()
{
    flag = true;
    op = 2;
    value1 = lineEdit->text().toDouble();
    lineEdit->setText("-");
}

void MainWindow::slot_btnMul()
{
    flag = true;
    op = 3;
    value1 = lineEdit->text().toDouble();
    lineEdit->setText("*");
}

void MainWindow::slot_btnDiv()
{
    flag = true;
    op = 4;
    value1 = lineEdit->text().toDouble();
    lineEdit->setText("/");
}

void MainWindow::slot_btnMod()
{
    flag = true;
    op = 5;
    value1 = lineEdit->text().toDouble();
    lineEdit->setText("%");
}

void MainWindow::slot_btnEqual()
{
    flag = true;
    value2 = lineEdit->text().toDouble();
    qDebug() << "value1:" << value1 << "value2:" << value2;

    switch (op) {
    case 1:
        value = m_plus.add(value1, value2);
        break;
    case 2:
        value = m_plus.sub(value1, value2);
        break;
    case 3:
        value = m_plus.mul(value1, value2);
        break;
    case 4:
        value = m_plus.div(value1, value2);
        break;
    case 5:
        value = m_plus.mod(value1, value2);
        break;
    default:
        break;
    }
    lineEdit->setText(QString::number(value));
}

void MainWindow::slot_about()
{
    AboutCalculate aboutDialog;
    aboutDialog.exec();
}

void MainWindow::slot_copy()
{
    board->setText(lineEdit->text());
}

void MainWindow::slot_paste()
{
    lineEdit->setText(board->text());
}

void MainWindow::slot_showTime()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss");
    ui->statusBar->setToolTip(time);
    label->setText(time);
    qDebug() << "time:" << time;
}
