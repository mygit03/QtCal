#ifndef PREVIEWLABEL_H
#define PREVIEWLABEL_H

#include <QLabel>
#include <QPen>

class PreviewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PreviewLabel(QWidget *parent = 0);

signals:

public slots:
    void penChanged(QPen& pen);                 //画笔改变
    void brushChanged(QBrush& brush);           //画刷改变

protected:
    void paintEvent(QPaintEvent *event);        //绘图事件

private:
    QPen curPen;                                //当前画笔
    QBrush curBrush;                            //当前画刷
};

#endif // PREVIEWLABEL_H
