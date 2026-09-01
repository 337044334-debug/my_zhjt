#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
// #include "pe15thread.h"
// #include "login.h"

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
    // Pe15thread *pe15thread;
    // Login *login;

private slots:
    //void login_show();

};
#endif // WIDGET_H
