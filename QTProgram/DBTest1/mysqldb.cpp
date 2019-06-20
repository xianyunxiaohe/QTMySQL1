#include "mysqldb.h"

MySQLDB::MySQLDB()
{
    isopen = false;
    OpenDB();
    query = QSqlQuery(db);
}
MySQLDB::~MySQLDB()
{
    if(NULL != mysql)
    {
        delete  mysql ;
        mysql = NULL;
    }
}
bool MySQLDB::OpenDB()
{
    if (false == isopen) {

        db=QSqlDatabase::addDatabase("QMYSQL");
        //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
        db.setHostName("127.0.0.1");
        //连接数据库端口号，与设置一致
        db.setPort(3308);
        //连接数据库名，与设置一致
        db.setDatabaseName("foodcomment");
        //数据库用户名，与设置一致
        db.setUserName("root");
        db.setPassword("123456");
        //数据库密码，与设置一致
        db.open();
        if(!db.open())
        {
            qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
            return false;
        }
        else
        {
            qDebug()<<"连接成功"<<"connect to mysql OK";
            isopen = true;
        }
    }
}

bool MySQLDB::CloseDB()
{
    db.close();
    isopen = false;
    return true;
}
//执行SQL更新语句
int MySQLDB::ExecUpdataSQl(QString sql)
{
    //OpenDB();
    //QSqlQuery query(db);
    query.clear();
    int res = query.exec(sql);
    qDebug()<<"sql:"<<sql;
    return res;
}
//执行SQL查询语句
QSqlQuery MySQLDB::ExecSelectSQL(QString sql)
{
    //OpenDB();
    //QSqlQuery query(db);
    query.clear();
    query.exec(sql);
    return query;
}
MySQLDB *MySQLDB::GetMysql()
{

    if(NULL == mysql){
        std::mutex mt;
        mt.lock();
        if(NULL == mysql)
        {
            mysql = new MySQLDB();
        }
        mt.unlock();
    }
    return mysql;
}

MySQLDB *MySQLDB::mysql = NULL;

