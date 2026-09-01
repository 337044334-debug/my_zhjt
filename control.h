#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Control; }
QT_END_NAMESPACE

class Control : public QWidget
{
    Q_OBJECT

public:
    Control(QWidget *parent = nullptr);

    void updata_settings(QString,QString,QString,QString);
    void updata_humiture(QString,QString,QString);
    void compare();
    void init();
    ~Control();

signals:
    void updata();


private slots:
    void on_pushButton_led1_on_clicked();
    void on_pushButton_led1_off_clicked();
    void on_pushButton_led2_on_clicked();
    void on_pushButton_led2_off_clicked();
    void on_pushButton_led3_on_clicked();
    void on_pushButton_led3_off_clicked();
    void on_pushButton_fan_on_clicked();
    void on_pushButton_fan_2_clicked();
    void on_pushButton_fan_3_clicked();
    void on_pushButton_fan_off_clicked();
    void on_pushButton_beep_on_clicked();
    void on_pushButton_beep_off_clicked();

private:
    Ui::Control *ui;
    void beepring();
    void beepunring();    
    QString hum;//湿度
    QString tem;//温度
    QString ill;//光照
    QString tem_max;//最大温度
    QString ill_lv1;//lv1参数值
    QString ill_lv2;//lv2参数值
    QString ill_lv3;//lv3参数值
};
#endif // CONTROL_H
