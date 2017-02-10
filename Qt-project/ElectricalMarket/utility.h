#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <QList>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <qtSql/QSqlError>
#include <QVariant>
#include <QDebug>

class Utility
{
public:
    static QString getCurDate();
    static void DBConnectFailed(QWidget *widget, const QString &str);
    static void InputError(QWidget *widget, const QString &title, const QString &error);
};

#endif // UTILITY_H
