#include "saleswidget.h"
#include "store.h"

SalesWidget::SalesWidget(QWidget *parent) : QWidget(parent)
{
    InitSalesWidget();
}

void SalesWidget::InitSalesWidget()
{
    salesWidget = new QWidget();
    InitAddSalesWidget();
    InitSearchSalesWidget();

    QTabWidget *tabWidget = new QTabWidget(salesWidget);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->setTabShape(QTabWidget::Rounded);

    tabWidget->addTab(addSalesWidget, QIcon(), QString::fromLocal8Bit("增加销售单"));
    tabWidget->addTab(searchSalesWidget, QIcon(), QString::fromLocal8Bit("查询销售表单"));

    QHBoxLayout *hLayout = new QHBoxLayout(salesWidget);
    hLayout->addWidget(tabWidget);
    salesWidget->setLayout(hLayout);
}

void SalesWidget::InitAddSalesWidget()
{
    addSalesWidget = new QWidget();
    // 标签
    QLabel *aSaleLabel = new QLabel(QString::fromLocal8Bit("销售单"));
    aSaleLabel->setFixedHeight(30);
    QLabel *deviceLabel = new QLabel(QString::fromLocal8Bit("商品信息"));
    deviceLabel->setFixedHeight(30);
    QLabel *tableLabel = new QLabel(QString::fromLocal8Bit("本次销售详细表单"));
    tableLabel->setFixedHeight(40);
    QLabel *dateLabel = new QLabel(QString::fromLocal8Bit("销售日期"));
    QLabel *amountLabel = new QLabel(QString::fromLocal8Bit("销售额"));
    QLabel *custLabel = new QLabel(QString::fromLocal8Bit("顾客姓名"));
    QLabel *teleLabel = new QLabel(QString::fromLocal8Bit("顾客联系电话"));
    QLabel *barCodeLabel = new QLabel(QString::fromLocal8Bit("条形码"));
    QLabel *numLabel = new QLabel(QString::fromLocal8Bit("数量"));
    QLabel *priceLabel = new QLabel(QString::fromLocal8Bit("单价"));

    // 输入框
    aIDEdit = new QLineEdit(addSalesWidget);
    aIDEdit->setReadOnly(true);
    aIDEdit->setFixedWidth(100);
    amountEdit = new QLineEdit(addSalesWidget);
    amountEdit->setReadOnly(true);
    amountEdit->setFixedWidth(250);
    aDateEdit =  new QDateEdit(addSalesWidget);
    aDateEdit->setFixedWidth(150);
    custEdit = new QLineEdit(addSalesWidget);
    custEdit->setFixedWidth(150);
    custTeleEdit = new QLineEdit(addSalesWidget);
    custTeleEdit->setFixedWidth(150);

    barCodeEdit = new QLineEdit(addSalesWidget);
    barCodeEdit->setFixedWidth(250);
    numEdit = new QLineEdit(addSalesWidget);
    numEdit->setFixedWidth(250);
    priceEdit= new QLineEdit(addSalesWidget);
    priceEdit->setFixedWidth(250);

    // 表格
    aSalesTable = new QTableWidget(addSalesWidget);
    aSalesTable->setColumnCount(3);
    QStringList tableHeader;
    tableHeader << QString::fromLocal8Bit("商品条形码")
                << QString::fromLocal8Bit("单价")
                << QString::fromLocal8Bit("数量");
    aSalesTable->setHorizontalHeaderLabels(tableHeader);
    aSalesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 按钮
    QPushButton *idButton = new QPushButton(addSalesWidget);
    idButton->setText(QString::fromLocal8Bit("销售单编号"));
    idButton->setFixedWidth(125);
    QPushButton *submitButton = new QPushButton(addSalesWidget);
    submitButton->setText(QString::fromLocal8Bit("加入销售单"));
    submitButton->setFixedWidth(125);
    QPushButton *resetButton = new QPushButton(addSalesWidget);
    resetButton->setText(QString::fromLocal8Bit("重置"));
    resetButton->setFixedWidth(125);
    QPushButton *finishButton = new QPushButton(addSalesWidget);
    finishButton->setText(QString::fromLocal8Bit("完成订单"));
    finishButton->setFixedWidth(125);
    // 布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(idButton, 1, Qt::AlignLeft);
    hLayout1->addWidget(aIDEdit, 2, Qt::AlignLeft);
    hLayout1->addWidget(dateLabel, 1, Qt::AlignRight);
    hLayout1->addWidget(aDateEdit, 2, Qt::AlignRight);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(custLabel, 1, Qt::AlignLeft);
    hLayout2->addWidget(custEdit, 3, Qt::AlignLeft);
    hLayout2->addWidget(teleLabel, 1, Qt::AlignRight);
    hLayout2->addWidget(custTeleEdit, 3, Qt::AlignRight);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(amountLabel, 1, Qt::AlignLeft);
    hLayout3->addWidget(amountEdit, 2, Qt::AlignLeft);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(aSaleLabel);
    vLayout1->addLayout(hLayout1);
    vLayout1->addLayout(hLayout2);
    vLayout1->addLayout(hLayout3);

    QHBoxLayout *hLayout4 = new QHBoxLayout;
    hLayout4->addWidget(barCodeLabel, 1, Qt::AlignLeft);
    hLayout4->addWidget(barCodeEdit, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout5 = new QHBoxLayout;
    hLayout5->addWidget(priceLabel, 1, Qt::AlignLeft);
    hLayout5->addWidget(priceEdit, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout6 = new QHBoxLayout;
    hLayout6->addWidget(numLabel, 1, Qt::AlignLeft);
    hLayout6->addWidget(numEdit, 2, Qt::AlignLeft);

    QHBoxLayout *hLayout7 = new QHBoxLayout;
    hLayout7->addWidget(submitButton, 1, Qt::AlignRight);
    hLayout7->addWidget(resetButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(deviceLabel);
    vLayout2->addLayout(hLayout4);
    vLayout2->addLayout(hLayout5);
    vLayout2->addLayout(hLayout6);
    vLayout2->addLayout(hLayout7);

    QHBoxLayout *hLayout8 = new QHBoxLayout;
    hLayout8->addWidget(tableLabel, 1 , Qt::AlignLeft);
    hLayout8->addWidget(finishButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout3 = new QVBoxLayout;
    vLayout3->addLayout(hLayout8);
    vLayout3->addWidget(aSalesTable);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1);
    vLayout->addLayout(vLayout2);
    vLayout->addLayout(vLayout3);

    addSalesWidget->setLayout(vLayout);

    // 信号槽
    connect(idButton, &QPushButton::clicked,
            this, &SalesWidget::setID);
    connect(submitButton, &QPushButton::clicked,
            this, &SalesWidget::insertToSales);
    connect(resetButton, &QPushButton::clicked,
            this, &SalesWidget::clearSalesDetail);
    connect(finishButton, &QPushButton::clicked,
            this, &SalesWidget::insertSalesToDB);
}

void SalesWidget::InitSearchSalesWidget()
{
    searchSalesWidget = new QWidget();
    // 标签
    QLabel *saleLabel = new QLabel(QString::fromLocal8Bit("销售单总览"));
    saleLabel->setFixedHeight(40);
    QLabel *saleDetLabel = new QLabel(QString::fromLocal8Bit("销售详细表"));
    saleDetLabel->setFixedHeight(40);
    QLabel *dateLabel = new QLabel(QString::fromLocal8Bit("销售日期"));
    QLabel *sIDLabel = new QLabel(QString::fromLocal8Bit("销售单编号"));
    // 输入框
    sIDEdit = new QLineEdit(searchSalesWidget);
    sIDEdit->setFixedWidth(250);
    sDateEdit = new QDateEdit(searchSalesWidget);
    sDateEdit->setFixedWidth(250);
    // 表格
    sSalesTable = new QTableWidget(searchSalesWidget);
    sSalesTable->setColumnCount(5);
    QStringList stHeader;
    stHeader << QString::fromLocal8Bit("销售单编号")
             << QString::fromLocal8Bit("销售日期")
             << QString::fromLocal8Bit("账单金额")
             << QString::fromLocal8Bit("顾客姓名")
             << QString::fromLocal8Bit("顾客联系方式");
    sSalesTable->setHorizontalHeaderLabels(stHeader);
    sSalesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    sSalesDetailTable = new QTableWidget(searchSalesWidget);
    sSalesDetailTable->setColumnCount(4);
    QStringList sdtHeader;
    sdtHeader << QString::fromLocal8Bit("销售单编号")
              << QString::fromLocal8Bit("商品条形码")
              << QString::fromLocal8Bit("数量")
              << QString::fromLocal8Bit("单价");
    sSalesDetailTable->setHorizontalHeaderLabels(sdtHeader);
    sSalesDetailTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 按钮
    QPushButton *sAllButton = new QPushButton(searchSalesWidget);
    sAllButton->setText(QString::fromLocal8Bit("查询所有销售单"));
    sAllButton->setFixedWidth(125);
    QPushButton *sByDateButton = new QPushButton(searchSalesWidget);
    sByDateButton->setText(QString::fromLocal8Bit("按日期查询"));
    sByDateButton->setFixedWidth(125);
    QPushButton *sByIDButton = new QPushButton(searchSalesWidget);
    sByIDButton->setText(QString::fromLocal8Bit("按销售单号查询"));
    sByIDButton->setFixedWidth(125);

    // 布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(dateLabel, 1, Qt::AlignLeft);
    hLayout1->addWidget(sDateEdit, 2, Qt::AlignLeft);
    hLayout1->addWidget(sByDateButton, 3, Qt::AlignRight);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(saleLabel);
    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(sAllButton, 1, Qt::AlignRight);
    vLayout1->addWidget(sSalesTable);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(sIDLabel, 1, Qt::AlignLeft);
    hLayout2->addWidget(sIDEdit, 2, Qt::AlignLeft);
    hLayout2->addWidget(sByIDButton, 3, Qt::AlignRight);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(saleDetLabel);
    vLayout2->addLayout(hLayout2);
    vLayout2->addWidget(sSalesDetailTable);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1);
    vLayout->addLayout(vLayout2);

    searchSalesWidget->setLayout(vLayout);

    // 信号槽
    connect(sAllButton, &QPushButton::clicked,
            this, &SalesWidget::searchSalesAll);
    connect(sByDateButton, &QPushButton::clicked,
            this, &SalesWidget::searchSalesByDate);
    connect(sByIDButton, &QPushButton::clicked,
            this, &SalesWidget::searchSaleDetailByID);
}

void SalesWidget::searchSalesAll()
{
    QList<Sales> result;
    if(!Sales::searchSaleAll(result))
    {
        QMessageBox::critical(searchSalesWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }

    showInSearchSaleTable(result);
}

void SalesWidget::searchSalesByDate()
{
    QString date = sDateEdit->text();
    QList<Sales> result;
    if(!Sales::searchSaleByDate(date, result))
    {
        QMessageBox::critical(searchSalesWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }

    showInSearchSaleTable(result);
}

void SalesWidget::searchSaleDetailByID()
{
    QString id = sIDEdit->text();
    if(id.isEmpty())
    {
        QMessageBox::critical(searchSalesWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("销售单编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QList<SaleItem> result;
    if(!Sales::searchSaleDetByID(id, result))
    {
        QMessageBox::critical(searchSalesWidget, QString::fromLocal8Bit("查询出错"),
                              QString::fromLocal8Bit("数据库连接错误"), QMessageBox::Yes);
        return ;
    }
    showInSearchSaleDetTable(result);
}

void SalesWidget::setID()
{
    // 清空上一次的内容
    custEdit->clear();
    custTeleEdit->clear();
    amountEdit->clear();
    barCodeEdit->clear();
    priceEdit->clear();
    numEdit->clear();

    aSalesTable->clearContents();
    aSalesTable->setRowCount(0);

    // 生成新的编号
    unsigned n = Sales::countSales();
    ++n;
    aIDEdit->setText(QString::number(n));
}

void SalesWidget::insertToSales()
{
    QString idText = aIDEdit->text();
    if(idText.isEmpty())
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加商品出错"),
                              QString::fromLocal8Bit("销售编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QString code = barCodeEdit->text();
    if(code.isEmpty())
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加商品出错"),
                              QString::fromLocal8Bit("条形码不能为空"), QMessageBox::Yes);
        return ;
    }

    QString priceText = priceEdit->text();
    if(priceText.isEmpty())
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加商品出错"),
                              QString::fromLocal8Bit("单价不能为空"), QMessageBox::Yes);
        return ;
    }

    QString numText = numEdit->text();
    if(numText.isEmpty())
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加商品出错"),
                              QString::fromLocal8Bit("数量不能为空"), QMessageBox::Yes);
        return ;
    }

    // 判断库存是否足够
    unsigned num = numText.toInt();
    QList<Store> storeList;
    if(Store::searchStoreByBarCode(code, storeList) < num)
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加商品出错"),
                              QString::fromLocal8Bit("库存不足"), QMessageBox::Yes);
        return ;
    }

    // 库存充足，修改库存
    unsigned needNum = num;
    for(auto &s : storeList)
    {
        if(s.num >= needNum)
        {
            s.num -= needNum;
            needNum = 0;
            break;
        }
        else
        {
            needNum -= s.num;
            s.num = 0;
        }
    }
    // 保存修改到Store表中
    if(!Store::modifyStoreByList(storeList))
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("修改库存出错"),
                              QString::fromLocal8Bit("数据库连接失败"), QMessageBox::Yes);
        return ;
    }

    // 库存修改成功，将销售单保存到数据库中
    float price = priceText.toDouble();
    SaleItem sItem(idText, code, num, price);
    sList.push_back(sItem);

    int index = aSalesTable->rowCount();
    aSalesTable->setRowCount(index + 1);
    aSalesTable->setItem(index, 0, new QTableWidgetItem(code));
    aSalesTable->setItem(index, 1, new QTableWidgetItem(priceText));
    aSalesTable->setItem(index, 2, new QTableWidgetItem(numText));
}

void SalesWidget::clearSalesDetail()
{
    barCodeEdit->clear();
    priceEdit->clear();
    numEdit->clear();
}

void SalesWidget::insertSalesToDB()
{
    QString idText = aIDEdit->text();
    if(idText.isEmpty())
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加销售单失败"),
                              QString::fromLocal8Bit("销售编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QString cust = custEdit->text();
    QString tele = custTeleEdit->text();
    QString date = aDateEdit->text();
    float totalAmount = 0;
    for(const auto &sItem : sList)
    {
        totalAmount += sItem.num * sItem.price;
    }
    // 插入到销售Sales表中
    if(!Sales::insertSaleToDB(idText, date, cust, tele, totalAmount))
    {
        QMessageBox::critical(addSalesWidget, QString::fromLocal8Bit("添加销售单失败"),
                              QString::fromLocal8Bit("销售已经提交，请勿重复提交"), QMessageBox::Yes);
        return ;
    }
    // 插入到销售详细表SalesDetail中
    Sales::insertSaleDetailToDB(sList);
    // 清空数据
    sList.clear();
    // 销售额
    amountEdit->setText(QString::number(totalAmount));
}

void SalesWidget::showInSearchSaleTable(const QList<Sales> &list)
{
    if(sSalesTable != nullptr)
    {
        sSalesTable->clearContents();
        int index = 0;
        for(const auto &s : list)
        {
            if(sSalesTable->rowCount() <= index)
            {
                sSalesTable->setRowCount(index + 5);
            }
            sSalesTable->setItem(index, 0, new QTableWidgetItem(s.id));
            sSalesTable->setItem(index, 1, new QTableWidgetItem(s.date));
            sSalesTable->setItem(index, 2, new QTableWidgetItem(QString::number(s.amount)));
            sSalesTable->setItem(index, 3, new QTableWidgetItem(s.customer));
            sSalesTable->setItem(index, 4, new QTableWidgetItem(s.custTele));
            ++index;
        }
    }
}

void SalesWidget::showInSearchSaleDetTable(const QList<SaleItem> &list)
{
    if(sSalesDetailTable != nullptr)
    {
        sSalesDetailTable->clearContents();
        int index = 0;
        for(const auto &s : list)
        {
            if(sSalesDetailTable->rowCount() <= index)
            {
                sSalesDetailTable->setRowCount(index + 5);
            }
            sSalesDetailTable->setItem(index, 0, new QTableWidgetItem(s.saleID));
            sSalesDetailTable->setItem(index, 1, new QTableWidgetItem(s.barcode));
            sSalesDetailTable->setItem(index, 2, new QTableWidgetItem(QString::number(s.num)));
            sSalesDetailTable->setItem(index, 3, new QTableWidgetItem(QString::number(s.price)));
            ++index;
        }
    }
}

void SalesWidget::showInAddSaleDetTable(const QList<SaleItem> &list)
{
    if(aSalesTable != nullptr)
    {
        aSalesTable->clearContents();
        int index = 0;
        for(const auto &s : list)
        {
            if(aSalesTable->rowCount() <= index)
            {
                aSalesTable->setRowCount(index + 5);
            }
            aSalesTable->setItem(index, 0, new QTableWidgetItem(s.barcode));
            aSalesTable->setItem(index, 1, new QTableWidgetItem(QString::number(s.price)));
            aSalesTable->setItem(index, 2, new QTableWidgetItem(QString::number(s.num)));
            ++index;
        }
    }
}


