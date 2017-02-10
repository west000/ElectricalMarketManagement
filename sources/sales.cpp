#include "sales.h"

Sales::Sales()
{

}

bool Sales::insertSaleToDB(const QString &id, const QString &date, const QString &cust, const QString &tele, float amount)
{
    QSqlQuery query;
    query.prepare("INSERT INTO sales(saleID, saleDate, amount, customer, ctelenum) VALUES(?, ?, ?, ?, ?)");
    QVariant vID = id;
    QVariant vDate = date;
    QVariant vAmount = amount;
    QVariant vCust = cust;
    QVariant vTele = tele;

    query.addBindValue(vID);
    query.addBindValue(vDate);
    query.addBindValue(vAmount);
    query.addBindValue(vCust);
    query.addBindValue(vTele);

    if(!query.exec())
        return false;

    query.finish();
    return true;
}

bool Sales::insertSaleDetailToDB(const QList<SaleItem> &list)
{
    QSqlQuery query;
    query.prepare("INSERT INTO salesdetail(saleID, barcode, salenum, saleprice) VALUES(?, ?, ?, ?)");
    QVariantList ids;
    QVariantList codes;
    QVariantList nums;
    QVariantList prices;
    for(const auto &s : list)
    {
        ids << s.saleID;
        codes << s.barcode;
        nums << s.num;
        prices << s.price;
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


bool Sales::searchSaleAll(QList<Sales> &result)
{
    QSqlQuery query;
    query.exec("SELECT saleID, saledate, amount, customer, ctelenum FROM sales");

    qDebug() << "begin";
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        float amount = QString(query.value(2).toString()).toDouble();
        qDebug() << id << date << amount;
        QString cust = query.value(3).toString();
        QString tele = query.value(4).toString();
        Sales s(id, date, cust, tele, amount);
        result.push_back(s);
    }
    qDebug() << "end";

    query.finish();
    return true;
}

bool Sales::searchSaleByDate(const QString &date, QList<Sales> &result)
{
    QSqlQuery query;
    query.prepare("SELECT saleID, saledate, amount, customer, ctelenum\
                   FROM sales\
                   WHERE saledate=?");
    QVariant vDate = date;
    query.addBindValue(vDate);

    query.exec();
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString date = query.value(1).toString();
        float amount = QString(query.value(2).toString()).toDouble();
        QString cust = query.value(3).toString();
        QString tele = query.value(4).toString();
        Sales s(id, date, cust, tele,amount);
        result.push_back(s);
    }
    query.finish();
    return true;
}

bool Sales::searchSaleDetByID(const QString &id, QList<SaleItem> &result)
{
    QSqlQuery query;
    query.prepare("SELECT saleID, barcode, salenum, saleprice\
                   FROM salesdetail\
                   WHERE saleID=?");
    QVariant vID = id;
    query.addBindValue(vID);

    query.exec();
    while(query.next())
    {
        //SaleItem(const QString &id, const QString &code, unsigned n, float p)
        QString id = query.value(0).toString();
        QString code = query.value(1).toString();
        unsigned n = QString(query.value(2).toString()).toInt();
        float price = QString(query.value(3).toString()).toDouble();

        SaleItem item(id, code, n, price);
        result.push_back(item);
    }
    query.finish();
    return true;
}


unsigned Sales::countSales()
{
    QSqlQuery query;
    query.exec("SELECT count(*) FROM sales");
    unsigned count = 0;
    if(query.next())
    {
        count = QString(query.value(0).toString()).toInt();
    }
    return count;
}
