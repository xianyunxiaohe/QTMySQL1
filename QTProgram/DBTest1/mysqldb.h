#ifndef MYSQLDB_H
#define MYSQLDB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <iostream>
#include <thread>
#include <mutex>

class MySQLDB
{
public:
    ~MySQLDB();
    //连接mysql数据库
    bool OpenDB();
    //关闭mysql数据库连接
    bool CloseDB();
    //执行SQL查询语句
    QSqlQuery ExecSelectSQL(QString sql);
    //执行SQL更新语句
    int ExecUpdataSQl(QString sql);
    //获取MySQLDB单例
    static MySQLDB *GetMysql();
private:
    MySQLDB();
    QSqlDatabase db;
    bool isopen;
    static MySQLDB *mysql;
    QSqlQuery query;
};

#endif // MYSQLDB_H
