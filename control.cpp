#include "control.h"
#include "ui_control.h"
#include <linux/input.h>
#include <fcntl.h>
#include <settings.h>
#include <unistd.h>
#include <QDebug>

Control::Control(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Control)
{
    ui->setupUi(this);
    connect(this,&Control::updata,this,&Control::compare);
}


void Control::updata_settings(QString tem, QString lv1, QString lv2, QString lv3)
{
    tem_max=tem;
    ill_lv1=lv1;
    ill_lv2=lv2;
    ill_lv3=lv3;
    emit updata();
}

void Control::updata_humiture(QString tem_new, QString hum_new, QString ill_new)
{
    hum=hum_new;
    tem=tem_new;
    ill=ill_new;
    emit updata();
}

void Control::compare()
{
    qDebug()<<"tem_max:"<<tem_max<<"\n";
    qDebug()<<"ill_lv1:"<<ill_lv1<<"\n";
    qDebug()<<"ill_lv2:"<<ill_lv2<<"\n";
    qDebug()<<"ill_lv3:"<<ill_lv3<<"\n";
    qDebug()<<"tem:"<<tem<<"\n";
    qDebug()<<"hum:"<<hum<<"\n";
    qDebug()<<"ill:"<<ill<<"\n";
    if(ill<ill_lv1&&ill>ill_lv2)
    {
        emit on_pushButton_led1_on_clicked();
        emit on_pushButton_led2_off_clicked();
        emit on_pushButton_led3_off_clicked();
    }
    else if(ill<ill_lv2&&ill>ill_lv3)
    {
        emit on_pushButton_led1_on_clicked();
        emit on_pushButton_led2_on_clicked();
        emit on_pushButton_led3_off_clicked();
    }
    else if(ill<ill_lv3)
    {
        emit on_pushButton_led1_on_clicked();
        emit on_pushButton_led2_on_clicked();
        emit on_pushButton_led3_on_clicked();
    }
    if(tem>tem_max)
        emit on_pushButton_fan_3_clicked();
    else
        emit on_pushButton_fan_off_clicked();
}

Control::~Control()
{
    delete ui;
}


void Control::on_pushButton_led1_on_clicked()
{
    ui->pushButton_led1_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led1_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led1/brightness");
}


void Control::on_pushButton_led1_off_clicked()
{
    ui->pushButton_led1_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led1_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led1/brightness");
}


void Control::on_pushButton_led2_on_clicked()
{
    ui->pushButton_led2_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led2_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led2/brightness");
}


void Control::on_pushButton_led2_off_clicked()
{
    ui->pushButton_led2_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led2_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led2/brightness");
}


void Control::on_pushButton_led3_on_clicked()
{
    ui->pushButton_led3_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led3_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led3/brightness");
}


void Control::on_pushButton_led3_off_clicked()
{
    ui->pushButton_led3_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led3_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led3/brightness");
}


void Control::on_pushButton_fan_on_clicked()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/lv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 100 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_2_clicked()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/lv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 200 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_3_clicked()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/lv3.png);border-style:outset;");
    system("echo 255 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_off_clicked()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 0 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_beep_on_clicked()//蜂鸣器开
{
    ui->pushButton_beep_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_beep_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    emit beepring();
}


void Control::on_pushButton_beep_off_clicked()//蜂鸣器关
{
    ui->pushButton_beep_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_beep_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    emit beepunring();
}

void Control::init()
{
    ui->pushButton_led1_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led1_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led1/brightness");

    ui->pushButton_led2_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led2_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led2/brightness");

    ui->pushButton_led3_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led3_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led3/brightness");

    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 0 > /sys/class/hwmon/hwmon1/pwm1");

    ui->pushButton_beep_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_beep_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    emit beepunring();
}

void Control::beepring()
{
    int fd;
    struct input_event event;
    struct timeval time;
    fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 1000;
    time.tv_sec = 1;
    time.tv_usec = 0;
    event.time = time;
    write(fd, &event, sizeof(struct input_event));
}

void Control::beepunring()
{
    int fd;
    struct input_event event;
    struct timeval time;
    fd = open("/dev/input/by-path/platform-beeper-event", O_RDWR);
    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 0;
    time.tv_sec = 0;
    time.tv_usec = 0;
    event.time = time;
    write(fd, &event, sizeof(struct input_event));
}

