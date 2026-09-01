#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

QT_BEGIN_NAMESPACE
namespace Ui { class Weather; }
QT_END_NAMESPACE

class Weather : public QWidget
{
    Q_OBJECT

public:
    Weather(QWidget *parent = nullptr);
    ~Weather();

private slots:
    void replyFinished(QNetworkReply *reply); //天气数据处理槽函数

    void on_pushButton_weather_clicked();

private:
    Ui::Weather *ui;
    //请求句柄
    QNetworkAccessManager *manager;
    void sendQuest(QString cityStr);
};
#endif // WEATHER_H
