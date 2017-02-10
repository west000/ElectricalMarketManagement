#ifndef SALESWIDGET_H
#define SALESWIDGET_H

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
#include "sales.h"

class SalesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SalesWidget(QWidget *parent = 0);
    void InitSalesWidget();
    void InitAddSalesWidget();
    void InitSearchSalesWidget();

signals:

public slots:
    void searchSalesAll();
    void searchSalesByDate();
    void searchSaleDetailByID();

    void setID();
    void insertToSales();
    void clearSalesDetail();
    void insertSalesToDB();

    void showInSearchSaleTable(const QList<Sales> &list);
    void showInSearchSaleDetTable(const QList<SaleItem> &list);
    void showInAddSaleDetTable(const QList<SaleItem> &list);

public:
    QWidget *salesWidget;
    // 两个页面
    QWidget *addSalesWidget;
    QWidget *searchSalesWidget;
    // 输入框
    // 新增销售单的页面
    QLineEdit *aIDEdit;
    QDateEdit *aDateEdit;
    QLineEdit *custEdit;
    QLineEdit *custTeleEdit;
    QLineEdit *amountEdit;
    QLineEdit *barCodeEdit;
    QLineEdit *numEdit;
    QLineEdit *priceEdit;
    // 查询销售单的页面
    QLineEdit *sIDEdit;
    QDateEdit *sDateEdit;
    // 表格
    QTableWidget *aSalesTable;
    QTableWidget *sSalesTable;
    QTableWidget *sSalesDetailTable;

    QList<SaleItem> sList;
};

#endif // SALESWIDGET_H
