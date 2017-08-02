#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPen>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PainterWidget(QWidget *parent = 0);

    enum ShapeType {    //枚举准备绘制的图形
        Line,
        Rubber,
        Rectangle,
        Ellipse
    };

    void init();                        //初始化

    void setShape(ShapeType shape);

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

private:
    void paint(QImage &image);

signals:

public slots:
    void setColor(QColor c);
    void clear();
    void penChanged(QPen& pen);
    void brushChanged(QBrush& brush);
    void loadFormFile();
    void saveToFile();

protected:
    bool bDrawing;      //true:绘制临时缓冲区的图形，false:绘制存储的图形
    int x,y,w,h;        //x，y坐标以及宽高

private:
    QImage bufferImage;         //用来存储最终的图形
    QImage tempImage;           //临时缓冲区
    QImage clearImage;          //清屏时用的图片
    ShapeType curShape;
    QPen curPen;
    QBrush curBrush;
    QPoint startPoint;          //起始点
    QPoint endPoint;            //终点
    QColor color;
};

#endif // PAINTERWIDGET_H
