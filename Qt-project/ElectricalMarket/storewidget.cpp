#include "storewidget.h"

StoreWidget::StoreWidget(QWidget *parent) : QWidget(parent)
{
    InitStoreWidget();
}

void StoreWidget::InitStoreWidget()
{
    storeWidget = new QWidget();

    // 标签
    QLabel *title = new QLabel(QString::fromLocal8Bit("库存信息查询"));
    title->setFixedHeight(40);
    QLabel *storeTableLabel = new QLabel(QString::fromLocal8Bit("库存列表"));
    storeTableLabel->setFixedHeight(40);
    QLabel *purchaseIDLabel = new QLabel(QString::fromLocal8Bit("进货单编号"));
    QLabel *purchaseBeginDateLabel = new QLabel(QString::fromLocal8Bit("进货起始日期"));
    QLabel *barCodeLabel = new QLabel(QString::fromLocal8Bit("商品条形码"));
    QLabel *dnameLabel = new QLabel(QString::fromLocal8Bit("商品名称"));
    title->setParent(storeWidget);
    storeTableLabel->setParent(storeWidget);
    purchaseIDLabel->setParent(storeWidget);
    purchaseBeginDateLabel->setParent(storeWidget);
    barCodeLabel->setParent(storeWidget);
    dnameLabel->setParent(storeWidget);
    // 输入框
    purchaseBeginDate = new QDateEdit(storeWidget);
    purchaseBeginDate->setFixedWidth(250);
    purchaseIDEdit = new QLineEdit(storeWidget);
    purchaseIDEdit->setFixedWidth(250);
    dnameEdit = new QLineEdit(storeWidget);
    dnameEdit->setFixedWidth(250);
    barcodeEdit = new QLineEdit(storeWidget);
    barcodeEdit->setFixedWidth(250);
    // 表格
    storeTable = new QTableWidget(storeWidget);
    storeTable->setColumnCount(5);
    QStringList tableHeader;
    tableHeader << QString::fromLocal8Bit("进货批次编号")
                << QString::fromLocal8Bit("进货时间")
                << QString::fromLocal8Bit("商品条形码")
                << QString::fromLocal8Bit("商品名称")
                << QString::fromLocal8Bit("剩余数量");
    storeTable->setHorizontalHeaderLabels(tableHeader);
    storeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置不可编辑
    // 按钮
    QPushButton *searchAllButton = new QPushButton(storeWidget);
    searchAllButton->setText(QString::fromLocal8Bit("查询所有"));
    searchAllButton->setFixedWidth(125);
    QPushButton *searchByPIDButton = new QPushButton(storeWidget);
    searchByPIDButton->setText(QString::fromLocal8Bit("按进货批次查询"));
    searchByPIDButton->setFixedWidth(125);
    QPushButton *searchByPDateButton = new QPushButton(storeWidget);
    searchByPDateButton->setText(QString::fromLocal8Bit("按进货日期查询"));
    searchByPDateButton->setFixedWidth(125);
    QPushButton *searchByBarCodeButton = new QPushButton(storeWidget);
    searchByBarCodeButton->setText(QString::fromLocal8Bit("按商品条形码查询"));
    searchByBarCodeButton->setFixedWidth(125);
    QPushButton *searchByDnameButton = new QPushButton(storeWidget);
    searchByDnameButton->setText(QString::fromLocal8Bit("按商品名称查询"));
    searchByDnameButton->setFixedWidth(125);

    // 布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(purchaseIDLabel, 1, Qt::AlignLeft);
    hLayout1->addWidget(purchaseIDEdit, 2, Qt::AlignLeft);
    hLayout1->addWidget(searchByPIDButton, 3, Qt::AlignRight);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(purchaseBeginDateLabel, 1, Qt::AlignLeft);
    hLayout2->addWidget(purchaseBeginDate, 2, Qt::AlignLeft);
    hLayout2->addWidget(searchByPDateButton, 3, Qt::AlignRight);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(barCodeLabel, 1, Qt::AlignLeft);
    hLayout3->addWidget(barcodeEdit, 2, Qt::AlignLeft);
    hLayout3->addWidget(searchByBarCodeButton, 3, Qt::AlignRight);

    QHBoxLayout *hLayout4 = new QHBoxLayout;
    hLayout4->addWidget(dnameLabel, 1, Qt::AlignLeft);
    hLayout4->addWidget(dnameEdit, 2, Qt::AlignLeft);
    hLayout4->addWidget(searchByDnameButton, 3, Qt::AlignRight);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(title);
    vLayout1->addLayout(hLayout1);
    vLayout1->addLayout(hLayout2);
    vLayout1->addLayout(hLayout3);
    vLayout1->addLayout(hLayout4);
    vLayout1->addWidget(searchAllButton, 1, Qt::AlignRight);

    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(storeTableLabel);
    vLayout2->addWidget(storeTable);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1);
    vLayout->addLayout(vLayout2);

    storeWidget->setLayout(vLayout);

    // 信号槽
    connect(searchByPIDButton, &QPushButton::clicked,
            this, &StoreWidget::searchByPID);
    connect(searchByPDateButton, &QPushButton::clicked,
            this, &StoreWidget::searchByPDate);
    connect(searchByBarCodeButton, &QPushButton::clicked,
            this, &StoreWidget::searchByBarCode);
    connect(searchByDnameButton, &QPushButton::clicked,
            this, &StoreWidget::searchByDname);
    connect(searchAllButton, &QPushButton::clicked,
            this, &StoreWidget::searchAll);
}

void StoreWidget::searchByPID()
{
    QString pID = purchaseIDEdit->text();
    if(pID.isEmpty())
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("进货批次编号不能为空"), QMessageBox::Yes);
        return ;
    }

    QList<Store> result;
    if(Store::searchByPID(pID, result))
    {
        showResultOnTable(result);
    }
    else
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
        return ;
    }
}

void StoreWidget::searchByPDate()
{
    QString date = purchaseIDEdit->text();

    QList<Store> result;
    if(Store::searchByPDate(date, result))
    {
        showResultOnTable(result);
    }
    else
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
        return ;
    }
}

void StoreWidget::searchByBarCode()
{
    QString code = barcodeEdit->text();
    if(code.isEmpty())
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("条形码不能为空"), QMessageBox::Yes);
        return ;
    }

    QList<Store> result;
    if(Store::searchByBarCode(code, result))
    {
        showResultOnTable(result);
    }
    else
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
        return ;
    }
}

void StoreWidget::searchByDname()
{
    QString name = dnameEdit->text();
    if(name.isEmpty())
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("商品名称不能为空"), QMessageBox::Yes);
        return ;
    }

    QList<Store> result;
    if(Store::searchByDname(name, result))
    {
        showResultOnTable(result);
    }
    else
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
        return ;
    }
}

void StoreWidget::searchAll()
{
    QList<Store> result;
    if(Store::searchAll(result))
    {
        showResultOnTable(result);
    }
    else
    {
        QMessageBox::critical(storeWidget, QString::fromLocal8Bit("查询错误"),
                              QString::fromLocal8Bit("数据库连接出错"), QMessageBox::Yes);
        return ;
    }
}

void StoreWidget::showResultOnTable(const QList<Store> &result)
{
    // 首先先清空原有的数据
    storeTable->clearContents();
    // 显示结果
    int index = 0;
    for(const auto &item : result)
    {
        if(storeTable->rowCount() <= index)
        {
            storeTable->setRowCount(index + 5);
        }
        storeTable->setItem(index, 0, new QTableWidgetItem(item.pID));
        storeTable->setItem(index, 1, new QTableWidgetItem(item.pDate));
        storeTable->setItem(index, 2, new QTableWidgetItem(item.barcode));
        storeTable->setItem(index, 3, new QTableWidgetItem(item.dname));
        storeTable->setItem(index, 4, new QTableWidgetItem(QString::number(item.num)));
        ++index;
    }
}

void StoreWidget::clearStoreInput()
{
    purchaseIDEdit->clear();
    dnameEdit->clear();
    barcodeEdit->clear();
    QDate date = QDate::currentDate();
    purchaseBeginDate->setDate(date);
}
