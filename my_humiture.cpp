#include "my_humiture.h"
#include "ui_my_humiture.h"

#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QDebug>

My_Humiture::My_Humiture(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::My_Humiture)
    , tem(0)
    , hum(0)
    , ill(0)
{
    ui->setupUi(this);

    currentTime=new QTimer(this);
    connect(currentTime,&QTimer::timeout,this,&My_Humiture::timeUpdate);//1s更新一次时间
    currentTime->start(1000); // 每次发射timeout信号时间间隔为1秒

    thread_collentdata=new CollentDataThread;
    connect(thread_collentdata,&CollentDataThread::send,this,&My_Humiture::set_humAdtemAdill);
    thread_collentdata->start();
}

My_Humiture::~My_Humiture()
{
    delete ui;
}



void My_Humiture::set_humAdtemAdill(float tem_new, float hum_new, float ill_new)
{
    tem = tem_new;
    hum = hum_new;
    ill = ill_new;
    ui->humidity->setText(QString::number(hum_new,'f', 2));
    ui->temperature->setText(QString::number(tem_new,'f', 2));
    ui->illumination->setText(QString::number(ill_new,'f', 2));
}

void My_Humiture::timeUpdate()
{
    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy年MM月dd日 hh:mm:ss "); //设置显示的格式
    ui->time->setText(Timestr);
}

float My_Humiture::get_hum()
{
    return hum;
}

float My_Humiture::get_tem()
{
    return tem;
}

float My_Humiture::get_ill()
{
    return ill;
}

CollentDataThread* My_Humiture::getDataThread()
{
    return thread_collentdata;
}
