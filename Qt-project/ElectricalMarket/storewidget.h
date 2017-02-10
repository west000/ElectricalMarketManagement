#ifndef STOREWIDGET_H
#define STOREWIDGET_H

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
#include <QList>

#include "utility.h"
#include "store.h"

class StoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StoreWidget(QWidget *parent = 0);
    void InitStoreWidget();

signals:

public slots:
    void searchByPID();
    void searchByPDate();
    void searchByBarCode();
    void searchByDname();
    void searchAll();
    void clearStoreInput();
    void showResultOnTable(const QList<Store> &result);

public:
    QWidget *storeWidget;
    // 输入框
    QLineEdit *purchaseIDEdit;
    QLineEdit *dnameEdit;
    QLineEdit *barcodeEdit;
    QDateEdit *purchaseBeginDate;
    // 表格
    QTableWidget *storeTable;
};

#endif // STOREWIDGET_H
