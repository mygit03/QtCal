#ifndef ABOUTCALCULATE_H
#define ABOUTCALCULATE_H

#include <QDialog>

namespace Ui {
class AboutCalculate;
}

class AboutCalculate : public QDialog
{
    Q_OBJECT

public:
    explicit AboutCalculate(QWidget *parent = 0);
    ~AboutCalculate();

private:
    Ui::AboutCalculate *ui;
};

#endif // ABOUTCALCULATE_H
