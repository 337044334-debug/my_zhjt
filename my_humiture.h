#ifndef MY_HUMITURE_H
#define MY_HUMITURE_H

#include <QWidget>
#include "collentdatathread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class My_Humiture; }
QT_END_NAMESPACE

class My_Humiture : public QWidget
{
    Q_OBJECT

public:
    My_Humiture(QWidget *parent = nullptr);
    ~My_Humiture();


private:
    Ui::My_Humiture *ui;
    QTimer *currentTime;
    QString hum;//湿度
    QString tem;//温度
    QString ill;//光照
    CollentDataThread thread_collentdata;//数据采集线程

private slots:
    void set_humAdtemAdill(QString tem,QString hum,QString ill);
    void timeUpdate();
};
#endif // MY_HUMITURE_H
