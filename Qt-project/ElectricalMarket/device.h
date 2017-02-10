#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QString>
#include <QList>

class DeviceWidget;

class Device
{
    friend class DeviceWidget;
public:
    Device(const QString &name, const QString &prod, const QString &code, const QString &date) :
        dname(name), productor(prod), barcode(code), makedate(date)
    {}

    static bool insertNewDeviceToDB(const QString &name, const QString &prod, const QString &code, const QString &date);
    static bool searchAll(QList<Device> &result);
    static bool searchByBarCode(const QString &code);
private:
    QString dname;
    QString productor;
    QString barcode;
    QString makedate;
};

#endif // DEVICE_H
