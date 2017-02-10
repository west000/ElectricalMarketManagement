#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <qtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QBoxLayout>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("electricalmarket");
    db.setUserName("root");
    db.setPassword("westlife312");
    if(db.open())
    {
        qDebug()<<"success!";
    }
    else
    {
        qDebug()<<"failure";
        QMessageBox::critical(0, QObject::tr("Database Error"),
                                      db.lastError().text());
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}

