#include "painter.h"

#include <QColorDialog>
#include <QToolBar>
#include <QDockWidget>

Painter::Painter(QWidget *parent) :
    QMainWindow(parent)
{
    init();
}

void Painter::init()
{
    widget = new PainterWidget;//新建一个widget对象作为主窗口的中央窗体
    setCentralWidget(widget);
    createActions();    //创建不同图形的QAction
    createToolBars();   //创建工具条
    creatDockWindows(); //创建调色板

    setWindowTitle(tr("绘图"));
    setWindowIcon(QIcon(":/images/cal.png"));
    setMinimumSize(800,600);    //设置窗口的最小尺寸
    widget->setColor(Qt::blue); //初始化画笔为蓝色s
}

void Painter::draw(QAction *action)
{
    if(action == line)
        widget->setShape(PainterWidget::Line);
    else if(action == rubber)
        widget->setShape(PainterWidget::Rubber);
    else if(action == rectangle)
        widget->setShape(PainterWidget::Rectangle);
    else if(action == ellipse)
        widget->setShape(PainterWidget::Ellipse);
}

void Painter::slotColor()
{
    QColor color = QColorDialog::getColor(Qt::black,this);
    if (color.isValid())
    {
        widget->setColor(color);
        QPixmap p(20,20);   //更新颜色选择按钮上的颜色显示
        p.fill(color);
        colorButton->setIcon(QIcon(p));
    }
}

void Painter::createActions()
{
    line = new QAction(QIcon(":/images/pen.png"),tr("&Line"),this);
    line->setCheckable(true);

    rubber = new QAction(QIcon(":/images/rubber.png"),
                         tr("&Rubber"),this);
    rubber->setCheckable(true);

    rectangle = new QAction(QIcon(":/images/rectangle.png"),
                            tr("&Rectangle"),this);
    rectangle->setCheckable(true);

    ellipse = new QAction(QIcon(":/images/ellipse.png"),
                          tr("&Ellipse"),this);
    ellipse->setCheckable(true);

    drawGroup = new QActionGroup(this);
    drawGroup->addAction(line);
    drawGroup->addAction(rubber);
    drawGroup->addAction(rectangle);
    drawGroup->addAction(ellipse);
    connect(drawGroup,SIGNAL(triggered(QAction*)),this,
            SLOT(draw(QAction*)));
}

void Painter::createToolBars()
{
    QToolBar *toolBar = addToolBar("Tool");
    loadButton = new QToolButton;
    loadButton->setIcon(QIcon(":/images/load.png"));    //打开文件按钮
    toolBar->addWidget(loadButton);
    connect(loadButton,SIGNAL(clicked()),widget,SLOT(loadFormFile()));

    saveButton = new QToolButton;
    saveButton->setIcon(QIcon(":/images/save.png"));    //保存文件按钮
    toolBar->addWidget(saveButton);
    connect(saveButton,SIGNAL(clicked()),widget,SLOT(saveToFile()));

    toolBar->addAction(rectangle);  //绘制矩形
    toolBar->addAction(ellipse);    //绘制椭圆形
    toolBar->addSeparator();

    toolBar->addAction(line);       //画笔
    colorButton = new QToolButton;  //画笔颜色按钮
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::blue);
    colorButton->setIcon(QIcon(pixmap));
    toolBar->addWidget(colorButton);
    connect(colorButton,SIGNAL(clicked()),this,SLOT(slotColor()));
    toolBar->addAction(rubber);
    toolBar->addSeparator();

    clearButton = new QToolButton;  //清屏按钮
    clearButton->setText(tr("clear"));
    toolBar->addWidget(clearButton);
    connect(clearButton,SIGNAL(clicked()),widget,SLOT(clear()));
}

void Painter::creatDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Palette"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    paletteWidget = new Palette(dock);
    dock->setWidget(paletteWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    connect(paletteWidget, SIGNAL(penChanged(QPen&)), widget,
            SLOT(penChanged(QPen&)));
    connect(paletteWidget, SIGNAL(brushChanged(QBrush&)), widget,
            SLOT(brushChanged(QBrush&)));
}
