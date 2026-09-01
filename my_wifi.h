#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <QWidget>
#include <qradiobutton.h>
class set_wifi;

QT_BEGIN_NAMESPACE
namespace Ui { class My_WiFi; }
QT_END_NAMESPACE

class My_WiFi : public QWidget
{
    Q_OBJECT

public:
    My_WiFi(QWidget *parent = nullptr);
    ~My_WiFi();
    void Get_Wifi_Name();
    QRadioButton *wlangroup[16];
    QString wifiName;

private slots:
    void on_connectBTN_2_clicked();
    void on_connectBTN_clicked();


private:
    Ui::My_WiFi *ui;
    set_wifi *WifiDlg;
};
#endif // MY_WIFI_H
