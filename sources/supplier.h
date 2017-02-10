#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>
#include <QList>

class SupplierWidget;
class Supplier
{
    friend class SupplierWidget;
public:
    Supplier();
    Supplier(const QString &name, const QString &addr, const QString &tele):
        sname(name), saddr(addr), telenum(tele)
    {}

    static bool insertNewSupplierToDB(const QString &name, const QString &addr, const QString &tele);

    static bool searchAll(QList<Supplier> &result);
    static bool searchByName(const QString &name);

private:
    QString sname;
    QString saddr;
    QString telenum;
};

#endif // SUPPLIER_H
