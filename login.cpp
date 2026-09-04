#include "login.h"
#include "ui_login.h"


int Numberoferrors =3;

/*
<QSqlDatabase>  //添加、删除、复制、关闭数据库实例
<QSqlError>  //获取错误信息
<QSqlQuery>  //数据查询
*/

Login::Login(QWidget *parent) :
    QDialog(parent)
    ,ui(new Ui::Login)
    ,currentLineEdit(nullptr)
{
    ui->setupUi(this);
    registerDialog = new Register(this);
    //初始化数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    init();
    syszuxpinyin_send =new SyszuxPinyin();
    connect(ui->username,&My_lineEdit::send_show,this,&Login::keyboardshow_send);
    connect(ui->password,&My_lineEdit::send_show,this,&Login::keyboardshow_send);
    connect(syszuxpinyin_send,&SyszuxPinyin::sendPinyin,this,&Login::keyboard_input_send);
    connect(registerDialog,&Register::register_close,this,&Login::on_pushButton_exit_clicked);
}

Login::~Login()
{
    //关闭数据库
    if(db.isOpen())
        db.close();
    //关闭ui界面
    delete ui;
}


void Login::btn_hide()
{
    ui->Sign->hide();
    ui->main->hide();
}

void Login::btn_show()
{
    ui->Sign->show();
    ui->main->show();
}


void Login::init()
{    
    //创建usr数据库
    db.setDatabaseName("usr.db");
    //打开
    if(!db.open())
    {
        QMessageBox::warning(0, tr("Warning"), db.lastError().text());
        return;
    }

    createTable();//建表
    insertInfo();//插入
}

bool Login::match()//匹配
{
    //查询usrname对应的password
    QSqlQuery query(db);
    // ① 准备SQL
    query.prepare(
            "SELECT usrname FROM usr "
            "WHERE usrname = :username "
            "AND password = :password"
    );
    // ② 填入用户名
    query.bindValue(":username", ui->username->text());
    // ③ 填入密码
    query.bindValue(":password", ui->password->text());
    // ④ 执行SQL
    if(!query.exec())
        {
            qDebug() << query.lastError().text();
            return false;
        }
    // ⑤ 有没有查询到数据？
    if(query.next())
    {
        return true;
    }
    // ⑥ 没查询到
    return false;
}

void Login::createTable()//建表
{
    //创建一个数据库操作对象
    QSqlQuery sq;
    //如果没有就创建
    QString sql = "CREATE TABLE IF NOT EXISTS usr(usrname TEXT PRIMARY KEY,password TEXT NOT NULL);";
    if(sq.exec(sql))
        qDebug() << "CREATE TABLE success";
    else
        qDebug() << sq.lastError().text();
}

void Login::insertInfo()//插入
{
    QSqlQuery sq;
    //插入默认用户【usrname：usr；password：123】->没有才添加INSERT OR IGNORE
    QString sql = "INSERT OR IGNORE INTO usr(usrname,password) VALUES(\"usr\",\"123\");";
    if(sq.exec(sql))
        qDebug() << "INSERT INTO success";
    else
        qDebug() << sq.lastError().text();
}

void Login::keyboardshow_send(QString data)
{
    currentLineEdit = qobject_cast<My_lineEdit *>(sender());
    syszuxpinyin_send->lineEdit_window->setText(data);
    syszuxpinyin_send->resize(800,310);
    syszuxpinyin_send->move(120,280);
    syszuxpinyin_send->show();
}
void Login::keyboard_input_send(QString gemfield)
{
    if(currentLineEdit)
    {
        currentLineEdit->setText(gemfield);
    }
}

void Login::on_pushButton_login_clicked()
{

    bool ret =match();
    if(ret == true)
    {
        QMessageBox::information(this, tr("information"),"密码正确，门锁已打开");
   //重置错误次数
        Numberoferrors =3;        
        btn_show();        
//        beepunring();
//        connect(&pe15thread,SIGNAL(pesig()),this,SLOT(loginSlot()));
    }
    else
    {
        QString info;
        Numberoferrors--;
        switch(Numberoferrors)
        {
            case 2:
                info ="密码错误,还有3次机会";
                break;
            case 1:
                info ="密码错误,还有2次机会";
                break;
            case 0:
                info ="密码错误,还有1次机会";
                break;
            default:
                info ="即将报警";
                break;
        }

        QMessageBox::warning(this, tr("warning"),info);
        if(Numberoferrors <0)
        {
            qDebug() << Numberoferrors;
            //beepring();
        }
    }
}


void Login::on_pushButton_exit_clicked()
{
    emit loginclose();
}

void Login::on_Sign_clicked()
{
    this->hide();
    registerDialog->show();
}

void Login::on_main_clicked()
{
    emit loginclose();
}
