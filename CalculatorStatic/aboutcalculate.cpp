#include "aboutcalculate.h"
#include "ui_aboutcalculate.h"

AboutCalculate::AboutCalculate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutCalculate)
{
    ui->setupUi(this);
}

AboutCalculate::~AboutCalculate()
{
    delete ui;
}
