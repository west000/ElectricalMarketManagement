#ifndef SALES_H
#define SALES_H

#include <QString>
#include <QList>
#include "utility.h"

class SaleItem
{
public:
    SaleItem()
    {}

    SaleItem(const QString &id, const QString &code, unsigned n, float p):
        saleID(id), barcode(code), num(n), price(p)
    {}

    QString saleID;
    QString barcode;
    unsigned num;
    float price;
};


class SalesWidget;
class Sales
{
    friend class SalesWidget;
public:
    Sales();

    Sales(const QString &id, const QString &date, const QString &cust, const QString &tele, float a):
        id(id), date(date), customer(cust), custTele(tele), amount(a)
    {}

    static bool insertSaleToDB(const QString &id, const QString &date, const QString &cust, const QString &tele, float amount);
    static bool insertSaleDetailToDB(const QList<SaleItem> &list);

    static bool searchSaleAll(QList<Sales> &result);
    static bool searchSaleByDate(const QString &date, QList<Sales> &result);
    static bool searchSaleDetByID(const QString &id, QList<SaleItem> &result);

    static unsigned countSales();

private:
    QString id;
    QString date;
    QString customer;
    QString custTele;
    float amount;
};

#endif // SALES_H
