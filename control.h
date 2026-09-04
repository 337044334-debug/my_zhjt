#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include "smartcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Control; }
QT_END_NAMESPACE

class Control : public QWidget
{
    Q_OBJECT

public:
    Control(SmartController *smart,QWidget *parent = nullptr);  
    
    ~Control();

signals:
    


private slots:
    void led1_on_slots();
    void led2_on_slots();
    void led3_on_slots();

    void led1_off_slots();
    void led2_off_slots();
    void led3_off_slots();

    void fan_on_slots();
    void fan_off_slots(); 

    void init();
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

    void no_btn();







private:
    Ui::Control *ui;
    void beepring();
    void beepunring(); 
    SmartController* smart; 
      
};
#endif // CONTROL_H
