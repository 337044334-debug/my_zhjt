#include "set_wifi.h"
#include "ui_set_wifi.h"
#include "my_lineedit.h"
#include <QMessageBox>
#include <QDebug>
set_wifi::set_wifi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_wifi)
{
    ui->setupUi(this);

    syszuxpinyin_send =new SyszuxPinyin();
    connect(ui->password_edit,&My_lineEdit::send_show,this,&set_wifi::keyboardshow_send);
    connect(syszuxpinyin_send,&SyszuxPinyin::sendPinyin,this,&set_wifi::confirmString_send);
}

set_wifi::~set_wifi()
{
    delete ui;
}
//调用name
void set_wifi::setWifiName(const QString &name)
{
    m_wifiName = name;
}

//读取i的值
int set_wifi::get_i()
{
    char buf[32] = {0};
    FILE* fp0 = fopen("i.ini", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp0);
    QString str = buf;
    return str.toInt();
}
//验证是否登陆成功
QString set_wifi::get_TorF()
{
    char buf[32] = {0};
    FILE* fp = fopen("TorF.ini", "r+");//读写方式打开
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), fp);
    QString str = buf;
    return str;
}

void set_wifi::keyboardshow_send(QString data)
{
    syszuxpinyin_send->lineEdit_window->setText(data);
    syszuxpinyin_send->resize(800,310);
    syszuxpinyin_send->move(120,280);
    syszuxpinyin_send->show();
}

void set_wifi::confirmString_send(QString gemfield)
{
    ui->password_edit->setText(gemfield);
}

void set_wifi::on_pushButton_clicked()
{
    char set_ssid[64];
    char set_password[64];
    char select_wlan[64];
        QString passwordtext = ui->password_edit->text();

        if (ui->password_edit->text().isEmpty() || passwordtext.length() < 8) {
                  QMessageBox::critical(this,
                       tr("Connect information"),
                       tr("密码不能为空且长度必须大于等于8位"));
                   return;
        }
            int i =get_i();
            sprintf(set_ssid,"wpa_cli -i wlan0 set_network %d ssid '\"%s\"'",i,m_wifiName.toLatin1().data());
            sprintf(set_password, "wpa_cli -i wlan0 set_network %d psk '\"%s\"' ",i,ui->password_edit->text().toLatin1().data());
            sprintf(select_wlan, "wpa_cli -i wlan0 select_network %d ",i);
            system(set_ssid);
            system(set_password);
            system("wpa_cli -i wlan0 list_network");
            system(select_wlan);
            QFile file("./TorF.ini");
            file.open(QFile::WriteOnly|QFile::Truncate);
            file.close();
            system("udhcpc -i wlan0 -B -n > TorF.ini");
            qDebug()<< get_TorF().data()->toUpper();
            if(get_TorF() == "")
            {
                QMessageBox::warning(this,tr("Connect information"), tr("连接错误"));
                return ;
            }
            char echo_1[64];
            char echo_2[64];
            sprintf(echo_1,"echo \"nameserver 114.114.114.114\" > /etc/resolv.conf");
            system(echo_1);
            sprintf(echo_2,"echo \"nameserver 8.8.8.8\" > /etc/resolv.conf");
            system(echo_2);
            close();
            QMessageBox::information(this, tr("Connect information"), tr("连接成功"));
}


void set_wifi::on_pushButton_2_clicked()
{
    close();
}

