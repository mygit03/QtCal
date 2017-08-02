#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
//#include <QtWebKit/QWebView>

#include "aboutcalculate.h"
#include "help.h"
#include "equcal.h"
#include "matrixcal.h"
#include "draw.h"
#include "funcdraw.h"
#include "painter/painter.h"
//#include "browser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();                              //初始化

    int f2to10(QString str);                  //二进制转十进制
    int f8to10(QString str);                  //八进制转十进制
    int f16to10(QString str);                 //十六进制转十进制
    QString f10to2(int num);                  //十进制转任意进制
    void set10();                             //设置十进制

private slots:
    void display();                             //定时器槽函数

    void on_rBtn_2_clicked(bool checked);

    void on_rBtn_8_clicked(bool checked);

    void on_rBtn_10_clicked(bool checked);

    void on_rBtn_16_clicked(bool checked);

    void on_btn_0_clicked();

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_10_clicked();

    void on_btn_11_clicked();

    void on_btn_12_clicked();

    void on_btn_13_clicked();

    void on_btn_14_clicked();

    void on_btn_15_clicked();

    void on_btn_point_clicked();            //'.'

    void on_btn_symbol_clicked();           //'±'

    void on_btn_add_clicked();              //'+'

    void on_btn_sub_clicked();              //'-'

    void on_btn_mul_clicked();              //'*'

    void on_btn_div_clicked();              //'/'

    void equal();                           //'='

    void on_btn_mod_clicked();              //'%'

    void on_btn_x_clicked();                //'1/x'

    void on_btn_sqrt_clicked();             //'√'

    void on_btn_pow_clicked();              //'x^2'

    void on_btn_nx_clicked();               //'x^y'

    void on_btn_int_clicked();              //取整

    void on_btn_and_clicked();              //与

    void on_btn_or_clicked();               //或

    void on_btn_tongHuo_clicked();          //同或

    void on_btn_yiHuo_clicked();            //异或

    void on_btn_matrixCal_clicked();        //矩阵计算

    void on_btn_equCal_clicked();           //方程计算

    void on_btn_ln_clicked();              //高精度计算

    void on_btn_draw_clicked();             //绘图板

    void on_btn_funcDraw_clicked();         //函数绘图

    void on_btn_exp_clicked();             //线性拟合

    void on_btn_del_clicked();              //back 退格键

    void on_btn_CE_clicked();               //清除输入(CE)
    //键入数字时，按下相应的数字键，如果按错可用（CE）键消去一次数值，再重新输入正确的数字如你要输9*7，
    //但你输入了9*8，显示屏显示8（输错了）时，按一下CE键，那么就只是清除了8（显示屏则显示"0"），
    //然后你再按7，再按=（显示屏上就会显示63）

    void on_btn_C_clicked();                //清除键(C) 清除数据，所有数据、算式都清除，归零复位

    void on_btn_MC_clicked();

    void on_btn_MR_clicked();

    void on_btn_MS_clicked();

    void on_btn_addM_clicked();             //M+

    void on_btn_subM_clicked();             //M-

    void on_btn_n_clicked();                //n!

    void on_btn_PI_clicked();               //π

    void on_aboutCalculate_triggered();     //关于计算器

    void on_copy_triggered();               //复制

    void on_paste_triggered();              //粘贴

    void on_cut_triggered();                //剪切

    void on_standard_triggered();           //标准型

    void on_multiFunc_triggered();          //多功能型

    void on_btn_sin_clicked();

    void on_btn_cos_clicked();

    void on_btn_tan_clicked();

    void on_btn_log_clicked();

    void on_btn_10x_clicked();

    void on_Help_triggered();               //帮助

    void on_calOnLine_triggered();          //在线计算器

    void on_Browser_triggered();            //浏览器

private:
    Ui::MainWindow *ui;

//    QString str;                //lineEdit内容
    QString value1, value2;     //运算符两边的值
    QString text;               //LineEdit内容，复制粘贴使用
    double sumInMemory,memory;  //记忆存储
    int op;                     //运算符号
    int zflag;                  //进制标志变量
    int flag;                   //0表示没有进行计算，1表示已经计算
//    Painter* m_pPainter;        //画图板的对象
    QTimer *timer;              //定时器

//    QWebView *webView;
};

#endif // MAINWINDOW_H
