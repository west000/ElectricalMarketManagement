#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QDebug>
#include <QDateEdit>
#include <QTableWidget>
#include <QMessageBox>

#include "utility.h"
#include "device.h"

class DeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceWidget(QWidget *parent = 0);
    void InitDeviceInfoWidget();
    void InitDeviceTable();

signals:

public slots:
    void getNewDeviceInfo();
    void clearDeviceInfoInput();

public:
    QWidget *deviceInfoWidget;
    // 输入框
    QLineEdit *barCodeEdit;
    QLineEdit *dnameEdit;
    QLineEdit *productEdit;
    QDateEdit *makedateEdit;
    // 表格
    QTableWidget *deviceInfoTable;
};

#endif // DEVICEWIDGET_H
