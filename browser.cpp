#include "browser.h"
#include "ui_browser.h"

Browser::Browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Browser)
{
    ui->setupUi(this);

    init();
}

Browser::~Browser()
{
    delete ui;
}

void Browser::init()
{
    setWindowState(Qt::WindowMaximized);

    process = 0;

    view = new QWebView(this);
    setCentralWidget(view);
    locationEdit = new QLineEdit(this);
    btn_home = new QPushButton(this);
    btn_home->setIcon(QIcon(":/images/home.png"));
    btn_home->setText(tr("主页"));
    btn_jump = new QPushButton(this);
    btn_jump->setIcon(QIcon(":/images/jump.png"));
    btn_jump->setText(tr("跳转"));

    connect(view,SIGNAL(loadProgress(int)),this,SLOT(setProcess(int)));
    connect(view,SIGNAL(titleChanged(QString)),this,SLOT(adjustTitle()));
    connect(view,SIGNAL(loadFinished(bool)),this,SLOT(finishLoading(bool)));
    connect(locationEdit,SIGNAL(returnPressed()),this,SLOT(changeLocation()));
    connect(btn_jump,SIGNAL(clicked()),this,SLOT(changeLocation()));
    connect(btn_home,SIGNAL(clicked()),this,SLOT(returnHome()));

    view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);;
    connect(view,SIGNAL(linkClicked(QUrl)),this,SLOT(urlChanged(QUrl)));

    locationEdit->setText(tr("http://www.bing.com/"));
    view->load(QUrl(locationEdit->text()));
    view->show();

    ui->mainToolBar->addAction(view->pageAction(QWebPage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Stop));
    ui->mainToolBar->addWidget(locationEdit);
    ui->mainToolBar->addWidget(btn_jump);
    ui->mainToolBar->addWidget(btn_home);
}

void Browser::urlChanged(QUrl url)
{
    locationEdit->setText(url.toString());
    view->load(url);
}

void Browser::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void Browser::setProcess(int p)
{
    process = p;
}

void Browser::adjustTitle()
{
    if(process <= 0 || process >= 100)
    {
        setWindowTitle(view->title());
    }
    else
    {
        setWindowTitle(QString(tr("%1(%2%)")
                               .arg(view->title()).arg(process)));
    }
}

void Browser::finishLoading(bool finished)
{
    if(finished)
    {
        process = 100;
        setWindowTitle(view->title());
    }
    else
    {
//        setWindowTitle(tr("web page loading error!"));
    }
}

void Browser::returnHome()
{
    locationEdit->setText(tr("http://www.bing.com/"));
    view->load(QUrl(locationEdit->text()));
}
