#ifndef PURCHASEWIDGET_H
#define PURCHASEWIDGET_H

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
#include "purchase.h"
#include "store.h"

class PurchaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PurchaseWidget(QWidget *parent = 0);
    void InitPurchaseWidget();
    void InitAddPurchaseWidget();
    void InitSearchPurchaseWidget();
signals:

public slots:
    void searchPurAll();
    void searchPurDetAll();
    void searchPDByDate();
    void searchPDByID();

    void setPID();
    void insertToPurchase();
    void clearDeviceInfo();
    void insertNewPurchase();

    void showInThePurDetTable(const QList<Purchase> &list);

public:
    QWidget *purchaseWidget;
    // 两个页面
    QWidget *addPurchaseInfoWidget;
    QWidget *searchPurchaseWidget;
    // 输入框
    // 新增进货单的页面
    QLineEdit *aIDEdit;
    QLineEdit *aSupplierEdit;
    QDateEdit *aDateEdit;
    QLineEdit *aBarCodeEdit;
    QLineEdit *aDeviceNum;
    QLineEdit *aDevicePrice;
    // 查询进货单的页面
    QDateEdit *sDateEdit;
    QLineEdit *sIDEdit;
    // 表格
    QTableWidget *addPurchaseTable;
    QTableWidget *searchPurchaseTable;
    QTableWidget *searchPurchaseDetailTable;
    // 进货单详细内容
    QList<Purchase> pList;
    QList<Store> sList;
};

#endif // PURCHASEWIDGET_H
