#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 连接数据库
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QODBC");
    sqldb.setHostName("localhost");
    sqldb.setPort(3306);
    sqldb.setDatabaseName("Mysql");
    sqldb.setUserName("root");
    sqldb.setPassword("wxc123...");
    if (!sqldb.open()) {
        QMessageBox::critical(0, QObject::tr("后台数据库连接失败"), "无法创建连接!请检查排除故障后重启程序.", QMessageBox::Cancel);
    }
    Login w;

    w.show();

    return a.exec();
}
