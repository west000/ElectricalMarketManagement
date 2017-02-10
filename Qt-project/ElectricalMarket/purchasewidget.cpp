#include "purchasewidget.h"
#include "supplier.h"
#include "device.h"

PurchaseWidget::PurchaseWidget(QWidget *parent) : QWidget(parent)
{
    InitPurchaseWidget();
}

void PurchaseWidget::InitPurchaseWidget()
{
    purchaseWidget = new QWidget();
    InitAddPurchaseWidget();
    InitSearchPurchaseWidget();

    QTabWidget *tabWidget = new QTabWidget(purchaseWidget);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->setTabShape(QTabWidget::Rounded);

    tabWidget->addTab(addPurchaseInfoWidget, QIcon(), QString::fromLocal8Bit("新增进货单"));
    tabWidget->addTab(searchPurchaseWidget, QIcon(), QString::fromLocal8Bit("查询进货单"));

    QHBoxLayout *hLayout = new QHBoxLayout(purchaseWidget);
    hLayout->addWidget(tabWidget);
    purchaseWidget->setLayout(hLayout);
}

void PurchaseWidget::InitAddPurchaseWidget()
{
    addPurchaseInfoWidget = new QWidget();

    // 标签
    // 新增进货单的页面
    QLabel *purchaseLabel = new QLabel(QString::fromLocal8Bit("进货单信息"));
    purchaseLabel->setFixedHeight(30);
    QLabel *deviceLabel = new QLabel(QString::fromLocal8Bit("货物信息"));
    deviceLabel->setFixedHeight(30);
    QLabel *tableLabel = new QLabel(QString::fromLocal8Bit("本次进货详细表单"));
    tableLabel->setFixedHeight(30);
    QLabel *pDateLabel = new QLabel(QString::fromLocal8Bit("进货日期"));
    QLabel *barcodeLabel = new QLabel(QString::fromLocal8Bit("条形码"));
    QLabel *numLabel = new QLabel(QString::fromLocal8Bit("数量"));
    QLabel *priceLabel = new QLabel(QString::fromLocal8Bit("单价"));

    // 输入框
    aIDEdit = new QLineEdit(addPurchaseInfoWidget);
    aIDEdit->setFixedWidth(125);
    aIDEdit->setReadOnly(true);
    aSupplierEdit = new QLineEdit(addPurchaseInfoWidget);
    aSupplierEdit->setFixedWidth(125);
    aDateEdit = new QDateEdit(addPurchaseInfoWidget);
    aDateEdit->setFixedWidth(250);
    aBarCodeEdit = new QLineEdit(addPurchaseInfoWidget);
    aBarCodeEdit->setFixedWidth(250);
    aDeviceNum = new QLineEdit(addPurchaseInfoWidget);
    aDeviceNum->setFixedWidth(250);
    aDevicePrice = new QLineEdit(addPurchaseInfoWidget);
    aDevicePrice->setFixedWidth(250);
    // 表格
    addPurchaseTable = new QTableWidget(addPurchaseInfoWidget);
    addPurchaseTable->setColumnCount(3);
    QStringList tableHeader;
    tableHeader << QString::fromLocal8Bit("条形码")
                << QString::fromLocal8Bit("单价")
                << QString::fromLocal8Bit("数量");
    addPurchaseTable->setHorizontalHeaderLabels(tableHeader);
    addPurchaseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置不可编辑
    // 按钮
    QPushButton *pIDButton = new QPushButton(addPurchaseInfoWidget);
    pIDButton->setText(QString::fromLocal8Bit("进货批次编号"));
    pIDButton->setFixedWidth(125);
    QPushButton *supplierButton = new QPushButton(addPurchaseInfoWidget);
    supplierButton->setText(QString::fromLocal8Bit("供应商"));
    supplierButton->setFixedWidth(125);
    QPushButton *submitButton = new QPushButton(addPurchaseInfoWidget);
    submitButton->setText(QString::fromLocal8Bit("加入进货单"));
    submitButton->setFixedWidth(125);
    QPushButton *resetButton = new QPushButton(addPurchaseInfoWidget);
    resetButton->setText(QString::fromLocal8Bit("重置"));
    resetButton->setFixedWidth(125);
    QPushButton *finishButton = new QPushButton(addPurchaseInfoWidget);
    finishButton->setText(QString::fromLocal8Bit("完成订单"));
    finishButton->setFixedWidth(125);

    // 布局
    // 进货表信息布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(pIDButton, 1, Qt::AlignLeft);
    hLayout1->addWidget(aIDEdit, 2, Qt::AlignLeft);
    hLayout1->addWidget(supplierButton, 1, Qt::AlignRight);
    hLayout1->addWidget(aSupplierEdit, 2, Qt::AlignRight);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(pDateLabel, 1, Qt::AlignLeft);
    hLayout2->addWidget(aDateEdit, 2, Qt::AlignLeft);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(purchaseLabel);
    vLayout1->addLayout(hLayout1);
    vLayout1->addLayout(hLayout2);

    // 货物信息布局
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(barcodeLabel, 1, Qt::AlignLeft);
    hLayout3->addWidget(aBarCodeEdit, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout4 = new QHBoxLayout;
    hLayout4->addWidget(numLabel, 1, Qt::AlignLeft);
    hLayout4->addWidget(aDeviceNum, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout5 = new QHBoxLayout;
    hLayout5->addWidget(priceLabel, 1, Qt::AlignLeft);
    hLayout5->addWidget(aDevicePrice, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout6 = new QHBoxLayout;
    hLayout6->addWidget(submitButton, 1, Qt::AlignRight);
    hLayout6->addWidget(resetButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(deviceLabel);
    vLayout2->addLayout(hLayout3);
    vLayout2->addLayout(hLayout4);
    vLayout2->addLayout(hLayout5);
    vLayout2->addLayout(hLayout6);

    // 货物表布局
    QHBoxLayout *hLayout7 = new QHBoxLayout;
    hLayout7->addWidget(tableLabel, 1, Qt::AlignLeft);
    hLayout7->addWidget(finishButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout3 = new QVBoxLayout;
    vLayout3->addLayout(hLayout7);
    vLayout3->addWidget(addPurchaseTable);

    // 整体布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1);
    vLayout->addLayout(vLayout2);
    vLayout->addLayout(vLayout3);

    addPurchaseInfoWidget->setLayout(vLayout);

    // 信号槽
    connect(pIDButton, &QPushButton::clicked,
            this, &PurchaseWidget::setPID);
    connect(submitButton, &QPushButton::clicked,
            this, &PurchaseWidget::insertToPurchase);
    connect(resetButton, &QPushButton::clicked,
            this, &PurchaseWidget::clearDeviceInfo);
    connect(finishButton, &QPushButton::clicked,
            this, &PurchaseWidget::insertNewPurchase);
}

void PurchaseWidget::setPID()
{
    // 清空上一次的内容
    pList.clear();
    sList.clear();
    addPurchaseTable->clearContents();
    addPurchaseTable->setRowCount(0);
    // 生成新编号
    unsigned n = Purchase::countPurchase();
    ++n;
    aIDEdit->setText(QString::number(n));
}

void PurchaseWidget::insertToPurchase()
{
    QString idText = aIDEdit->text();
    if(idText.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加货物出错"),
                              QString::fromLocal8Bit("进货编号不能为空"), QMessageBox::Yes);
        return ;
    }


    QString code = aBarCodeEdit->text();
    if(code.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加货物出错"),
                              QString::fromLocal8Bit("条形码不能为空"), QMessageBox::Yes);
        return ;
    }

    if(!Device::searchByBarCode(code))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加货物出错"),
                              QString::fromLocal8Bit("条形码不存在，请重新确认"), QMessageBox::Yes);
        return ;
    }

    QString numText = aDeviceNum->text();
    if(numText.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加货物出错"),
                              QString::fromLocal8Bit("数量不能为空"), QMessageBox::Yes);
        return ;
    }

    QString priceText = aDevicePrice->text();
    if(priceText.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加货物出错"),
                              QString::fromLocal8Bit("单价不能为空"), QMessageBox::Yes);
        return ;
    }

    unsigned id = idText.toInt();
    unsigned num = numText.toInt();
    float price  = priceText.toDouble();
    Purchase pd(id, code, num, price);
    pList.push_back(pd);

    Store s(idText, code, num);
    sList.push_back(s);

    int index = addPurchaseTable->rowCount();
    addPurchaseTable->setRowCount(index + 1);
    addPurchaseTable->setItem(index, 0, new QTableWidgetItem(code));
    addPurchaseTable->setItem(index, 1, new QTableWidgetItem(priceText));
    addPurchaseTable->setItem(index, 2, new QTableWidgetItem(numText));
}

void PurchaseWidget::clearDeviceInfo()
{
    aBarCodeEdit->clear();
    aDeviceNum->clear();
    aDevicePrice->clear();
}

void PurchaseWidget::insertNewPurchase()
{
    QString idText = aIDEdit->text();
    if(idText.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加进货单出错"),
                              QString::fromLocal8Bit("进货编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QString supplier = aSupplierEdit->text();
    if(supplier.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加进货单出错"),
                              QString::fromLocal8Bit("供应商名称不能为空"), QMessageBox::Yes);
        return ;
    }

    if(!Supplier::searchByName(supplier))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加进货单出错"),
                              QString::fromLocal8Bit("供应商不存在"), QMessageBox::Yes);
        return ;
    }

    QString date = aDateEdit->text();

    float totalAmount = 0;
    for(const auto &pd : pList)
    {
        totalAmount += pd.amount * pd.num;
    }
    unsigned id = idText.toInt();
    // 插入到Purchase表中
    if(!Purchase::insertNewPurchaseToDB(id, date, supplier, totalAmount))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加进货单出错"),
                              QString::fromLocal8Bit("进货单已经提交，请勿重复提交"), QMessageBox::Yes);
        return ;
    }
    Purchase::insertPurchaseDetailListToDB(pList);
    // 插入到Store表中
    if(!Store::insertToStore(sList))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("添加库存出错"),
                              QString::fromLocal8Bit("数据库连接失败"), QMessageBox::Yes);
        return ;
    }

    // 清空数据
    aBarCodeEdit->clear();
    aDeviceNum->clear();
    aDevicePrice->clear();
    addPurchaseTable->clearContents();
    aSupplierEdit->clear();
}


void PurchaseWidget::InitSearchPurchaseWidget()
{
    searchPurchaseWidget = new QWidget();

    // 标签
    QLabel *purchaseTableLabel = new QLabel(QString::fromLocal8Bit("进货批次表"));
    purchaseTableLabel->setFixedHeight(40);
    QLabel *purchaseDetialTableLabel = new QLabel(QString::fromLocal8Bit("进货详细表"));
    purchaseDetialTableLabel->setFixedHeight(40);
    QLabel *pDateLabel = new QLabel(QString::fromLocal8Bit("进货日期"));
    QLabel *pIDLabel = new QLabel(QString::fromLocal8Bit("进货单编号"));
    // 输入框
    sDateEdit = new QDateEdit(searchPurchaseWidget);
    sDateEdit->setFixedWidth(250);
    sIDEdit = new QLineEdit(searchPurchaseWidget);
    sIDEdit->setFixedWidth(250);
    // 表格
    searchPurchaseTable = new QTableWidget(searchPurchaseWidget);
    searchPurchaseTable->setColumnCount(4);
    QStringList ptHeader;
    ptHeader << QString::fromLocal8Bit("进货批次编号")
             << QString::fromLocal8Bit("进货日期")
             << QString::fromLocal8Bit("供应商")
             << QString::fromLocal8Bit("总价");
    searchPurchaseTable->setHorizontalHeaderLabels(ptHeader);
    searchPurchaseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置不可编辑

    searchPurchaseDetailTable = new QTableWidget(searchPurchaseWidget);
    searchPurchaseDetailTable->setColumnCount(7);
    QStringList pdtHeader;
    pdtHeader << QString::fromLocal8Bit("进货批次编号")
              << QString::fromLocal8Bit("进货时间")
              << QString::fromLocal8Bit("供应商")
              << QString::fromLocal8Bit("商品条形码")
              << QString::fromLocal8Bit("商品名称")
              << QString::fromLocal8Bit("进货数量")
              << QString::fromLocal8Bit("进货单价");
    searchPurchaseDetailTable->setHorizontalHeaderLabels(pdtHeader);
    searchPurchaseDetailTable->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置不可编辑
    // 按钮
    QPushButton *searchAllPurButton = new QPushButton(searchPurchaseWidget);
    searchAllPurButton->setText(QString::fromLocal8Bit("查询所有进货单"));
    searchAllPurButton->setFixedWidth(125);
    QPushButton *searchAllPurDetButton = new QPushButton(searchPurchaseWidget);
    searchAllPurDetButton->setText(QString::fromLocal8Bit("查询所有进货详细单"));
    searchAllPurDetButton->setFixedWidth(125);
    QPushButton *searchByDateButton = new QPushButton(searchPurchaseWidget);
    searchByDateButton->setText(QString::fromLocal8Bit("按进货日期查询"));
    searchByDateButton->setFixedWidth(125);
    QPushButton *searchByIDButton = new QPushButton(searchPurchaseWidget);
    searchByIDButton->setText(QString::fromLocal8Bit("按进货单编号查询"));
    searchByIDButton->setFixedWidth(125);
    // 布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(purchaseTableLabel, 1, Qt::AlignLeft);
    hLayout1->addWidget(searchAllPurButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(searchPurchaseTable);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(pDateLabel, 1, Qt::AlignLeft);
    hLayout2->addWidget(sDateEdit, 2, Qt::AlignLeft);
    hLayout2->addWidget(searchByDateButton, 3, Qt::AlignRight);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(pIDLabel, 1, Qt::AlignLeft);
    hLayout3->addWidget(sIDEdit, 2, Qt::AlignLeft);
    hLayout3->addWidget(searchByIDButton, 3, Qt::AlignRight);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(purchaseDetialTableLabel);
    vLayout2->addLayout(hLayout2);
    vLayout2->addLayout(hLayout3);
    vLayout2->addWidget(searchAllPurDetButton, 1, Qt::AlignRight);
    vLayout2->addWidget(searchPurchaseDetailTable);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1);
    vLayout->addLayout(vLayout2);

    searchPurchaseWidget->setLayout(vLayout);

    // 信号槽
    connect(searchAllPurButton, &QPushButton::clicked,
            this, &PurchaseWidget::searchPurAll);
    connect(searchAllPurDetButton, &QPushButton::clicked,
            this, &PurchaseWidget::searchPurDetAll);
    connect(searchByIDButton, &QPushButton::clicked,
            this, &PurchaseWidget::searchPDByID);
    connect(searchByDateButton, &QPushButton::clicked,
            this, &PurchaseWidget::searchPDByDate);
}

void PurchaseWidget::searchPurAll()
{
    searchPurchaseTable->clearContents();
    QList<Purchase> result;
    if(!Purchase::searchPurchaseAll(result))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }

    int index = 0;
    for(const auto &p : result)
    {
        if(searchPurchaseTable->rowCount() <= index)
        {
            searchPurchaseTable->setRowCount(index + 5);
        }
        searchPurchaseTable->setItem(index, 0, new QTableWidgetItem(QString::number(p.pID)));
        searchPurchaseTable->setItem(index, 1, new QTableWidgetItem(p.pDate));
        searchPurchaseTable->setItem(index, 2, new QTableWidgetItem(p.sName));
        searchPurchaseTable->setItem(index, 3, new QTableWidgetItem(QString::number(p.amount)));
        ++index;
    }
}

void PurchaseWidget::showInThePurDetTable(const QList<Purchase> &list)
{
    if(searchPurchaseDetailTable != nullptr)
    {
        int index = 0;
        for(const auto &pd : list)
        {
            if(searchPurchaseDetailTable->rowCount() <= index)
            {
                searchPurchaseDetailTable->setRowCount(index + 5);
            }
            searchPurchaseDetailTable->setItem(index, 0, new QTableWidgetItem(QString::number(pd.pID)));
            searchPurchaseDetailTable->setItem(index, 1, new QTableWidgetItem(pd.pDate));
            searchPurchaseDetailTable->setItem(index, 2, new QTableWidgetItem(pd.sName));
            searchPurchaseDetailTable->setItem(index, 3, new QTableWidgetItem(pd.barcode));
            searchPurchaseDetailTable->setItem(index, 4, new QTableWidgetItem(pd.dname));
            searchPurchaseDetailTable->setItem(index, 5, new QTableWidgetItem(QString::number(pd.num)));
            searchPurchaseDetailTable->setItem(index, 6, new QTableWidgetItem(QString::number(pd.amount)));
            ++index;
        }
    }
}

void PurchaseWidget::searchPurDetAll()
{
    searchPurchaseDetailTable->clearContents();
    QList<Purchase> result;
    if(!Purchase::searchPurDetAll(result))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }
    showInThePurDetTable(result);
}

void PurchaseWidget::searchPDByDate()
{
    searchPurchaseDetailTable->clearContents();
    QList<Purchase> result;
    QString date = sDateEdit->text();
    if(!Purchase::searchPurDetByDate(date, result))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }
    showInThePurDetTable(result);
}

void PurchaseWidget::searchPDByID()
{
    searchPurchaseDetailTable->clearContents();
    QString idText = sIDEdit->text();
    if(idText.isEmpty())
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("进货编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QList<Purchase> result;
    unsigned id = idText.toInt();
    if(!Purchase::searchPurDetByID(id, result))
    {
        QMessageBox::critical(addPurchaseInfoWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }
    showInThePurDetTable(result);
}
