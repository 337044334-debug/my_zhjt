#ifndef CALCULATE_H
#define CALCULATE_H

#include <QWidget>
#include "syszuxpinyin.h"
#include "my_lineedit.h"
#include "collentdatathread.h"
#include <QtMqtt/qmqttclient.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculate; }
QT_END_NAMESPACE

class Calculate : public QWidget
{
    Q_OBJECT

public:
    explicit Calculate(CollentDataThread* data_thread,QWidget *parent = nullptr);
    SyszuxPinyin *syszuxpinyin_send;
    ~Calculate();

signals:
    void led1_on();
    void led2_on();
    void led3_on();
    void led1_off();
    void led2_off();
    void led3_off();
    void fan_on();
    void fan_off();
    void beep_on();
    void beep_off();

private:
    Ui::Calculate *ui;
    My_lineEdit *currentLineEdit;//虚拟键盘

    QMqttClient  *m_client;//mqtt client指针
    QString currentTimestamp;//时间戳
    QString ioTCoreld;
    QString deviceKey;
    QString deviceSecret;
    QString brokerAddr;
    int brokerPort;//MQTT端口(1883)
    QString clientId;//MQTT客户端ID
    QString username;
    QString password;
    QString password_md5;
    QString mqttTopic;
    QString mqttMessage;
    QTimer *m_timer;
    void InitTimer();

    /*  在数据采集模块  */
    CollentDataThread* thread_collentdata;
    float hum;
    float tem;
    float ill;

private slots:
    void keyboardshow_send(QString data);
    void keyboard_input_send(QString gemfield);   //接收键盘发过来的数据
    void on_pushButton_gettime_clicked();
    void on_pushButton_calculate_clicked();
    void on_pushButton_connectmqtt_clicked();

    void messageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void TimertimeOut();
    void mqttconnectSlot();

    void my_humiture_new(float,float,float);
};
#endif // CALCULATE_H
