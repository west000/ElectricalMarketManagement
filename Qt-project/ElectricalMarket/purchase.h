#ifndef PURCHASE_H
#define PURCHASE_H

#include <QString>
#include <QList>

class PurchaseWidget;

class Purchase
{
    friend class PurchaseWidget;
public:
    Purchase();
    Purchase(unsigned id, const QString &name, const QString &date, float a);
    Purchase(unsigned id, const QString &code, unsigned n, float price);
    Purchase(unsigned id, const QString &date, const QString &supplier,
             const QString &code, const QString &dname, float price, unsigned num);


    static bool insertNewPurchaseToDB(int id, const QString &date, const QString &supplier, float amount);
    static bool insertPurchaseDetailListToDB(const QList<Purchase> &pdList);

    static bool searchPurchaseAll(QList<Purchase> &result);
    static bool searchPurDetAll(QList<Purchase> &result);
    static bool searchPurDetByID(unsigned id, QList<Purchase> &result);
    static bool searchPurDetByDate(const QString &date, QList<Purchase> &result);

    static unsigned countPurchase();

private:
    QString pDate;
    QString sName;      // 供应商名称
    QString barcode;
    QString dname;      // 商品名称
    unsigned pID;
    unsigned num;
    float amount;       // 既可以表示一件商品的单价，也可以表示一张表单的总额
};

#endif // PURCHASE_H
