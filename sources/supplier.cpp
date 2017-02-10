#include "supplier.h"
#include "utility.h"

Supplier::Supplier()
{

}

bool Supplier::insertNewSupplierToDB(const QString &name, const QString &addr, const QString &tele)
{
    QSqlQuery query;
    query.prepare("INSERT INTO supplier(sname, saddr, telenum) VALUES (?, ?, ?)");
    QVariant vname = name;
    QVariant vaddr = addr;
    QVariant vtele = tele;
    query.addBindValue(vname);
    query.addBindValue(vaddr);
    query.addBindValue(vtele);

    if(!query.exec())
        return false;

    query.finish();
    return true;
}

bool Supplier::searchAll(QList<Supplier> &result)
{
    QSqlQuery query;
    query.exec("SELECT sname, saddr, telenum FROM supplier");

    while(query.next())
    {
        QString name = query.value(0).toString();
        QString addr = query.value(1).toString();
        QString tele = query.value(2).toString();
        Supplier s(name, addr, tele);
        result.push_back(s);
    }
    return true;
}

bool Supplier::searchByName(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM supplier WHERE sname=?");
    QVariant vName = name;
    query.addBindValue(vName);
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
