#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <iostream>
#include <fstream>
#include "mysqldb.h"

using namespace std;
void connect_mysql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3308);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("foodcomment");      //连接数据库名，与设置一致
    db.setUserName("root");          //数据库用户名，与设置一致
    db.setPassword("123456");    //数据库密码，与设置一致
    db.open();
    if(!db.open())
    {
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        return ;
    }
    else
    {
        qDebug()<<"连接成功"<<"connect to mysql OK";
    }
    QSqlQuery query(db);
    query.exec("select * from food");
    while(query.next()){
        qDebug()<<query.value("keywords").toString();
    }
}
int main()
{
    ifstream inFile("F:\\A1YanHe\\out.txt", ios::in);
    std::string lineStr;
    MySQLDB* mydb = MySQLDB::GetMysql();

    int i = 0;
    while (!inFile.eof())
    {
        getline(inFile, lineStr);
        if (lineStr.find("Line", 0) != string::npos)
        {
            i++;
        }
        if (lineStr.find("positive_prob", 0) != string::npos)
        {
            lineStr.replace(0, 14, "");

            QString sql = QString("update   food  set emotion_positive_prob = '%1'  where id='%2'")
                    .arg( QString::fromStdString(lineStr))
                    .arg(i);

            mydb->ExecUpdataSQl(sql);
        }
        if (lineStr.find("confidence", 0) != string::npos)
        {
            lineStr.replace(0, 11, "");

            QString sql = QString("update   food set emotion_confidengce= '%1'  where id='%2'")
                    .arg( QString::fromStdString(lineStr))
                    .arg(i);

            mydb->ExecUpdataSQl(sql);
        }
//        if (i== 5) {
//            break;
//        }

    }
    return 0;
}

int main02(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);
    //connect_mysql();
    MySQLDB* mydb = MySQLDB::GetMysql();
    QSqlQuery query = mydb->ExecSelectSQL("select * from food");
    while(query.next()){
        qDebug()<<query.value("keywords").toString();
    }
    return a.exec();
}
int main01()
{
    ifstream inFile("F:\\A1YanHe\\EOout.txt", ios::in);
    std::string lineStr;
    MySQLDB* mydb = MySQLDB::GetMysql();

    int i = 0;
    while (!inFile.eof())
    {
        getline(inFile, lineStr);
        if (lineStr.find("keywords", 0) != string::npos)
        {
            lineStr.replace(0, 11, "");
            i++;
            QString sql = QString("insert into   food (id,keywords) values( '%1','%2' )")
                    .arg(i)
                    .arg( QString::fromStdString(lineStr));

            mydb->ExecUpdataSQl(sql);
        }

    }
    return 0;
}
