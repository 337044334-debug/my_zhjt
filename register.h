#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "my_lineedit.h"
#include "syszuxpinyin.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    SyszuxPinyin *syszuxpinyin_send;
    ~Register();

private:
    Ui::Register *ui;
    My_lineEdit *currentLineEdit;//虚拟键盘
    QSqlDatabase db;
    bool insertusr();//插入

private slots:
    void keyboardshow_send(QString data);
    void keyboard_input_send(QString gemfield);   //接收键盘发过来的数据
    void on_pushButton_register_clicked();
    void on_pushButton_exit_2_clicked();

signals:
    void register_close();

};

#endif // REGISTER_H
