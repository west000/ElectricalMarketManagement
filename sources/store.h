#ifndef STORE_H
#define STORE_H

#include <QList>
#include <QString>


class StoreWidget;
class PurchaseWidget;

class Store
{
    friend class StoreWidget;
    friend class PurchaseWidget;
public:
    Store();
    Store(const QString &id, const QString &date, const QString &code, const QString &name, unsigned n):
        pID(id), pDate(date), barcode(code), dname(name), num(n)
    {}

    Store(const QString &id, const QString &code, unsigned n):
        pID(id), barcode(code), num(n)
    {}


    static bool insertToStore(QList<Store> &list);
    static bool modifyStoreByCodeAndID(const QString &code, const QString &id, unsigned num);

    static bool searchByPID(const QString &id, QList<Store> &result);
    static bool searchByPDate(const QString &date, QList<Store> &result);
    static bool searchByBarCode(const QString &code, QList<Store> &result);
    static bool searchByDname(const QString &name, QList<Store> &result);
    static bool searchAll(QList<Store> &result);

    static unsigned searchStoreByBarCode(const QString &code, QList<Store> &list);
    static bool modifyStoreByList(const QList<Store> &list);

public:
    QString pID;
    QString pDate;
    QString barcode;
    QString dname;
    unsigned num;
};

#endif // STORE_H
