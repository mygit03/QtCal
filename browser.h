#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include <QtWebKit/QWebView>
#include <QLineEdit>
#include <QPushButton>

//class QWebView;
//class QLineEdit;

namespace Ui {
class Browser;
}

class Browser : public QMainWindow
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = 0);
    ~Browser();

    void init();

protected slots:
    void urlChanged(QUrl url);

    void changeLocation();

    void setProcess(int p);

    void adjustTitle();

    void finishLoading(bool finished);

    void returnHome();

private:
    Ui::Browser *ui;

    QWebView *view;
    QLineEdit *locationEdit;
    QPushButton *btn_home;
    QPushButton *btn_jump;
    int process;
};

#endif // BROWSER_H
