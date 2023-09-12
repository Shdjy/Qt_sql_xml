#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    //插入信息
    void insertUserName(QSqlDatabase db, const int &userid, const QString &name);
    //按照名字查询
    void selectQueryUser(QSqlDatabase db, const QString &username);
    //删除
    void deleteUser(QSqlDatabase db, const QString &username);
    //修改
    void updateUser(QSqlDatabase db, const int &id, const QString &name);
    //查找所有数据
    void queryAllUser(QSqlDatabase db);
};
#endif // WIDGET_H
