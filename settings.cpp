#include "settings.h"
#include "ui_settings.h"
#include <QMessageBox>
#include <QDebug>

Settings::Settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
    ,currentLineEdit(nullptr)
    ,tem_max("28")
    ,ill_lv1("3")
    ,ill_lv2("2")
    ,ill_lv3("1")

{
    ui->setupUi(this);
    ui->lineEdit_led_lv1->setText("3");
    ui->lineEdit_led_lv2->setText("2");
    ui->lineEdit_led_lv3->setText("1");
    ui->lineEdit_fan_tem->setText("28");
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


void Settings::on_pushButton_settings_led_clicked()
{
    if(ui->lineEdit_led_lv1->text()!=""&&ui->lineEdit_led_lv2->text()!=""&&ui->lineEdit_led_lv3->text()!="")
    {
        ill_lv1 =ui->lineEdit_led_lv1->text();
        ill_lv2 =ui->lineEdit_led_lv2->text();
        ill_lv3 =ui->lineEdit_led_lv3->text();
        QMessageBox::information(this,tr("information"), tr("修改成功"));
    }
    else
        QMessageBox::warning(this,tr("warning"), tr("阈值不能为空"));
    emit send(tem_max,ill_lv1,ill_lv2,ill_lv3);//更新数据
    qDebug()<<"tem_max:"<<tem_max<<"\n";
    qDebug()<<"ill_lv1:"<<ill_lv1<<"\n";
    qDebug()<<"ill_lv2:"<<ill_lv2<<"\n";
    qDebug()<<"ill_lv3:"<<ill_lv3<<"\n";
}


void Settings::on_pushButton_settings_fan_clicked()
{
    if(ui->lineEdit_fan_tem->text()!="")
    {
        tem_max = ui->lineEdit_fan_tem->text();
        QMessageBox::information(this,tr("information"), tr("修改成功"));
    }
    else
        QMessageBox::warning(this,tr("information"), tr("风扇开启温度阈值不能为空"));
    emit send(tem_max,ill_lv1,ill_lv2,ill_lv3);//更新数据
    qDebug()<<"tem_max:"<<tem_max<<"\n";
    qDebug()<<"ill_lv1:"<<ill_lv1<<"\n";
    qDebug()<<"ill_lv2:"<<ill_lv2<<"\n";
    qDebug()<<"ill_lv3:"<<ill_lv3<<"\n";
}


void Settings::on_pushButton_settings_ON_clicked()
{
    emit send(tem_max,ill_lv1,ill_lv2,ill_lv3);//更新数据
    qDebug()<<"tem_max:"<<tem_max<<"\n";
    qDebug()<<"ill_lv1:"<<ill_lv1<<"\n";
    qDebug()<<"ill_lv2:"<<ill_lv2<<"\n";
    qDebug()<<"ill_lv3:"<<ill_lv3<<"\n";
    QMessageBox::information(this, tr("in,ill_lv1formation"),"开启智能检测成功");
    ui->pushButton_settings_ON->setStyleSheet("background-image:url(:/icon/OpenMonitoring.png);border-style:outset;");
    ui->pushButton_settings_OFF->setStyleSheet("background-image:url(:/icon/disCloseMonitoring.png);border-style:outset;");
}


void Settings::on_pushButton_settings_OFF_clicked()
{
    emit intelligent_control_off();
    ui->pushButton_settings_ON->setStyleSheet("background-image:url(:/icon/disOpenMonitoring.png);border-style:outset;");
    ui->pushButton_settings_OFF->setStyleSheet("background-image:url(:/icon/CloseMonitoring.png);border-style:outset;");
    QMessageBox::information(this, tr("information"),"关闭智能检测成功");
}

