#include "my_wifi.h"
#include "ui_my_wifi.h"
#include "set_wifi.h"

#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QMessageBox>

My_WiFi::My_WiFi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::My_WiFi)
{
    ui->setupUi(this);
    WifiDlg = new set_wifi(this);

    wlangroup[0]=ui->radioButton;
    wlangroup[1]=ui->radioButton_2;
    wlangroup[2]=ui->radioButton_3;
    wlangroup[3]=ui->radioButton_4;
    wlangroup[4]=ui->radioButton_5;
    wlangroup[5]=ui->radioButton_6;
    wlangroup[6]=ui->radioButton_7;
    wlangroup[7]=ui->radioButton_8;
    wlangroup[8]=ui->radioButton_9;
    wlangroup[9]=ui->radioButton_10;
    wlangroup[10]=ui->radioButton_11;
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    QThread::msleep(100);
    Get_Wifi_Name();//获取wifi名称
}

//获取wifi名称
void My_WiFi::Get_Wifi_Name()
{
    QStringList arguments;
    QProcess process;
    system("wpa_cli -i wlan0 scan");
    QThread::msleep(100);
    arguments << "-i" << "wlan0" << "scan_results";
    process.start("wpa_cli",arguments);
    if(!process.waitForFinished()){
        qDebug() << "Failed execute command";
        return;
    }
    //获取wifi的全部信息【ac:92:32:91:9d:b0	2462	-29	[WPA2-PSK-CCMP][WPS][ESS]	ufoooooo_5G】
    QByteArray output = process.readAllStandardOutput();
    QString result = QString::fromLocal8Bit(output);
    QStringList wifiList = result.split("\n");
    //提取WiFi名字【第五列】
    QStringList wifiNames;
    for (int i =0;i < wifiList.size();i++) {
        QString wifiInfo = wifiList.at(i);
        QStringList infoList = wifiInfo.split("\t");
        if(infoList.size() >= 5){
            QString wifiNamelist = infoList.at(4);
            wifiNames.append(wifiNamelist);
        }
    }
    //将WiFi名字输出到ui界面
    for (int i = 0;i < wifiNames.size() && i < 11;i++){
        QString wifiName = wifiNames.at(i);
        qDebug() << wifiName;
        wlangroup[i]->setVisible(true);
        wlangroup[i]->setText(wifiName);
    }

}

My_WiFi::~My_WiFi()
{
    delete ui;
}


void My_WiFi::on_connectBTN_2_clicked()
{
    Get_Wifi_Name();
    QMessageBox::information(this,tr("Connect information"), tr("成功!"));
}


void My_WiFi::on_connectBTN_clicked()
{

    // 先找用户选择的 WiFi
        for(int i = 0; i < 16; i++)
        {
            if(wlangroup[i]->isChecked())
            {
                // 选中的 WiFi 变蓝
                wlangroup[i]->setStyleSheet(
                    "color:rgb(114, 159, 207);"
                );

                // 保存 WiFi 名称
                wifiName = wlangroup[i]->text();

                // 创建新的网络配置
                system("wpa_cli -i wlan0 add_network > i.ini");

                // 打开密码输入窗口
                WifiDlg->show();
                WifiDlg->setWifiName(wifiName);  // 传递成员变量的值

                return;
            }
        }

        // 没有选择 WiFi
        QMessageBox::warning(
            this,
            "Warning",
            "请选择要连接的网络",
            QMessageBox::Yes
        );

}

