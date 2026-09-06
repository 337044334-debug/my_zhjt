#include "widget.h"
#include "ui_widget.h"
#include "my_wifi.h"
#include "weather.h"
#include "my_humiture.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*  WIfi创建  */
    QVBoxLayout *tab_wifi = new QVBoxLayout(ui->tab_WiFi);
    tab_wifi->setContentsMargins(0, 0, 0, 0);

    My_WiFi *wifi = new My_WiFi(ui->tab_WiFi);
    tab_wifi->addWidget(wifi);

    /*  天气创建  */
    QVBoxLayout *tab_weather = new QVBoxLayout(ui->tab_weather);
    tab_weather->setContentsMargins(0, 0, 0, 0);

    Weather *weather = new Weather(ui->tab_weather);
    tab_weather->addWidget(weather);

    /*  参数设置  */
    QVBoxLayout *tab_settings = new QVBoxLayout(ui->tab_settings);
    tab_settings->setContentsMargins(0, 0, 0, 0);

    settings = new Settings(ui->tab_settings);
    tab_settings->addWidget(settings);

    /*  温湿度显示  */
    QVBoxLayout *tab_humiture = new QVBoxLayout(ui->tab_humiture);
    tab_humiture->setContentsMargins(0, 0, 0, 0);

    My_Humiture *my_humiture = new My_Humiture(ui->tab_humiture);
    tab_humiture->addWidget(my_humiture);

    /*  传感器参数  */
    data_thread=my_humiture->getDataThread();

    /*  智能控制  */
    smart = new SmartController(data_thread, settings, this);

    /*  百度云模块  */
    QVBoxLayout *tab_calculate = new QVBoxLayout(ui->tab_ioT);
    tab_calculate->setContentsMargins(0, 0, 0, 0);

    calculate = new Calculate(data_thread,ui->tab_ioT);
    tab_calculate->addWidget(calculate);

    /*  控制  */
    QVBoxLayout *tab_control = new QVBoxLayout(ui->tab_control);
    tab_control->setContentsMargins(0, 0, 0, 0);

    control = new Control(calculate,smart,ui->tab_humiture);
    tab_control->addWidget(control);

    



    /*  login界面  */
    pe15thread=new Pe15thread();
    login=new Login(this);
    connect(pe15thread,&Pe15thread::pesig,this,&Widget::login_show);
    connect(login,&Login::loginclose,this,&Widget::login_close);
    pe15thread->start();

}

Widget::~Widget()
{
     pe15thread->stop();

    if(pe15thread->isRunning())
    {
        pe15thread->wait();
    }

    delete pe15thread;    
    delete ui;
}

void Widget::login_show()
{
    qDebug()<<"有信号";
    this->hide();
    login->btn_hide();
    login->show();
    pe15thread->pause();
}

void Widget::login_close()
{
    this->show();
    login->hide();
    pe15thread->resume();    
}





