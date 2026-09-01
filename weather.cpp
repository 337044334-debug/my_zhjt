#include "weather.h"
#include "ui_weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Weather)
{
    ui->setupUi(this);
    QStringList cityList = QString("石家庄、太原、沈阳、长春、哈尔滨、南京、杭州、合肥、福州、南昌、济南、郑州、武汉、长沙、广州、海口、成都、贵阳、昆明、西安、兰州、西宁、台北").split("、");
    ui->comboBox->addItems(cityList);
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager,&QNetworkAccessManager::finished,this,&Weather::replyFinished);//完成网络回复

}

Weather::~Weather()
{
    delete ui;
}

void Weather::replyFinished(QNetworkReply *reply)
{
    QString all = reply->readAll();//读取回复内容
    QJsonParseError err;//JSON解析的错误
    QJsonDocument json_recv = QJsonDocument::fromJson(all.toUtf8(), &err);//读写JSON【fromJson：JSON解析】
    qDebug()<<"all:"<<all;
    if (!json_recv.isNull() && err.error == QJsonParseError::NoError)
    {
        QJsonObject object = json_recv.object();//包装为JSON对象
        QStringList keys = object.keys();//返回所有键列表
        for (const QString& key : keys) {
            qDebug() << "Key:" << key;
        }
        QString weather_type = object.value("wea").toString();
        qDebug()<<"weather_type :"<<weather_type;
        QString tuijian = object.value("air_tips").toString();
        qDebug()<<"tuijian: "<<tuijian;
        QString low = object.value("tem2").toString();
        qDebug()<<"low :"<<low;
        QString high = object.value("tem1").toString();
        QString wendu = low + "℃~" + high + "℃";
        qDebug()<<"wendu: "<<wendu;
        QString strength = object.value("win_speed").toString();
        qDebug()<<"strength: "<<strength;
        QString fengli = object.value("win").toString() + strength;
        qDebug()<<"fengli: "<<fengli;
        ui->label_weather->setText(weather_type);    //显示天气类型
        ui->label_temperature->setText(wendu);      //温度
        ui->label_wind->setText(fengli);              //风力
        ui->label_recommend->setText(tuijian);      //推荐
    }
    else{
        ui->label_recommend->setText( "json_recv is NULL or is not a object !");
        qDebug() << "recv weather data! error:"<< err.error;
    }
    reply->deleteLater(); //销毁请求对象
}


void Weather::on_pushButton_weather_clicked()
{
    QString local_city = ui->comboBox->currentText().trimmed(); //获得需要查询天气的城市名称
    sendQuest(local_city);//发送网络请求
}

void Weather::sendQuest(QString cityStr)
{
    QString url =
        "http://v0.yiketianqi.com/api?unescape=1&version=v61"
        "&appid=13717381&appsecret=S3yuPKG9&city=" + cityStr;
    QNetworkRequest quest;
    quest.setUrl(QUrl(url));
    quest.setHeader(QNetworkRequest::UserAgentHeader, "RT-Thread ART");
    manager->get(quest);
}

