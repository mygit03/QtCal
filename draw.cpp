#include "draw.h"
#include "ui_draw.h"

#include <QPainter>
#include <QDebug>

Draw::Draw(int width,int height,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);

    setWindowTitle(tr("函数绘图"));

    m_pPainter = new QPainter(this);

    m_pImage = new QImage(width, height, QImage::Format_RGB32);

    m_width = width;
    m_height = height;
}

Draw::~Draw()
{
    delete ui;
}

void Draw::paintEvent(QPaintEvent *)
{
    //分别取得X和Y最大值,最小值
    float maxX=m_pXPointBuff[0];
    float minX=m_pXPointBuff[0];
    float maxY=m_pYPointBuff[0];
    float minY=m_pYPointBuff[0];
    for(int i=0;i<m_numPoint;i++)
    {
        if(m_pXPointBuff[i]>maxX)
            maxX=m_pXPointBuff[i];
        if(m_pXPointBuff[i]<minX)
            minX=m_pXPointBuff[i];
        if(m_pYPointBuff[i]>maxY)
            maxY=m_pYPointBuff[i];
        if(m_pYPointBuff[i]<minY)
            minY=m_pYPointBuff[i];
    }

    qDebug()<<"maxY : "<<maxY<<endl;
    //如果原点必须在X轴上，加上下面2行，否则注释掉
    if(minX>0)
        minX=0;
    //如果原点必须在Y轴上，加上下面2行，否则注释掉
    if(minY>0)
        minY=0;
    //确定图象显示大小
    int width=m_width;
    int height=m_height;
    //确定坐标图四周预留的空白大小
    const int mytop=20;
    const int mybottom=20;
    const int myleft=20;
    const int myright=20;
    //确定X，Y轴每单位显示宽度
    float intervalX=(width-myleft-myright)/(maxX-minX);    //自己改动了一下(maxX-minX)替换为6000
    float intervalY=(height-mybottom-mytop)/(maxY-minY);   //自己改动了一下(maxY-minY)替换为600

    //绘制X，Y轴
    //X轴从图形区域最左端到最右端

    float bottomY=0;      //bottomY表示X轴的y值
    float leftX=0;         //leftX表示Y轴的x值

    if(minY>0)
        bottomY=minY;
    if(minX>0)
        leftX=minX;

    QPainter painter(this);

    // 贴图
    //painter.drawImage(minX, minY, *m_pImage, 0, 0, m_width, m_height);

    QPen pen;
    pen.setColor(QColor(255,0,0));  //设置画笔为红色
    painter.setPen(pen);  //选择画笔

    painter.setBrush(Qt::black);//设置绘制背景的笔的颜色
    //X轴
    painter.drawLine(float(myleft),float(height-(mybottom+(bottomY-minY)*intervalY)),
                     float(width-myright),float(height-(mybottom+(bottomY-minY)*intervalY)));
    //Y轴
    //painter.drawLine(float(myleft+(leftX-minX)*intervalX),float(height-mybottom),
    //                 float(myleft+(leftX-minX)*intervalX),float(mytop));

    painter.drawLine(float(myleft+(leftX-minX)*intervalX),float(height-mybottom),
                     float(myleft+(leftX-minX)*intervalX),float(mytop));

    //确定显示刻度个数

    const int count=20;                //yue
    const int countY=20;

    //确定每个显示刻度之间的宽度
    float spaceX=(width-myleft-myright)/count;
    float spaceY=(height-mybottom-mytop)/count;

    QString str;
    //CString str;
    //X轴
    for(int i=0;i<=count;i++)
    {
        str = QString("%1").arg(float(minX+i*(maxX-minX)/count));
        //str.Format("%.1f",minX+i*(maxX-minX)/count);
        painter.drawLine(float(myleft+spaceX*i),float(height-(mybottom+(bottomY-minY)*intervalY)),
                         float(myleft+spaceX*i),float(height-(mybottom+(bottomY-minY)*intervalY+5)));
        if(i%5 == 0)
        {
            painter.drawText(float(myleft+spaceX*i),
                             float(height-(mybottom+(bottomY-minY)*intervalY-15)),str);
        }
    }
    painter.drawText(float(myleft+spaceX*count),
                     float(height-(mybottom+(bottomY-minY)*intervalY-30)),tr("X轴"));
    //Y轴
    for(int i=0;i<=countY;i++)
    {
        str = QString("%1").arg(float(minY+i*(maxY-minY)/count));

        painter.drawLine(float(myleft+(leftX-minX)*intervalX),float(height-(mybottom+spaceY*i)),
                         float(myleft+(leftX-minX)*intervalX+5),float(height-(mybottom+spaceY*i)));
        if(i%5 == 0)
        {
            painter.drawText(float(myleft+(leftX-minX)*intervalX+10),float(height-(mybottom+spaceY*i)),str);
        }
    }
    painter.drawText(float(myleft+(leftX-minX)*intervalX-18),float(height-(mybottom+spaceY*countY)),tr("Y轴"));

    //绘制曲线。由于绘图坐标的Y轴是向下延升，所以这里每个点的Y值是用
    //图象高度减去y值大小。

    for(int i=0;i<m_num;i++)
    {
        if(i != m_num-1)
        {
            painter.drawLine(float(myleft+(m_pXBuf[i]-minX)*intervalX),
                             float(height-(mybottom+(m_pYBuf[i]-minY)*intervalY)),
                             float(myleft+(m_pXBuf[i+1]-minX)*intervalX),
                             float(height-(mybottom+(m_pYBuf[i+1]-minY)*intervalY))
                             );
        }else
        {

        }

    }

    QPen pen1;
    pen1.setWidth(5);//改变线宽
    pen1.setColor(Qt::blue);
    painter.setPen(pen1);

    for(int i = 0 ; i < m_numPoint ;i++)
    {

        painter.drawPoint(myleft+(m_pXPointBuff[i]-minX)*intervalX,
                          height-(mybottom+(m_pYPointBuff[i]-minY)*intervalY));
        qDebug()<<"i : "<<i<<endl;
    }
}

void Draw::drawLine(float *pXBuf, float *pYBuf, int size)
{
    m_pXBuf = new float[size];
    m_pYBuf = new float[size];
    m_pXBuf = pXBuf;
    m_pYBuf = pYBuf;

    m_num = size;
}

void Draw::drawPoint(float *pXPointBuff, float *pYPointBuff,
                     int size, float *pXBuf, float *pYBuf, int size1)
{
    m_pXPointBuff = new float[size];
    m_pYPointBuff = new float[size];

    m_pXPointBuff = pXPointBuff;
    m_pYPointBuff = pYPointBuff;
    m_numPoint = size;

    m_pXBuf = new float[size];
    m_pYBuf = new float[size];
    m_pXBuf = pXBuf;
    m_pYBuf = pYBuf;

    m_num = size1;
}
