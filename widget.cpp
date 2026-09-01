#include "widget.h"
#include "ui_widget.h"
#include "my_wifi.h"
#include "settings.h"
#include "weather.h"
#include "my_humiture.h"
#include "control.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVBoxLayout *tab_wifi = new QVBoxLayout(ui->tab_WiFi);
    tab_wifi->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *tab_settings = new QVBoxLayout(ui->tab_settings);
    tab_settings->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *tab_weather = new QVBoxLayout(ui->tab_weather);
    tab_weather->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *tab_humiture = new QVBoxLayout(ui->tab_humiture);
    tab_humiture->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *tab_control = new QVBoxLayout(ui->tab_control);
    tab_control->setContentsMargins(0, 0, 0, 0);

    My_WiFi *wifi = new My_WiFi(ui->tab_WiFi);
    tab_wifi->addWidget(wifi);

    Settings *settings = new Settings(ui->tab_settings);
    tab_settings->addWidget(settings);

    Weather *weather = new Weather(ui->tab_weather);
    tab_weather->addWidget(weather);

    My_Humiture *my_humiture = new My_Humiture(ui->tab_humiture);
    tab_humiture->addWidget(my_humiture);

    Control *control = new Control(ui->tab_humiture);
    tab_control->addWidget(control);

    login = new Login(this);
    login->show();

    connect(settings,&Settings::intelligent_control_off,control,&Control::init);
    connect(settings,&Settings::send,control,&Control::updata_settings);//更新阈值设置
    connect(my_humiture,&My_Humiture::send,control,&Control::updata_humiture);//更新传感器参数

}

Widget::~Widget()
{
    delete ui;
}





