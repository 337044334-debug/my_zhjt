#include "calculate.h"
#include "ui_calculate.h"

#include <QDateTime>
#include <QTimer>

Calculate::Calculate(CollentDataThread* data_thread,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculate)
    ,brokerPort(1883)//MQTT端口(1883)
    ,currentTimestamp("0")//时间戳
    ,clientId("zhjt")//MQTT客户端ID
    ,thread_collentdata(data_thread)
    ,tem(0.0)
    ,hum(0.0)
    ,ill(0.0)
{
    ui->setupUi(this);

    syszuxpinyin_send =new SyszuxPinyin();
    connect(ui->lineEdit_coreid,&My_lineEdit::send_show,this,&Calculate::keyboardshow_send);
    connect(ui->lineEdit_devkey,&My_lineEdit::send_show,this,&Calculate::keyboardshow_send);
    connect(ui->lineEdit_devsecret,&My_lineEdit::send_show,this,&Calculate::keyboardshow_send);
    connect(ui->lineEdit_time,&My_lineEdit::send_show,this,&Calculate::keyboardshow_send);
    connect(syszuxpinyin_send,&SyszuxPinyin::sendPinyin,this,&Calculate::keyboard_input_send);

    m_client = new QMqttClient(this);
    m_timer = new QTimer;
    ui->lineEdit_coreid->setText("aelakbg");
    ui->lineEdit_devkey->setText("zhjt");
    ui->lineEdit_devsecret->setText("PNUeAURoSqNYmtKr");
    
    connect(thread_collentdata,&CollentDataThread::send,this,&Calculate::my_humiture_new);

}

Calculate::~Calculate()
{
    delete ui;
}

void Calculate::my_humiture_new(float tem_new,float hum_new,float ill_new)
{
    tem=tem_new;
    hum=hum_new;
    ill=ill_new;
}


void Calculate::on_pushButton_calculate_clicked()
{
    username.clear();//MQTT登录用户名
    password.clear();//MD5之前的原始字符串
    password_md5.clear();//MD5之后的最终密码
    brokerAddr.clear();//MQTT服务器地址
    ioTCoreld = ui->lineEdit_coreid->text();//IoT Core ID
    deviceKey = ui->lineEdit_devkey->text();//设备Key
    deviceSecret = ui->lineEdit_devsecret->text();//设备Secret    

    /*brokerAddr->MQTT服务器地址
    brokerAddr在 IoT Core 详情页可以查看。
    也可通过 IoTCoreId+ .iot.+Region+.baidubce.com 拼接出来，
    其中 Region 即地域，在创建 IoT Core 时当前可选广州gz
    */
    if(ui->comboBox_city->currentText() =="广州")
        brokerAddr = brokerAddr
                    .append(ioTCoreld)
                    .append(".iot.")
                    .append("gz")
                    .append(".baidubce.com");
    else
        brokerAddr = brokerAddr
                    .append(ioTCoreld)
                    .append(".iot.")
                    .append("bj")
                    .append(".baidubce.com");

    /*usernam->MQTT登录用户名
    用户名拼接方式为 
    {adp_type}@{IoTCoreId}|{DeviceKey}|{timestamp}|{algorithm_type}
    adp_type：认证方式类型，当前仅支持取值“thingidp”  
    timestamp：生成签名时的时间戳，以秒为单位，长整数。可以不用传入。
    */
    username = username
                .append("thingidp")
                .append("@")
                .append(ioTCoreld)
                .append("|")
                .append(deviceKey)
                .append("|")
                .append(currentTimestamp)
                .append("|")
                .append("MD5");

    /*password->MD5之前的原始字符串
    组合加密字符串：
    {device_key}&{timestamp}&{algorithm_type}{device_secret}
    */
    password = password
                .append(deviceKey)
                .append("&")
                .append(currentTimestamp)
                .append("&")
                .append("MD5")
                .append(deviceSecret);
    /*password_md5->MD5之后的最终密码
    对加密字符串进行加密：使用MD5或者SHA256，对加密字符串进行加密。具体过程如下：
    1、获取加密字符串的UTF-8字符集比特数组；
    2、按选定的加密方式，对ioTCoreld中得到比特数组使用MD5或者SHA256进行加密
    3、将结果转换为小写形式    
    */
    QByteArray password_md5result;
    QCryptographicHash md((QCryptographicHash::Md5));
    md.addData(password.toUtf8());
    password_md5result = md.result();
    password_md5.append(password_md5result.toHex());

    ui->pushButton_connectmqtt->setEnabled(true);
    QMessageBox::information(this, tr("information"),"计算完成，请点击连接");
}
/*  获取时间戳  */
void Calculate::on_pushButton_gettime_clicked()
{
    qint64 timeT = QDateTime::currentSecsSinceEpoch();   //获取当前时间
    currentTimestamp = QString::number(timeT);
    ui->lineEdit_time->setText(currentTimestamp);
}

/*  连接百度云  */
void Calculate::on_pushButton_connectmqtt_clicked()
{
    //    qDebug()<<"brokerAddr ="<< brokerAddr;
    //    qDebug()<<"username ="<< username;
    //    qDebug()<<"password ="<< password_md5;
    //    qDebug()<<mqttTopic;

    connect(m_client,&QMqttClient::connected,this,&Calculate::mqttconnectSlot);//根据接受的信息输出控制
    //未连接服务器则连接
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->pushButton_connectmqtt->setText(tr(""));
        m_client->setHostname(brokerAddr);
        m_client->setPort(brokerPort);
        m_client->setUsername(username);
        m_client->setPassword(password_md5);
        m_client->connectToHost();
        QMessageBox::information(this, tr("information"),"连接成功");
        //定时器初始化
        InitTimer();
        connect(m_client,&QMqttClient::messageReceived,this,&Calculate::messageReceived);

        ui->pushButton_connectmqtt->setStyleSheet("background-image:url(:/icon/disconnect.png);border-style:outset;");

    }
        else
        {
            //断开连接
            ui->pushButton_connectmqtt->setStyleSheet("background-image:url(:/icon/4.png);border-style:outset;");
            QMessageBox::information(this, tr("information"),"断开连接");
            m_client->disconnectFromHost();
        }
}

void Calculate::InitTimer()
{

    //设置定时器是否为单次触发。默认为 false 多次触发
    m_timer->setSingleShot(false);
    //启动或重启定时器, 并设置定时器时间：毫秒
    m_timer->start(5000);
    //定时器触发信号槽
    connect(m_timer,&QTimer::timeout,this,&Calculate::TimertimeOut);
}
/*  发送信息  */
void Calculate::TimertimeOut()
{
    //发送地址
    mqttTopic = "$iot/zhjt/user/fortest";

    //消息封装为Json格式
    QJsonObject jsonObject;
    jsonObject["temperature"] = QString::number(tem,'f',2);
    jsonObject["humidity"] = QString::number(hum,'f',2);
    jsonObject["illumination"] = QString::number(ill,'f',2);

    QJsonDocument jsonDocument(jsonObject);

    // QJsonDocument::toJson()【压缩 JSON，不要多余的空格和换行】 返回 QByteArray
    QByteArray mqttMessage = jsonDocument.toJson(QJsonDocument::Compact);

    qDebug() << "发送数据:" << mqttMessage;

    if (m_client->publish(mqttTopic, mqttMessage) == -1)
    {
        QMessageBox::critical(
            this,
            "Error",
            "连接断开或输入的topic有误，无法发布",
            QMessageBox::Yes
        );

        m_timer->stop();
    }
}


/*  接收信息  */
void Calculate::messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug()<<"messageReceived:"<<topic.name()<<QString(message);
    QJsonObject json_object = QJsonDocument::fromJson(message).object();
//    qDebug() <<json_object;
//    qDebug() <<json_object.value("led1").toInt();
    QStringList jsonlist = json_object.keys();
    QString key = jsonlist[jsonlist.size()-1];
    if(key == "led1")
    {
        if(json_object.value("led1").toInt() ==1)
        {
            emit led1_on();
        }            
        else
            emit led1_off();
    }
    else if (key == "led2")
    {
        if(json_object.value("led2").toInt() ==1)
            emit led2_on();
        else
            emit led2_off();
    }
    else if (key == "led3")
    {
        if(json_object.value("led3").toInt() ==1)
            emit led3_on();
        else
            emit led3_off();
    }
    else if (key == "fan")
    {
        if(json_object.value("fan").toInt() ==255)
            emit fan_on();
        else
        {
           emit fan_off();
        }
    }
    else if (key == "beep")
    {
        if(json_object.value("beep").toInt() ==1)
        {
            emit beep_on();
        }
        else
        {
            emit beep_off();
        }
    }
}



void Calculate::mqttconnectSlot()
{
    qDebug()<<"sub";
    QString subScribeTopic ="$iot/zhjt/user/control";
    m_client->subscribe(subScribeTopic);
}

/*  虚拟键盘  */

void Calculate::keyboardshow_send(QString data)
{
    currentLineEdit = qobject_cast<My_lineEdit *>(sender());
    syszuxpinyin_send->lineEdit_window->setText(data);
    syszuxpinyin_send->resize(800,310);
    syszuxpinyin_send->move(120,280);
    syszuxpinyin_send->show();
}
void Calculate::keyboard_input_send(QString gemfield)
{
    if(currentLineEdit)
    {
        currentLineEdit->setText(gemfield);
    }
}

