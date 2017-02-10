#include "utility.h"

QString Utility::getCurDate()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");       // yyyy-MM-dd hh:mm:ss
    QByteArray bytes = current_date.toLatin1();
    char *pDate = bytes.data();
    return QString(pDate);
}

void Utility::DBConnectFailed(QWidget *widget, const QString &str)
{
    QMessageBox::critical(widget, str,
                          QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
}

void Utility::InputError(QWidget *widget, const QString &title, const QString &error)
{
    QMessageBox::critical(widget, title, error, QMessageBox::Yes);
}

