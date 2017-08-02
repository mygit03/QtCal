//*******************************************************
//                     曲线绘制类
//*******************************************************
// PROGRAM NAME : plotter.cpp
// 描述:可以进行放大缩小  不同范围数据只需在类中做简单修改即可
//=======================================================
//
//*******************************************************

#include "plotter.h"
#include "ui_plotter.h"

Plotter::Plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);

    Margin =40;
    setBackgroundRole(QPalette::Dark);//设置曲线图使用”暗“分量显示
    setAutoFillBackground(true);//设置是否自动填充背景色
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//设置窗口不见可缩放，在X,Y方向均如此
    setFocusPolicy(Qt::StrongFocus);//设置焦点
    rubberBandIsShown = false;//鼠标圈住的橡皮筋区域是否显示

    zoomInButton = new QToolButton(this);//创建一个放大按钮
    zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));//设置信号和槽的连接

    zoomOutButton = new QToolButton(this);//创建一个缩小按钮
    zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));//设置信号和槽的连接

    BeginTime="";

    setPlotSettings(PlotSettings());
}

Plotter::~Plotter()
{
    delete ui;

    delete zoomInButton;
    delete zoomOutButton;
}

void Plotter::setPlotSettings(const PlotSettings &settings)
{
    zoomStack.clear();//清空堆栈
    zoomStack.append(settings);//重新加载绘图设置
    curZoom = 0;//默认缩放级别是0，未缩放
    zoomInButton->hide();//隐藏放大按钮
    zoomOutButton->hide();//隐藏缩小按钮
    refreshPixmap();//刷新图像区域
}

//设置给定曲线的ID号，若存在，则替换原数据，若不存在，则插入新曲线
void Plotter::setCurveData(const QVector<QPointF> &data)
{
    curveMap = data;//成员类型为QMap<int,QVector<QPointF>>
    refreshPixmap();//刷新图像
}

QSize Plotter::minimumSizeHint() const
{
    return QSize(6 * Margin, 4 * Margin);
}

//指定窗口部件理想大小
QSize Plotter::sizeHint() const
{
    return QSize(12 * Margin, 8 * Margin);
}

//设置Y轴最大最小值和X轴点数
void Plotter::setCorrds(double x, double y, int z, int hx)
{
    //调用函数，将按钮设置成给定的大小
    setPlotSettings(PlotSettings(x,y,z,hx));
}

//设置起始刻度
void Plotter::SetBeginTime(QString data)
{
    BeginTime=data;
}

void Plotter::zoomIn()
{
    if (curZoom < zoomStack.count() - 1)//当前缩放级别小于可放大的最大级别
    {
        ++curZoom;
        //检测是否已经到最高放大级别，若是，放大按钮不可用，若不是，放大按钮可用
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);//将缩小按钮设置为可用
        zoomOutButton->show();//显示缩小按钮
        refreshPixmap();//刷新图像区域
    }
}

void Plotter::zoomOut()
{
    if (curZoom > 0)//当前图像经过了放大
    {
        --curZoom;
        //检测当前缩放级别，若放大，则缩小按钮可用，反之，不可用
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);//设置放大按钮可用
        zoomInButton->show();//显示放大按钮
        refreshPixmap();//刷新图像区域
    }
}

//将refreshPixmap中绘制好的图像，复制到窗口部件的（0，0）位置
void Plotter::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
    if (rubberBandIsShown)//橡皮筋选择框显示中
    {
        painter.setPen(palette().light().color());
        //橡皮筋选择区域显示亮背景，以区别于整个图片区域
        painter.drawRect(rubberBandRect.normalized().adjusted(0, 0, -1, -1));//确保
    }
    if (hasFocus())//判断绘图区域是否拥有焦点
    {
        QStyleOptionFocusRect option;//焦点区域的风格设置
        option.initFrom(this);//按照控件风格初始化焦点框
        option.backgroundColor = palette().dark().color();//设置焦点框颜色
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);//控制焦点框，背景，曲线图等控件
    }
}

//当窗口部件大小改变的时候，通过该函数实现绘图区域的大小重定义
void Plotter::resizeEvent(QResizeEvent *event)
{
    //将缩放按钮放在窗口的右上角
    int x = width() - (zoomInButton->width() + zoomOutButton->width() + 10);
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin, Margin,width() - 2 * Margin, height() - 2 * Margin);
    //左键按下
    if (event->button() == Qt::LeftButton)
    {//显示橡皮筋小框框
        if (rect.contains(event->pos()))
        {
            rubberBandIsShown = true;
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);//设置鼠标形状
        }
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
    if (rubberBandIsShown)//鼠标左键已经按下
    {
        updateRubberBandRegion();//更新橡皮筋的大小
        rubberBandRect.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标圈出橡皮筋并且释放
    if ((event->button() == Qt::LeftButton) && rubberBandIsShown)
    {
        rubberBandIsShown = false;//橡皮筋不再显示
        updateRubberBandRegion();//更新橡皮筋
        unsetCursor();//改变鼠标形状

        QRect rect = rubberBandRect.normalized();//取得橡皮筋区域
        if (rect.width() < 4 || rect.height() < 4)//橡皮筋区域小于4X4不作任何操作
            return;
        rect.translate(-Margin, -Margin);//移动画布
        PlotSettings prevSettings = zoomStack[curZoom]; //更改缩放级别
        PlotSettings settings;
        //更改坐标轴长度
        double dx = prevSettings.spanX() / (width() - 2 * Margin);
        double dy = prevSettings.spanY() / (height() - 2 * Margin);
        settings.minX = prevSettings.minX + dx * rect.left();
        settings.maxX = prevSettings.minX + dx * rect.right();
        settings.minY = prevSettings.maxY - dy * rect.bottom();
        settings.maxY = prevSettings.maxY - dy * rect.top();
        settings.adjust();
        //将当前缩放大小压栈并完成放大
        zoomStack.resize(curZoom + 1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:  //+号键
        zoomIn();
        break;
    case Qt::Key_Minus:  //-号键
        zoomOut();
        break;
    case Qt::Key_Left: //方向键左
        zoomStack[curZoom].scroll(-1,0);
        refreshPixmap();
        break;
    case Qt::Key_Right:  //方向键右
        zoomStack[curZoom].scroll(+1,0);
        refreshPixmap();
        break;
    case Qt::Key_Down:  //方向键下
        zoomStack[curZoom].scroll(0,-1);
        refreshPixmap();
        break;
    case Qt::Key_Up:    //方向键上
        zoomStack[curZoom].scroll(0,+1);
        refreshPixmap();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Plotter::wheelEvent(QWheelEvent *event)
{
    int numDegrees=event->delta()/8;  //滚轮转动的距离等于角度的8倍
    int numTicks=numDegrees/15;   //滚轮步长为15
    if (event->orientation()==Qt::Horizontal)  //滚轮水平滚动
        zoomStack[curZoom].scroll(numTicks,0);
    else
        zoomStack[curZoom].scroll(0,numTicks);  //滚轮垂直滚动
    refreshPixmap();
}

//完成对橡皮筋的绘制，重绘，擦除
void Plotter::updateRubberBandRegion()
{
    QRect rect=rubberBandRect.normalized();
    update(rect.left(),rect.top(),rect.width(),1);
    update(rect.left(),rect.top(),1,rect.height());
    update(rect.left(),rect.bottom(),rect.width(),1);
    update(rect.right(),rect.top(),1,rect.height());
}

//将绘图区重新绘制到内存的脱屏像素映射上，并更新
void Plotter::refreshPixmap()
{
    //定义一个和绘图区一样大小的画布
    pixmap=QPixmap(size());
    pixmap.fill(this,0,0);
    //从绘图区获取图形，并绘制到脱屏像素上，更新
    QPainter painter(&pixmap);
    painter.initFrom(this);
    drawGrid(&painter);
    drawCurves(&painter);
    update();
}

//用来绘制坐标系后面的网格
void Plotter::drawGrid(QPainter *painter)
{
    QRect rect;
    //取得绘图区域，大小要减去旁白
    if (Margin==40)
        rect=QRect(Margin+25,Margin,width()-2*Margin-10,height()-2*Margin);
    else
        rect=QRect(Margin+45,Margin,width()-2*Margin-50,height()-2*Margin);
    if (!rect.isValid())  //获取失败
        return;
    //设置缩放级别，背景色，画笔颜色，画笔风格
    PlotSettings settings=zoomStack[curZoom];
    QPen quiteDark=palette().dark().color().light();
    QPen light=palette().light().color();
    light.setWidth(2);
    QString str_tail,tempstr;
    int int_head;
    if (BeginTime!="")
    {
        tempstr=BeginTime;
        str_tail=tempstr.left(2);
        tempstr.remove(0,2);
        int_head=tempstr.toInt();
    }

    //绘制X轴上的网格和坐标
    for (int i=0;i<=settings.numXTicks;++i)
    {
        int x=rect.left()+(i*(rect.width()-1)/settings.numXTicks);
        double label=settings.minX+(i*settings.spanX()/settings.numXTicks);
        painter->setPen(quiteDark);
        painter->drawLine(x,rect.top(),x,rect.bottom());
        //横坐标只显示整数的坐标点，防止坐标过密，文字连在一起看不清
        if ((int)label==label)
        {
            if (i!=settings.numXTicks)
            {
                if (Margin==40)
                    if (BeginTime=="")
                        painter->drawText(x-Margin+15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,QString::number(label));
                    else
                    {
                        int tempint;
                        label=label+int_head;
                        tempint=(int)label;
                        tempint=tempint%24;
                        tempstr=QString::number(tempint);
                        tempstr.append(":");
                        tempstr.append(str_tail);
                        painter->drawText(x-Margin+15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,tempstr);
                    }
                else
                    if (BeginTime=="")
                        painter->drawText(x-Margin-15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,QString::number(label));
                    else
                    {
                        int tempint;
                        label=label+int_head;
                        tempint=(int)label;
                        tempint=tempint%24;
                        tempstr=QString::number(tempint);
                        tempstr.append(":");
                        tempstr.append(str_tail);
                        painter->drawText(x-Margin-15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,tempstr);
                    }
            }
            else
            {
                int tempint;
                if (BeginTime!="")
                {
                    label=label+int_head;
                    tempstr.append(":");
                    tempstr.append(str_tail);
                    tempint=(int)label;
                    tempint=tempint%24;
                    tempstr=QString::number(tempint);
                    tempstr.append(tr("(X轴)"));
                }
                else
                {
                    tempint=(int)label;
                    tempstr=QString::number(tempint);
                    tempstr.append(tr("(X轴)"));
                }
                if (Margin==40)
                    painter->drawText(x-Margin+15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,tempstr);
                else
                    painter->drawText(x-Margin-15,rect.bottom()+5,60,20,Qt::AlignHCenter|Qt::AlignTop,tempstr);
            }
        }
    }

    //绘制Y轴上的网格和坐标
    for (int j=0;j<=settings.numYTicks;++j)
    {
        if (settings.numYTicks==0)
            settings.numYTicks=10;
        int y=rect.bottom()-(j*(rect.height()-1)/settings.numYTicks);
        double label=settings.minY+(j*settings.spanY()/settings.numYTicks);
        painter->setPen(quiteDark);
        painter->drawLine(rect.left()-5,y,rect.right(),y);
        QString tempstr;
        if (Margin==40)
        {
            tempstr=QString::number(label,'f');
            if (tempstr.length()>6)
                tempstr=tempstr.left(6);
        }
        else
            tempstr=QString::number(label);
        painter->drawText(rect.left()-Margin-20,y-10,Margin+10,20,Qt::AlignRight|Qt::AlignVCenter,tempstr);
    }
    tempstr="unite";
    painter->drawText(rect.left()-Margin-20,rect.top()-25,Margin+20,20,Qt::AlignRight|Qt::AlignVCenter,tempstr);
    tempstr="curve";
    painter->drawText(rect.left(),rect.top()-25,rect.right()-rect.left(),20,Qt::AlignCenter|Qt::AlignVCenter,tempstr);
}

void Plotter::drawCurves(QPainter *painter)
{
    //定义一个枚举类型，存储曲线颜色
    static const QColor colorForIds[10]={Qt::red,Qt::green,Qt::blue,Qt::cyan,Qt::magenta,
                                         Qt::yellow,Qt::darkBlue,Qt::darkGreen,Qt::darkRed,
                                         Qt::white};
    //获得图形设置参数
    PlotSettings settings=zoomStack[curZoom];
    QRect rect;
    //获得绘图区域
    if (Margin==40)
        rect=QRect(Margin+25,Margin,width()-2*(Margin+5),height()-2*Margin);
    else
        rect=QRect(Margin+45,Margin,width()-2*(Margin+25),height()-2*Margin);
    if (!rect.isValid())//获取绘图区域失败
        return;
    painter->setClipRect(rect.adjusted(+1,+1,-1,-1));//设置Painter的操作区域

    //////////////////////////////////////////////////////
    ////修改部分/////////////////////////////////////////////
    /////////////////////////////////////////////////////////

    QVector<QPointF> data(curveMap);
    QPolygonF polyline(data.count());
    //遍历每个坐标点
    for (int j=0;j<data.count();++j)
    {
        double dx=data[j].x()-settings.minX;
        double dy=data[j].y()-settings.minY;
        double x=rect.left()+(dx*(rect.width()-1)/settings.spanX());
        double y=rect.bottom()-(dy*(rect.height()-1)/settings.spanY());
        polyline[j]=QPointF(x,y);
    }
    //设置曲线颜色
    painter->setPen(colorForIds[0]);
    painter->drawPolyline(polyline);
}

PlotSettings::PlotSettings()
{
    minX = 0.0;
    maxX = 10.0;
    numXTicks = 5;

    minY = 0.0;
    maxY = 10.0;
    numYTicks = 5;
}

//设置坐标系的坐标轴长度，x和y分别是负荷曲线值的最大最小值，num是某一天的预测点个数
PlotSettings::PlotSettings(double x, double y, int num, int hx)
{
    minX=0.0;
    maxX=hx;
    numXTicks=num;

    minY=y;
    maxY=x;
    if (ceil(x-y)<=10)
        numYTicks=ceil(x-y);
    else
        numYTicks=10;
}

//使用两个标记之间的距离，乘以给定的数字来增加减少minX,maxX,minY,maxY
//该功能主要用于鼠标滚轮滚动过程
void PlotSettings::scroll(int dx, int dy)
{
    double stepX=spanX()/numXTicks;
    minX=minX+dx*stepX;
    maxX=maxX+dx*stepX;
    double stepY=spanY()/numYTicks;
    minY=minY+dy*stepY;
    maxY=maxY+dy*stepY;
}

//当橡皮筋释放之后，用来调整坐标轴上的刻度和坐标长度
void PlotSettings::adjust()
{
    //调用私有函数处理单个坐标轴
    adjustAxis(minX,maxX,numXTicks);
    adjustAxis(minY,maxY,numYTicks);
}

void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;//设置最小的刻度
    //简单确定两个坐标点之间的距离，下称步长
    double grossStep = (max - min) / MinTicks;
    //采用10的n次，2X10的n次的形式表示步长
    double step = std::pow(10.0, std::floor(std::log10(grossStep)));
    //确定最合适的步长
    if (5 * step < grossStep)
    {
        step *= 5;
    }
    else if (2 * step < grossStep)
    {
        step *= 2;
    }
    //确定坐标刻度点数
    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    //得到坐标轴距离
    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;
}
