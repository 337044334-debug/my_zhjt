#include "control.h"
#include "ui_control.h"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

Control::Control(SmartController *smart,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Control)
    , smart(smart)
{
    ui->setupUi(this);
    connect(smart,&SmartController::led1_on,this,&Control::led1_on_slots);
    connect(smart,&SmartController::led2_on,this,&Control::led2_on_slots);
    connect(smart,&SmartController::led3_on,this,&Control::led3_on_slots);

    connect(smart,&SmartController::led1_off,this,&Control::led1_off_slots);
    connect(smart,&SmartController::led2_off,this,&Control::led2_off_slots);
    connect(smart,&SmartController::led3_off,this,&Control::led3_off_slots);

    connect(smart,&SmartController::fan_on,this,&Control::fan_on_slots);
    connect(smart,&SmartController::fan_off,this,&Control::fan_off_slots);

    connect(smart,&SmartController::smart_signal,this,&Control::no_btn);


    connect(smart,&SmartController::init_signals,this,&Control::init);


    init();

}
Control::~Control()
{
    delete ui;
}

void Control::no_btn()
{
    ui->pushButton_led1_on->setEnabled(false);
    ui->pushButton_led1_off->setEnabled(false);
    

    ui->pushButton_led2_on->setEnabled(false);
    ui->pushButton_led2_off->setEnabled(false);
    

    ui->pushButton_led3_on->setEnabled(false);
    ui->pushButton_led3_off->setEnabled(false);
    

    ui->pushButton_fan_on->setEnabled(false);
    ui->pushButton_fan_off->setEnabled(false);
    ui->pushButton_fan_2->setEnabled(false);
    ui->pushButton_fan_3->setEnabled(false);
}



void Control::on_pushButton_led1_on_clicked()
{
    led1_on_slots();
}


void Control::on_pushButton_led1_off_clicked()
{
    led1_off_slots();
}


void Control::on_pushButton_led2_on_clicked()
{
    led2_on_slots();
}


void Control::on_pushButton_led2_off_clicked()
{
    led2_off_slots();
}


void Control::on_pushButton_led3_on_clicked()
{
   led3_on_slots();
}


void Control::on_pushButton_led3_off_clicked()
{
   led3_off_slots();
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
    fan_on_slots();
}


void Control::on_pushButton_fan_off_clicked()//风扇关
{
    fan_off_slots();
}


void Control::on_pushButton_beep_on_clicked()//蜂鸣器开
{
    ui->pushButton_beep_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_beep_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    beepring();
}


void Control::on_pushButton_beep_off_clicked()//蜂鸣器关
{
    ui->pushButton_beep_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_beep_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    beepunring();
}

void Control::led1_on_slots()
{
    ui->pushButton_led1_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led1_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led1/brightness");
}

void Control::led2_on_slots()
{
    ui->pushButton_led2_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led2_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led2/brightness");
}

void Control::led3_on_slots()
{
     ui->pushButton_led3_on->setStyleSheet("background-image:url(:/icon/open.png);border-style:outset;");
    ui->pushButton_led3_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    system("echo 1 > /sys/class/leds/led3/brightness");
}

void Control::led1_off_slots()
{
    ui->pushButton_led1_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led1_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led1/brightness");
}

void Control::led2_off_slots()
{
    ui->pushButton_led2_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led2_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led2/brightness");
}

void Control::led3_off_slots()
{
     ui->pushButton_led3_on->setStyleSheet("background-image:url(:/icon/disopen.png);border-style:outset;");
    ui->pushButton_led3_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    system("echo 0 > /sys/class/leds/led3/brightness");
}

void Control::fan_on_slots()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/disclose.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/lv3.png);border-style:outset;");
    system("echo 255 > /sys/class/hwmon/hwmon1/pwm1");
}

void Control::fan_off_slots()
{
    ui->pushButton_fan_on->setStyleSheet("background-image:url(:/icon/dislv1.png);border-style:outset;");
    ui->pushButton_fan_off->setStyleSheet("background-image:url(:/icon/close.png);border-style:outset;");
    ui->pushButton_fan_2->setStyleSheet("background-image:url(:/icon/dislv2.png);border-style:outset;");
    ui->pushButton_fan_3->setStyleSheet("background-image:url(:/icon/dislv3.png);border-style:outset;");
    system("echo 0 > /sys/class/hwmon/hwmon1/pwm1");
}



void Control::init()
{
    ui->pushButton_led1_on->setEnabled(true);
    ui->pushButton_led1_off->setEnabled(true);
    

    ui->pushButton_led2_on->setEnabled(true);
    ui->pushButton_led2_off->setEnabled(true);
    

    ui->pushButton_led3_on->setEnabled(true);
    ui->pushButton_led3_off->setEnabled(true);
    

    ui->pushButton_fan_on->setEnabled(true);
    ui->pushButton_fan_off->setEnabled(true);
    ui->pushButton_fan_2->setEnabled(true);
    ui->pushButton_fan_3->setEnabled(true);

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

