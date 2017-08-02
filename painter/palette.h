#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QPainter>

#include "previewlabel.h"
#include "penstyledelegate.h"

class Palette : public QWidget
{
    Q_OBJECT
public:
    explicit Palette(QWidget *parent = 0);

    void init();                    //初始化
    void connectSignals();          //关联信号和槽

private:
    void createColorComboBox(QComboBox *comboBox);
    void createStyleComboBox();

signals:
    void penChanged(QPen& pen);  //当画笔发生改变时发出penChanged信号
    void brushChanged(QBrush& brush);//当画刷发生改变时发出brushChanged信号

public slots:
    void penChanged();
    void brushChanged();

private:
    QLabel *penColorLabel;
    QLabel *penWidthLabel;
    QLabel *penStyleLabel;
    QLabel *brushColorLabel;
    QLabel *brushStyleLabel;
    PreviewLabel *preLabel;                 //预览标签类的对象
    QSpinBox *penWidthSpinBox;              //画笔宽度
    QComboBox *penColorComboBox;            //画笔颜色
    QComboBox *penStyleComboBox;            //画笔风格
    QComboBox *brushColorComboBox;          //画刷颜色
    QComboBox *brushStyleComboBox;          //画刷风格
};

#endif // PALETTE_H
