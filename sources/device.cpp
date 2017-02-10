#include "device.h"
#include "utility.h"

bool Device::insertNewDeviceToDB(const QString &name, const QString &prod, const QString &code, const QString &date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO device(barcode, dname, makedate, productor) VALUES (?, ?, ?, ?)");
    QVariant vcode = code;
    QVariant vname = name;
    QVariant vdate = date;
    QVariant vprod = prod;
    query.addBindValue(vcode);
    query.addBindValue(vname);
    query.addBindValue(vdate);
    query.addBindValue(vprod);

    if(!query.exec())
        return false;

    query.finish();
    return true;
}

bool Device::searchAll(QList<Device> &result)
{
    QSqlQuery query;
    query.exec("SELECT barcode, dname, makedate, productor FROM device");

    while(query.next())
    {
        QString barcode = query.value(0).toString();
        QString dname = query.value(1).toString();
        QString date = query.value(2).toString();
        QString prod = query.value(3).toString();
        Device d(dname, prod, barcode, date);
        result.push_back(d);
    }
    return true;
}

bool Device::searchByBarCode(const QString &code)
{
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM device WHERE barcode=?");
    QVariant vCode = code;
    query.addBindValue(vCode);
    query.exec();

    int num;
    if(query.next())
    {
        num = QString(query.value(0).toString()).toInt();
        if(num == 1)
            return true;
        return false;
    }
    return false;
}
