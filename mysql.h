#ifndef MYSQL_H
#define MYSQL_H

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QUuid>
#include "mainwindow.h"
#include "addinfo.h"
#include "addfault.h"


class MySql
{

public:
    MySql();
    static void initsql();                     //初始化连接数据库
    static QSqlDatabase getDb(){return db;}
    void createtable();            //建表 索引 触发器
    bool inituser(QString man_sys,QString man_model,QString man_num);                               //将注册信息添加数据库
    //bool loguser(QString name,QString passward);                                                           //验证登录信息
    //bool forgetpassward(QString name,QString identify);                                                 //根据姓名和身份信息找回密码
    bool addstu(my_stu* stu);                                                                                               //添加设备信息
    bool updatestu(my_stu* stu);                                                                                         //修改设备信息
    bool deletestu(QString man_sys);                                                                                   //删除设备信息
    bool addfau(my_fau* stu);  //增加故障信息
    bool selectfau(my_stu *stu);//查询故障信息

private:
    QSqlQuery *query;
    static QSqlDatabase db;
};

#endif // MYSQL_H
