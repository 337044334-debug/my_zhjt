#include "my_humiture.h"
#include "ui_my_humiture.h"

#include <QDateTime>
#include <QTimer>
#include <QDebug>

My_Humiture::My_Humiture(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::My_Humiture)
{
    ui->setupUi(this);

    currentTime=new QTimer(this);
    connect(currentTime,&QTimer::timeout,this,&My_Humiture::timeUpdate);//1s更新一次时间
    currentTime->start(1000); // 每次发射timeout信号时间间隔为1秒


    connect(&thread_collentdata,&CollentDataThread::send,this,&My_Humiture::set_humAdtemAdill);
    thread_collentdata.start();
}

My_Humiture::~My_Humiture()
{
    delete ui;
}

void My_Humiture::set_humAdtemAdill(QString tem, QString hum, QString ill)
{
    ui->humidity->setText(hum);
    ui->temperature->setText(tem);
    ui->illumination->setText(ill);
}

void My_Humiture::timeUpdate()
{
    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy年MM月dd日 hh:mm:ss "); //设置显示的格式
    ui->time->setText(Timestr);
}
