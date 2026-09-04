#include "smartcontroller.h"
#include <QDebug>


SmartController::SmartController(CollentDataThread* data_thread,Settings* settings,QObject *parent) : 
    QObject(parent)
    ,settings(settings)
    ,thread_collentdata(data_thread)
    ,tem(0.0)
    ,hum(0.0)
    ,ill(0.0)
    ,ill_lv1(0.0)
    ,ill_lv2(0.0)
    ,ill_lv3(0.0)
    ,tem_max(0.0)
    ,smart(false)
    ,tmp(false)

{
    connect(settings,&Settings::send,this,&SmartController::settings_new);
    connect(thread_collentdata,&CollentDataThread::send,this,&SmartController::my_humiture_new);
}

void SmartController::compare()
{
    if(smart)
    {
        tmp=true;
        emit smart_signal();
        if(ill<ill_lv1&&ill>ill_lv2)
        {
            emit led1_on();
            emit led2_off();
            emit led3_off();
        }
        else if(ill<ill_lv2&&ill>ill_lv3)
        {
            emit led1_on();
            emit led2_on();
            emit led3_off();
        }
        else if(ill<ill_lv3)
        {
            emit led1_on();
            emit led2_on();
            emit led3_on();
        }
        if(tem>tem_max)
            emit fan_on();
        else
            emit fan_off();
    }
    else
    {
        if(tmp)
        {
            tmp=false;
            qDebug()<<"smart=false";
            emit init_signals();
        }
        
    }
    
}

void SmartController::settings_new(float ill_lv1_new,float ill_lv2_new,float ill_lv3_new,float tem_max_new,bool smart_new)
{
    ill_lv1=ill_lv1_new;
    ill_lv2=ill_lv2_new;
    ill_lv3=ill_lv3_new;
    tem_max=tem_max_new;
    smart=smart_new;
    compare();
}

void SmartController::my_humiture_new(float tem_new,float hum_new,float ill_new)
{
    tem=tem_new;
    hum=hum_new;
    ill=ill_new;
    compare();
}


