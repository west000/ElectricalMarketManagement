#include "supplierwidget.h"

SupplierWidget::SupplierWidget(QWidget *parent) : QWidget(parent)
{
    InitSupplierWidget();
    InitSupplierTable();
}

void SupplierWidget::InitSupplierTable()
{
    if(supplierTable != nullptr)
    {
        QList<Supplier> result;
        Supplier::searchAll(result);
        int index = 0;
        for(const auto &item : result)
        {
            if(supplierTable->rowCount() <= index)
            {
                supplierTable->setRowCount(index + 1);
            }
            supplierTable->setItem(index, 0, new QTableWidgetItem(item.sname));
            supplierTable->setItem(index, 1, new QTableWidgetItem(item.saddr));
            supplierTable->setItem(index, 2, new QTableWidgetItem(item.telenum));
            ++index;
        }
    }
}


void SupplierWidget::InitSupplierWidget()
{
    supplierWidget = new QWidget();

    // 标签
    QLabel *title = new QLabel(QString::fromLocal8Bit("增加供应商"));
    title->setFixedHeight(40);
    QLabel *supplierTableLabel = new QLabel(QString::fromLocal8Bit("供应商信息列表"));
    supplierTableLabel->setFixedHeight(40);
    QLabel *snameLabel = new QLabel(QString::fromLocal8Bit("供应商名称"));
    QLabel *saddrLabel = new QLabel(QString::fromLocal8Bit("供应商地址"));
    QLabel *teleLabel = new QLabel(QString::fromLocal8Bit("供应商联系电话"));
    title->setParent(supplierWidget);
    supplierTableLabel->setParent(supplierWidget);
    snameLabel->setParent(supplierWidget);
    saddrLabel->setParent(supplierWidget);
    teleLabel->setParent(supplierWidget);
    // 按钮
    QPushButton *submitButton = new QPushButton(supplierWidget);
    submitButton->setText(QString::fromLocal8Bit("添加"));
    submitButton->setFixedWidth(100);
    QPushButton *resetButton = new QPushButton(supplierWidget);
    resetButton->setText(QString::fromLocal8Bit("重置"));
    resetButton->setFixedWidth(100);
    // 输入框
    snameEdit = new QLineEdit(supplierWidget);
    saddrEdit = new QLineEdit(supplierWidget);
    teleEdit = new QLineEdit(supplierWidget);
    // 表格
    supplierTable = new QTableWidget(supplierWidget);
    supplierTable->setColumnCount(3);
    QStringList tableHeader;
    tableHeader << QString::fromLocal8Bit("供应商名称")
                << QString::fromLocal8Bit("供应商地址")
                << QString::fromLocal8Bit("联系电话");
    supplierTable->setHorizontalHeaderLabels(tableHeader);
    supplierTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    // 添加供应商信息的布局
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(snameLabel);
    hLayout1->addWidget(snameEdit);
    hLayout1->addWidget(teleLabel);
    hLayout1->addWidget(teleEdit);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(saddrLabel);
    hLayout2->addWidget(saddrEdit);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(submitButton);
    hLayout3->addWidget(resetButton);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(title);
    vLayout1->addLayout(hLayout1);
    vLayout1->addLayout(hLayout2);
    vLayout1->addLayout(hLayout3);

    // 供应商列表的布局
    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(supplierTableLabel);
    vLayout2->addWidget(supplierTable);

    // 供应商页面的布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1, 1);
    vLayout->addLayout(vLayout2, 2);

    supplierWidget->setLayout(vLayout);

    // 设置信号槽
    connect(submitButton, &QPushButton::clicked,
            this, &SupplierWidget::getSupplierInfo);
    connect(resetButton, &QPushButton::clicked,
            this, &SupplierWidget::clearSupplierInfoInput);
}

void SupplierWidget::getSupplierInfo()
{
    QString name = snameEdit->text();
    QString addr = saddrEdit->text();
    QString tele = teleEdit->text();

    if(name.isEmpty())
    {
        QMessageBox::critical(supplierWidget, QString::fromLocal8Bit("供应商名称出错"),
                              QString::fromLocal8Bit("供应商名称不能为空"), QMessageBox::Yes);
        return;
    }

    if(!Supplier::insertNewSupplierToDB(name, addr, tele))
    {
        QMessageBox::critical(supplierWidget, QString::fromLocal8Bit("供应商添加失败"),
                              QString::fromLocal8Bit("该供应商已经存在"), QMessageBox::Yes);
    }
    else
    {
        int index = supplierTable->rowCount();
        supplierTable->setRowCount(index + 1);
        supplierTable->setItem(index, 0, new QTableWidgetItem(name));
        supplierTable->setItem(index, 1, new QTableWidgetItem(addr));
        supplierTable->setItem(index, 2, new QTableWidgetItem(tele));
    }
}

void SupplierWidget::clearSupplierInfoInput()
{
    snameEdit->clear();
    saddrEdit->clear();
    teleEdit->clear();
}
