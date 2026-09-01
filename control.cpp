#include "control.h"
#include "ui_control.h"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

Control::Control(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Control)
{
    ui->setupUi(this);
    init();    
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


void Control::on_pushButton_fan_on_clicked()//风扇1档
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/lv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 100 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_2_clicked()//风扇2档
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/lv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 200 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_3_clicked()//风扇3档
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/lv3.png);border-style:outset;");
    system("echo 255 > /sys/class/hwmon/hwmon1/pwm1");
}


void Control::on_pushButton_fan_off_clicked()//风扇关
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

