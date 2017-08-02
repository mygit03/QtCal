#include "previewlabel.h"

#include <QPainter>

PreviewLabel::PreviewLabel(QWidget *parent) :
    QLabel(parent)
{
}

void PreviewLabel::penChanged(QPen &pen)
{
    curPen = pen;
    update();
}

void PreviewLabel::brushChanged(QBrush &brush)
{
    curBrush = brush;
    update();
}

//接收画笔和画刷改变的信号，并更新预览区域
void PreviewLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(curPen);
    painter.setBrush(curBrush);
    painter.drawRect(rect().x() + 10, rect().y() + 10,
                     rect().width() - 20, rect().height() - 20);
}
