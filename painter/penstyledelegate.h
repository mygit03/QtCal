#ifndef PENSTYLEDELEGATE_H
#define PENSTYLEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QPainter>

class PenStyleDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit PenStyleDelegate(QObject *parent = 0);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

signals:

public slots:

};

#endif // PENSTYLEDELEGATE_H
