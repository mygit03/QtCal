#include "painterwidget.h"

PainterWidget::PainterWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void PainterWidget::init()
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));    //画板背景色初始化为白色

    bufferImage = QImage(this->width(),this->height(),
                         QImage::Format_ARGB32);
    bufferImage.fill(Qt::white);
    tempImage = QImage(this->width(),this->height(),
                       QImage::Format_ARGB32);
    setMinimumSize(800,600);    //绘制区窗体的最小尺寸
}

void PainterWidget::setShape(PainterWidget::ShapeType shape)
{
    if(shape != curShape)
    {
        curShape = shape;
    }
}

void PainterWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   //判断是否鼠标左键按下，进入绘图状态
    {
        switch(curShape)   //准备要绘制的图形
        {
        case Line:
        case Rubber:
        {
            startPoint = event->pos();  //记录起点位置
            break;
        }
        case Rectangle:
        case Ellipse:
        {
            bDrawing = true;
            x = event->x();
            y = event->y();
            break;
        }
        }
    }
}

void PainterWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton) //判断移动鼠标时，左键是否一直按下去
    {
        QPainter painter(&bufferImage); //定义一个在bufferImage上绘图的painter
        switch(curShape)
        {
        case Line:
        {
            QPen pen;
            pen.setColor(color); //设置画笔的颜色
            painter.setPen(pen);
            endPoint=event->pos(); //记录终点位置
            painter.drawLine(startPoint,endPoint);
            startPoint=endPoint; //更新鼠标当前位置，为下次绘制做准备
            break;
        }
        case Rubber:
        {
            painter.setPen(QPen(Qt::white,20));  //橡皮擦其实是画笔颜色为白色，线宽为20的画笔
            endPoint=event->pos();
            painter.drawLine(startPoint,endPoint);
            startPoint=endPoint;
            break;
        }
        case Rectangle:
        case Ellipse:
        {
            w = event->x() - x;
            h = event->y() - y;
            break;
        }
        }
        tempImage = bufferImage;
        paint(tempImage);
        update();   //强迫窗口重绘
    }
}

void PainterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    bDrawing = false;
    paint(bufferImage);
}

void PainterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(bDrawing)
    {
        painter.drawImage(0,0,tempImage);
    }else
    {
        painter.drawImage(0,0,bufferImage);
    }
}

void PainterWidget::paint(QImage &image)
{
    QPainter painter(&image);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    switch(curShape){
    case Line:
    case Rubber:
        painter.drawLine(startPoint,endPoint);
        break;
    case Rectangle:
        painter.drawRect(x,y,w,h);
        break;
    case Ellipse:
        painter.drawEllipse(x,y,w,h);
        break;
    }
    update();
}

void PainterWidget::setColor(QColor c)
{
    color = c;
}

void PainterWidget::clear()
{
    clearImage = QImage(this->width(),this->height(),QImage::Format_ARGB32);
    clearImage.fill(Qt::white);
    bufferImage = clearImage;
    update();
}

void PainterWidget::penChanged(QPen &pen)
{
    curPen = pen;
}

void PainterWidget::brushChanged(QBrush &brush)
{
    curBrush = brush;
}

void PainterWidget::loadFormFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),":/",tr("Images (*.png *.xpm *.jpg)"));
    bufferImage.load(fileName);
    update();
}

void PainterWidget::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),":/untitled.png",tr("Images (*.png *.xpm *.jpg)"));
    bufferImage.save(fileName);
}
