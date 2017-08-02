#ifndef DRAW_H
#define DRAW_H

#include <QDialog>

namespace Ui {
class Draw;
}

class Draw : public QDialog
{
    Q_OBJECT

public:
    explicit Draw(int width, int height, QWidget *parent = 0);
    ~Draw();
    void paintEvent(QPaintEvent *);

    void drawLine(float* pXBuf,float* pYBuf,int size);
    void drawPoint(float* pXPointBuff,float* pYPointBuff,
                   int size,float* pXBuf,float* pYBuf,int size1);


private:
    Ui::Draw *ui;

    QImage* m_pImage;       // 曲线图句柄
    QPainter* m_pPainter;   // 画曲线图的Painter句柄

    float *m_pXBuf;
    float *m_pYBuf;
    int m_num;
    int m_width;
    int m_height;

    float* m_pXPointBuff;
    float* m_pYPointBuff;
    int m_numPoint;
};

#endif // DRAW_H
