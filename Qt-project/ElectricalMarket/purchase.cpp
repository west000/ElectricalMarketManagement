#include "purchase.h"
#include "utility.h"

Purchase::Purchase()
{

}

Purchase::Purchase(unsigned id, const QString &name, const QString &date, float a):
    pID(id), sName(name), pDate(date), amount(a)
{}

Purchase::Purchase(unsigned id, const QString &code, unsigned n, float price):
    pID(id), barcode(code), num(n), amount(price)
{}

Purchase::Purchase(unsigned id, const QString &date, const QString &supplier,
         const QString &code, const QString &dname, float price, unsigned n):
    pID(id), pDate(date), sName(supplier), barcode(code), dname(dname), num(n), amount(price)
{}

bool Purchase::insertNewPurchaseToDB(int id, const QString &date, const QString &supplier, float amount)
{
    QSqlQuery query;
    query.prepare("INSERT INTO purchase(pID, sname, pdate, amount) VALUES (?, ?, ?, ?)");
    QVariant vid = id;
    QVariant vsname = supplier;
    QVariant vdate = date;
    QVariant vamount = amount;
    query.addBindValue(vid);
    query.addBindValue(vsname);
    query.addBindValue(vdate);
    query.addBindValue(vamount);

    if(!query.exec())
        return false;

    query.finish();
    return true;
}

bool Purchase::insertPurchaseDetailListToDB(const QList<Purchase> &pdList)
{
    QSqlQuery query;
    query.prepare("INSERT INTO purchasedetail(pID, barcode, num, price) VALUES (?, ?, ?, ?)");
    QVariantList ids;
    QVariantList codes;
    QVariantList nums;
    QVariantList prices;
    for(const auto &pd : pdList)
    {
        ids << pd.pID;
        codes << pd.barcode;
        nums << pd.num;
        prices << pd.amount;
    }
    query.addBindValue(ids);
    query.addBindValue(codes);
    query.addBindValue(nums);
    query.addBindValue(prices);

    if(!query.execBatch())
    {
        return false;
    }

    query.finish();
    return true;
}

bool Purchase::searchPurchaseAll(QList<Purchase> &result)
{
    QSqlQuery query;
    query.exec("SELECT pID, sname, pdate, amount FROM purchase");

    while(query.next())
    {
        unsigned id = QString(query.value(0).toString()).toInt();
        QString name = query.value(1).toString();
        QString date = query.value(2).toString();
        float amount = QString(query.value(3).toString()).toDouble();
        Purchase p(id, name, date, amount);
        result.push_back(p);
    }
    query.finish();
    return true;
}

bool Purchase::searchPurDetAll(QList<Purchase> &result)
{
    QSqlQuery query;
    query.prepare("SELECT purchase.pID, device.barcode, device.dname, num, price, sname, pdate\
                  FROM purchasedetail, purchase, device\
                  WHERE purchase.pID=purchasedetail.pID and purchasedetail.barcode=device.barcode");
    query.exec();
    while(query.next())
    {
        unsigned id = QString(query.value(0).toString()).toInt();
        QString barcode = query.value(1).toString();
        QString dname = query.value(2).toString();
        unsigned num = QString(query.value(3).toString()).toInt();
        float price = QString(query.value(4).toString()).toDouble();
        QString supplier = query.value(5).toString();
        QString date = query.value(6).toString();

        Purchase pd(id, date, supplier, barcode, dname, price, num);
        result.push_back(pd);
    }
    query.finish();
    return true;
}

bool Purchase::searchPurDetByID(unsigned id, QList<Purchase> &result)
{
    QSqlQuery query;
    query.prepare("SELECT purchase.pID, device.barcode, device.dname, num, price, sname, pdate\
                  FROM purchasedetail, purchase, device\
                  WHERE purchase.pID=purchasedetail.pID and purchasedetail.barcode=device.barcode and purchase.pID=?");
    QVariant vID = QString::number(id);
    query.addBindValue(vID);

    query.exec();
    while(query.next())
    {
        unsigned id = QString(query.value(0).toString()).toInt();
        QString barcode = query.value(1).toString();
        QString dname = query.value(2).toString();
        unsigned num = QString(query.value(3).toString()).toInt();
        float price = QString(query.value(4).toString()).toDouble();
        QString supplier = query.value(5).toString();
        QString date = query.value(6).toString();

        Purchase pd(id, date, supplier, barcode, dname, price, num);
        result.push_back(pd);
    }
    query.finish();
    return true;
}

bool Purchase::searchPurDetByDate(const QString &date, QList<Purchase> &result)
{
    QSqlQuery query;
    query.prepare("SELECT purchase.pID, device.barcode, device.dname, num, price, sname, pdate\
                   FROM purchasedetail, purchase, device\
                   WHERE purchase.pID=purchasedetail.pID and purchasedetail.barcode=device.barcode and pdate=?");
    QVariant vdate = date;
    query.addBindValue(vdate);

    query.exec();
    while(query.next())
    {
        unsigned id = QString(query.value(0).toString()).toInt();
        QString barcode = query.value(1).toString();
        QString dname = query.value(2).toString();
        unsigned num = QString(query.value(3).toString()).toInt();
        float price = QString(query.value(4).toString()).toDouble();
        QString supplier = query.value(5).toString();
        QString date = query.value(6).toString();

        Purchase pd(id, date, supplier, barcode, dname, price, num);
        result.push_back(pd);
    }
    query.finish();
    return true;
}


unsigned Purchase::countPurchase()
{
    QSqlQuery query;
    query.exec("SELECT count(*) FROM purchase");
    unsigned count = 0;
    if(query.next())
    {
        count = QString(query.value(0).toString()).toInt();
    }
    return count;
}
