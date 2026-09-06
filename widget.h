#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "settings.h"
#include "collentdatathread.h"
#include "smartcontroller.h"
#include "control.h"
#include "pe15thread.h"
#include "login.h"
#include "calculate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

private:
    Ui::Widget *ui;
    Settings *settings;
    CollentDataThread *data_thread;
    SmartController *smart;
    Control *control;

    Pe15thread *pe15thread;
    Login *login;
    Calculate *calculate;

private slots:
    void login_show();
    void login_close();

};
#endif // WIDGET_H
