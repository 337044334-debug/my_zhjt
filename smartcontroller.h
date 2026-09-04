#ifndef SMARTCONTROLLER_H
#define SMARTCONTROLLER_H

#include <QObject>
#include "settings.h"
#include "my_humiture.h"

class SmartController : public QObject
{
    Q_OBJECT
public:
    explicit SmartController(CollentDataThread* data_thread,Settings* settings,QObject *parent = nullptr);

signals:
    void led1_on();
    void led2_on();
    void led3_on();
    void led1_off();
    void led2_off();
    void led3_off();
    void fan_on();
    void fan_off();
    void smart_signal();
    void init_signals();


//public slots:

private slots:
    
    void settings_new(float,float,float,float,bool);
    void my_humiture_new(float,float,float);


private:
    float tem;
    float hum;
    float ill;
    float ill_lv1;
    float ill_lv2;
    float ill_lv3;
    float tem_max;
    bool smart;
    bool tmp;
    void compare();

    Settings* settings;
    CollentDataThread* thread_collentdata;
};

#endif // SMARTCONTROLLER_H
