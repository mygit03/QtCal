#include "penstyledelegate.h"

PenStyleDelegate::PenStyleDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void PenStyleDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
//    QString text = index.data(Qt::DisplayRole).toString();
    Qt::PenStyle penStyle = (Qt::PenStyle)index.data(Qt::UserRole).toInt();
    QRect r = option.rect;

    if (option.state & QStyle::State_Selected) {
        painter->save();                                            //保存
        painter->setBrush(option.palette.highlight());
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);                             //绘制
        painter->setPen(QPen(option.palette.highlightedText(),2,
                             penStyle));                            //设置画笔
    }
    else
        painter->setPen(penStyle);
    painter->drawLine(0, r.y() + r.height()/2, r.right(),
                      r.y() + r.height()/2);                        //绘制线

    if (option.state & QStyle::State_Selected)
        painter->restore();             //恢复上一次保存的结果
}

QSize PenStyleDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    return QSize(100,30);
}
