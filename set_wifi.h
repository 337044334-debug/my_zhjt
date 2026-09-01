#ifndef SET_WIFI_H
#define SET_WIFI_H

#include <QDialog>
#include "syszuxpinyin.h"


namespace Ui {
class set_wifi;
}

class set_wifi : public QDialog
{
    Q_OBJECT

public:
    explicit set_wifi(QWidget *parent = nullptr);
    ~set_wifi();
    SyszuxPinyin *syszuxpinyin_serialName;
    SyszuxPinyin *syszuxpinyin_send;
    int get_i();
    QString get_TorF();
    void setWifiName(const QString &name);  // 添加设置方法
private:
    Ui::set_wifi *ui;
    QString m_wifiName;  // 添加成员变量存储WiFi名称

private slots:
    void keyboardshow_send(QString data);
    void confirmString_send(QString gemfield);   //接收键盘发过来的数据
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // SET_WIFI_H
