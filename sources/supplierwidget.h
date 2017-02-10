#ifndef SUPPLIERWIDGET_H
#define SUPPLIERWIDGET_H

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
#include "supplier.h"

class SupplierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SupplierWidget(QWidget *parent = 0);
    void InitSupplierWidget();
    void InitSupplierTable();

signals:

public slots:
    void getSupplierInfo();
    void clearSupplierInfoInput();

public:
    QWidget *supplierWidget;
    // 输入框
    QLineEdit *snameEdit;
    QLineEdit *saddrEdit;
    QLineEdit *teleEdit;
    // 表格
    QTableWidget *supplierTable;
};

#endif // SUPPLIERWIDGET_H
