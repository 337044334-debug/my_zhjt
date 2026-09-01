#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    syszuxpinyin_send =new SyszuxPinyin();
    connect(ui->username,&My_lineEdit::send_show,this,&Register::keyboardshow_send);
    connect(ui->password,&My_lineEdit::send_show,this,&Register::keyboardshow_send);
    connect(syszuxpinyin_send,&SyszuxPinyin::sendPinyin,this,&Register::keyboard_input_send);
}

Register::~Register()
{
    delete ui;
}

bool Register::insertusr()
{
    QString name = ui->username->text();
    QString password = ui->password->text();
    if (name == ""||password == "")
    {
        QMessageBox::warning(this,"警告","用户名密码不能为空");
        return false;
    }
    QSqlQuery sq;
    //防止sql注入问题
    QString sql = "INSERT INTO usr VALUES(?,?)";
    //预处理
    sq.prepare(sql);
    //占位符数据替换
    sq.addBindValue(name);
    sq.addBindValue(password);
    //执行sql语句
    if(sq.exec())
    {
        QMessageBox::information(this,"通知","注册成功");
    }
    else
    {
        QString errorMsg = sq.lastError().text();
        if(errorMsg=="UNIQUE constraint failed: usr.usrname Unable to fetch row")
            QMessageBox::critical(this,"错误","用户名已存在，请更换用户名！");
        else
            QMessageBox::critical(this,"错误",errorMsg);
    }
    return false;
}

void Register::keyboardshow_send(QString data)
{
    currentLineEdit = qobject_cast<My_lineEdit *>(sender());
    syszuxpinyin_send->lineEdit_window->setText(data);
    syszuxpinyin_send->resize(800,310);
    syszuxpinyin_send->move(120,280);
    syszuxpinyin_send->show();
}
void Register::keyboard_input_send(QString gemfield)
{
    if(currentLineEdit)
    {
        currentLineEdit->setText(gemfield);
    }
}

void Register::on_pushButton_register_clicked()
{
    insertusr(); //插入
}


void Register::on_pushButton_exit_2_clicked()
{
    close();
}

