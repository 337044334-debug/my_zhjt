#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "syszuxpinyin.h"
#include "my_lineedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Settings; }
QT_END_NAMESPACE

class Settings : public QWidget
{
    Q_OBJECT

public:
    Settings(QWidget *parent = nullptr);
    ~Settings();
    SyszuxPinyin *syszuxpinyin_serialName;//虚拟键盘
    SyszuxPinyin *syszuxpinyin_send;//虚拟键盘

signals:
    void send(float,float,float,float,bool);



private slots:
    void keyboardshow_send(QString data);//虚拟键盘显示
    void keyboard_input_send(QString gemfield);//虚拟键盘的接收发送
    void on_pushButton_settings_led_clicked();//LED参数修改
    void on_pushButton_settings_fan_clicked();//风扇参数修改
    void on_pushButton_settings_ON_clicked();//开始智能控制
    void on_pushButton_settings_OFF_clicked();//关闭智能控制


private:
    Ui::Settings *ui;
    My_lineEdit *currentLineEdit;//虚拟键盘
    float tem_max;//最大温度
    float ill_lv1;//lv1参数值
    float ill_lv2;//lv2参数值
    float ill_lv3;//lv3参数值
    bool smart;//智能控制
};
#endif // SETTINGS_H
