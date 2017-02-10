#include "store.h"
#include "utility.h"

Store::Store()
{

}

bool Store::insertToStore(QList<Store> &list)
{
    QSqlQuery query;
    query.prepare("INSERT INTO store(pID, barcode, lavenum) VALUES(?, ?, ?)");
    QVariantList ids;
    QVariantList codes;
    QVariantList nums;
    for(const auto &s : list)
    {
        ids << s.pID;
        codes << s.barcode;
        nums << int(s.num);
        qDebug() << s.num;
    }
    query.addBindValue(ids);
    query.addBindValue(codes);
    query.addBindValue(nums);

    if(!query.execBatch())
    {
        return false;
    }

    query.finish();
    return true;
}

bool Store::modifyStoreByCodeAndID(const QString &code, const QString &id, unsigned num)
{
    QSqlQuery query;
    query.prepare("UPDATE store\
                  SET lavenum=?\
                  WHERE barcode=? and pID=?");
    QVariant vNum = num;
    QVariant vCode = code;
    QVariant vID = id;

    query.addBindValue(vNum);
    query.addBindValue(vCode);
    query.addBindValue(vID);

    if(!query.exec())
        return false;

    query.finish();
    return true;
}

bool Store::searchByPID(const QString &id, QList<Store> &result)
{
    QSqlQuery query;
    query.prepare("SELECT store.pID, pdate, store.barcode, dname, lavenum\
                  FROM store, purchase, device\
                  WHERE store.pID=purchase.pID and store.barcode=device.barcode and purchase.pID=?");
    QVariant vID = id;
    query.addBindValue(vID);

    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        QString code = query.value(2).toString();
        QString name = query.value(3).toString();
        unsigned n = QString(query.value(4).toString()).toInt();

        Store s(id, date, code, name, n);
        result.push_back(s);
    }
    query.finish();
    return true;
}

bool Store::searchByPDate(const QString &date, QList<Store> &result)
{
    QSqlQuery query;
    query.prepare("SELECT store.pID, pdate, store.barcode, dname, lavenum\
                  FROM store, purchase, device\
                  WHERE store.pID=purchase.pID and store.barcode=device.barcode and pdate=?");
    QVariant vDate = date;
    query.addBindValue(vDate);

    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        QString code = query.value(2).toString();
        QString name = query.value(3).toString();
        unsigned n = QString(query.value(4).toString()).toInt();

        Store s(id, date, code, name, n);
        result.push_back(s);
    }
    query.finish();
    return true;
}

bool Store::searchByBarCode(const QString &code, QList<Store> &result)
{
    QSqlQuery query;
    query.prepare("SELECT store.pID, pdate, store.barcode, dname, lavenum\
                  FROM store, purchase, device\
                  WHERE store.pID=purchase.pID and store.barcode=device.barcode and store.barcode=?");
    QVariant vCode = code;
    query.addBindValue(vCode);

    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        QString code = query.value(2).toString();
        QString name = query.value(3).toString();
        unsigned n = QString(query.value(4).toString()).toInt();

        Store s(id, date, code, name, n);
        result.push_back(s);
    }
    query.finish();
    return true;
}

bool Store::searchByDname(const QString &name, QList<Store> &result)
{
    QSqlQuery query;
    query.prepare("SELECT store.pID, pdate, store.barcode, dname, lavenum\
                  FROM store, purchase, device\
                  WHERE store.pID=purchase.pID and store.barcode=device.barcode and dname=?");
    QVariant vName = name;
    query.addBindValue(vName);

    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        QString code = query.value(2).toString();
        QString name = query.value(3).toString();
        unsigned n = QString(query.value(4).toString()).toInt();

        Store s(id, date, code, name, n);
        result.push_back(s);
    }
    query.finish();
    return true;
}

bool Store::searchAll(QList<Store> &result)
{
    QSqlQuery query;
    query.exec("SELECT store.pID, pdate, store.barcode, dname, lavenum\
               FROM store, purchase, device\
               WHERE store.pID=purchase.pID and store.barcode=device.barcode");

    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        QString code = query.value(2).toString();
        QString name = query.value(3).toString();
        unsigned n = QString(query.value(4).toString()).toInt();

        Store s(id, date, code, name, n);
        result.push_back(s);
    }
    query.finish();
    return true;
    return true;
}

unsigned Store::searchStoreByBarCode(const QString &code, QList<Store> &list)
{
    QSqlQuery query;
    query.exec("SELECT pID, barcode, lavenum\
               FROM store\
               WHERE barcode=?");
    QVariant vCode = code;
    query.addBindValue(vCode);

    unsigned count = 0;
    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString code = query.value(1).toString();
        unsigned num = QString(query.value(2).toString()).toInt();
        count += num;
        Store s(id, code, num);
        list.push_back(s);
    }
    query.finish();
    return count;
}

bool Store::modifyStoreByList(const QList<Store> &list)
{
    QSqlQuery query;
    query.prepare("UPDATE store\
                   SET lavenum=?\
                   WHERE pID=? and barcode=?");
    QVariantList nums;
    QVariantList ids;
    QVariantList codes;
    for(const auto &s : list)
    {
        nums << s.num;
        ids << s.pID;
        codes << s.barcode;
    }
    query.addBindValue(nums);
    query.addBindValue(ids);
    query.addBindValue(codes);

    if(!query.execBatch())
    {
        return false;
    }

    query.finish();
    return true;
}
