#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QToolButton>
#include <QStylePainter>
#include <QMouseEvent>
#include <cmath>

class PlotSettings;

namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

public:
    explicit Plotter(QWidget *parent = 0);
    ~Plotter();

    void setPlotSettings(const PlotSettings &settings);     //设置绘图区域
    void setCurveData(const QVector<QPointF> &data);        //设置曲线点坐标数据
    //这里的QPointF是一个具有浮点数形式的QPoint
    QSize minimumSizeHint() const;                          //指定窗口部件理想的最小大小
    QSize sizeHint() const;                                 //指定窗口部件理想大小

    //设置Y轴最大最小值和X轴点数,z是横坐标点数
    void setCorrds(double x,double y,int z,int hx);
    //设置起始刻度
    void SetBeginTime(QString data);

public slots://公共槽 响应图像的放大缩小
    void zoomIn();                      //图像放大的槽
    void zoomOut();                     //图像缩小的槽

protected:                               //声明需要重新实现的QWidget事件处理器
    void paintEvent(QPaintEvent *event);//绘图事件
    void resizeEvent(QResizeEvent *event);//重置绘图区大小
    void mousePressEvent(QMouseEvent *event);//鼠标左键按下
    void mouseMoveEvent(QMouseEvent *event);//鼠标拖曳
    void mouseReleaseEvent(QMouseEvent *event);//鼠标左键释放
    void keyPressEvent(QKeyEvent *event);//按钮按下
    void wheelEvent(QWheelEvent *event);//鼠标滚轮事件

private:
    void updateRubberBandRegion();//更新数据
    void refreshPixmap();//刷新图像
    void drawGrid(QPainter *painter);//绘制网格
    void drawCurves(QPainter *painter);//绘制曲线

private:
    Ui::Plotter *ui;

    int Margin;  //曲线图和控件边框的距离

    QToolButton *zoomInButton;                  //放大按钮
    QToolButton *zoomOutButton;                 //缩小按钮
    QVector<QPointF>  curveMap;                 //存储曲线图上的定点
    QVector<PlotSettings> zoomStack;            //堆栈存储放大缩小的级别
    int curZoom;                                //存储当前的缩放级别 0表示未缩放
    bool rubberBandIsShown;                     //标志是否显示曲线图
    QRect rubberBandRect;                       //曲线显示区域
    QPixmap pixmap;                             //用于缓冲图像，在内存中存储，与屏幕上图像一致

    double ValueMax;                            //Y轴显示的最大坐标
    double ValueMin;                            //Y轴显示的最小坐标，即起始坐标

    QString str_Name;
    QString str_Y;
    QString BeginTime;                          //标志横坐标起始刻度
};

class PlotSettings
{
public:
    PlotSettings();
    PlotSettings(double x,double y,int num,int hx);     //带三个参数的构造函数
    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; }        //X轴的范围
    double spanY() const { return maxY - minY; }        //Y轴的范围

    double minX;    //X轴最小坐标
    double maxX;    //X轴最大坐标
    double minY;	//Y轴最小坐标
    double maxY;	//Y轴最大坐标
    int numXTicks;  //X轴的坐标点数，默认都会减掉1，例如numXTicks是5，实际是6个坐标点
    int numYTicks;  //Y轴的坐标点数，叙述同上

private:
    static void adjustAxis(double &min, double &max, int &numTicks);
};

#endif // PLOTTER_H
