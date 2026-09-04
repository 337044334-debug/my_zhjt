#include "settings.h"
#include "ui_settings.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
    ,currentLineEdit(nullptr)
    ,tem_max(28.00)
    ,ill_lv1(3.00)
    ,ill_lv2(2.00)
    ,ill_lv3(1.00)
    ,smart(false)
{
    ui->setupUi(this);
    ui->lineEdit_led_lv1->setText(QString::number(ill_lv1,'f', 2));
    ui->lineEdit_led_lv2->setText(QString::number(ill_lv2,'f', 2));
    ui->lineEdit_led_lv3->setText(QString::number(ill_lv3,'f', 2));
    ui->lineEdit_fan_tem->setText(QString::number(tem_max,'f', 2));
    syszuxpinyin_send =new SyszuxPinyin();
    connect(ui->lineEdit_led_lv1,&My_lineEdit::send_show,this,&Settings::keyboardshow_send);
    connect(ui->lineEdit_led_lv2,&My_lineEdit::send_show,this,&Settings::keyboardshow_send);
    connect(ui->lineEdit_led_lv3,&My_lineEdit::send_show,this,&Settings::keyboardshow_send);
    connect(ui->lineEdit_fan_tem,&My_lineEdit::send_show,this,&Settings::keyboardshow_send);
    connect(syszuxpinyin_send,&SyszuxPinyin::sendPinyin,this,&Settings::keyboard_input_send);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::keyboardshow_send(QString data)
{
    currentLineEdit = qobject_cast<My_lineEdit *>(sender());
    syszuxpinyin_send->lineEdit_window->setText(data);
    syszuxpinyin_send->resize(800,310);
    syszuxpinyin_send->move(120,280);
    syszuxpinyin_send->show();
}
void Settings::keyboard_input_send(QString gemfield)
{
    if(currentLineEdit)
    {
        currentLineEdit->setText(gemfield);
    }
}


void Settings::on_pushButton_settings_led_clicked()//led灯参数变更
{
    if(ui->lineEdit_led_lv1->text()!=""&&ui->lineEdit_led_lv2->text()!=""&&ui->lineEdit_led_lv3->text()!="")
    {
        ill_lv1 =ui->lineEdit_led_lv1->text().toFloat();
        ill_lv2 =ui->lineEdit_led_lv2->text().toFloat();
        ill_lv3 =ui->lineEdit_led_lv3->text().toFloat();
        QMessageBox::information(this,tr("information"), tr("修改成功"));
    }
    else
        QMessageBox::warning(this,tr("warning"), tr("阈值不能为空"));
    send(ill_lv1,ill_lv2,ill_lv3,tem_max,smart);
}


void Settings::on_pushButton_settings_fan_clicked()//风扇参数变更
{
    if(ui->lineEdit_fan_tem->text()!="")
    {
        tem_max = ui->lineEdit_fan_tem->text().toFloat();
        QMessageBox::information(this,tr("information"), tr("修改成功"));
    }
    else
        QMessageBox::warning(this,tr("information"), tr("风扇开启温度阈值不能为空"));
    send(ill_lv1,ill_lv2,ill_lv3,tem_max,smart);
}


void Settings::on_pushButton_settings_ON_clicked()//开启智能检
{
    smart=true;
    send(ill_lv1,ill_lv2,ill_lv3,tem_max,smart);
    QMessageBox::information(this, tr("in,ill_lv1formation"),"开启智能检测成功");
    ui->pushButton_settings_ON->setStyleSheet("background-image:url(:/icon/OpenMonitoring.png);border-style:outset;");
    ui->pushButton_settings_OFF->setStyleSheet("background-image:url(:/icon/disCloseMonitoring.png);border-style:outset;");
}


void Settings::on_pushButton_settings_OFF_clicked()//关闭智能检
{
    smart=false;
    send(ill_lv1,ill_lv2,ill_lv3,tem_max,smart);
    ui->pushButton_settings_ON->setStyleSheet("background-image:url(:/icon/disOpenMonitoring.png);border-style:outset;");
    ui->pushButton_settings_OFF->setStyleSheet("background-image:url(:/icon/CloseMonitoring.png);border-style:outset;");
    QMessageBox::information(this, tr("information"),"关闭智能检测成功");
}


