#ifndef PAINTER_H
#define PAINTER_H

#include <QMainWindow>
#include <QToolButton>
#include <QActionGroup>

#include "palette.h"
#include "painterwidget.h"

class Painter : public QMainWindow
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);

    void init();                    //初始化

signals:

public slots:
    void draw(QAction* action);
    void slotColor();

private:
    void createActions();
    void createToolBars();
    void creatDockWindows();

private:
    Palette *paletteWidget;
    PainterWidget *widget;
    QToolButton *colorButton;
    QToolButton *clearButton;
    QToolButton *loadButton;
    QToolButton *saveButton;
    QAction *line;
    QAction *rubber;
    QAction *rectangle;
    QAction *ellipse;
    QActionGroup *drawGroup;
};

#endif // PAINTER_H
