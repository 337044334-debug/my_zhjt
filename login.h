#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "my_lineedit.h"
#include "syszuxpinyin.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "register.h"
#include "pe15thread.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    SyszuxPinyin *syszuxpinyin_send;
    ~Login();

private:
    Ui::Login *ui;
    Register* registerDialog;
    My_lineEdit *currentLineEdit;//虚拟键盘
    Pe15thread pe15thread;
    QSqlDatabase db;
    void init();//初始化->初始化数据库、建表、添加默认用户
    bool match();//登录界面用户与默认用户对比
    void createTable();//建表
    void insertInfo();//插入

signals:
    void loginsuccess();
    void loginfailed();
    void loginclose();

private slots:
    void keyboardshow_send(QString data);
    void keyboard_input_send(QString gemfield);   //接收键盘发过来的数据
    void on_pushButton_login_clicked();
    void on_pushButton_exit_clicked();
    void loginSlot();
};

#endif // LOGIN_H
