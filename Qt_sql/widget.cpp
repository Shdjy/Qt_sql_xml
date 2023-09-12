#include "widget.h"
#include <QSqlError>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //qDebug() << QSqlDatabase::drivers();

    // 创建一个数据库连接，指定数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // 数据库连接需要设置的信息
    db.setHostName("localhost"); // 数据库服务器IP，我用的是本地电脑
    db.setDatabaseName("test");// 数据库名
    db.setUserName("root");// 用户名
    db.setPassword("123456");// 密码
    db.setPort(3306);// 端口号
    // 连接数据库
    bool ok = db.open();

    if (ok)
    {
        qDebug() << "database connect is ok";
    }
    else
    {
        qDebug() << "database connect is fail";
    }

    //实例化,执行sql语句
    QSqlQuery query(db);

    //从testa数据库中创建表
    query.exec("create table newUser(id int primary key,username text)");

    //插入操作
    qDebug()<<"---------------insert--------------";
//    insertUserName(db,1, "haodong");
//    insertUserName(db,2, "jiaqi");
//    insertUserName(db,3,"dongdong");


    //删除
    queryAllUser(db);
    deleteUser(db, "dongdong");
    //修改
    updateUser(db,2,"qiqi");
    //查询
    qDebug()<<"---------------select--------------";
    queryAllUser(db);
    //selectQueryUser(db, "haodong");


}

Widget::~Widget()
{
}

void Widget::insertUserName(QSqlDatabase db, const int &userid, const QString &name)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO newUser (id, username) VALUES(:id, :username)");
    query.bindValue(":id",userid);
    query.bindValue(":username",name);
    bool isOk = query.exec();
    qDebug()<<isOk;
    qDebug() << "error:" << query.lastError().text();
}


void Widget::queryAllUser(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.exec("select * from newUser");
    while(query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("username").toString();
        qDebug()<<"id:"<<id<<",name:"<<name;
    }
}

void Widget::selectQueryUser(QSqlDatabase db, const QString &username)
{
    QSqlQuery query(db);
    query.prepare("select * from newUser where username = :username");
    query.bindValue(":username",username);
    query.exec();
    while(query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("username").toString();
        qDebug()<<"id:"<<id<<",name:"<<name;
    }

}

void Widget::deleteUser(QSqlDatabase db, const QString &username)
{
    QSqlQuery query(db);
    query.prepare("delete from newUser where username = :username");
    query.bindValue(":username", username);
    query.exec();

}

void Widget::updateUser(QSqlDatabase db, const int &id, const QString &name)
{
    QSqlQuery query(db);
    query.prepare("update newUser set username = :name where id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name",name);
    query.exec();
}



