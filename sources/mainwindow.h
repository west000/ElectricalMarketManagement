#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

#include "devicewidget.h"
#include "supplierwidget.h"
#include "storewidget.h"
#include "purchasewidget.h"
#include "saleswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void InitDeviceInfoWidget();
    void InitSupplierWidget();
    void InitSalesWidget();
    void InitPurchaseWidget();
    void InitStoreWidget();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;

    DeviceWidget *devicePage;
    SupplierWidget *supplierPage;
    PurchaseWidget *purchasePage;
    SalesWidget *salesPage;
    StoreWidget *storePage;
};

#endif // MAINWINDOW_H
