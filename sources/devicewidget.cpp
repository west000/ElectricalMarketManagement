#include "devicewidget.h"

DeviceWidget::DeviceWidget(QWidget *parent) : QWidget(parent)
{
    InitDeviceInfoWidget();
    InitDeviceTable();
}

void DeviceWidget::InitDeviceTable()
{
    if(deviceInfoTable != nullptr)
    {
        QList<Device> result;
        Device::searchAll(result);
        int index = 0;
        for(const auto &item : result)
        {
            if(deviceInfoTable->rowCount() <= index)
            {
                deviceInfoTable->setRowCount(index + 1);
            }
            deviceInfoTable->setItem(index, 0, new QTableWidgetItem(item.barcode));
            deviceInfoTable->setItem(index, 1, new QTableWidgetItem(item.dname));
            deviceInfoTable->setItem(index, 2, new QTableWidgetItem(item.productor));
            deviceInfoTable->setItem(index, 3, new QTableWidgetItem(item.makedate));
            ++index;
        }
    }
}

void DeviceWidget::InitDeviceInfoWidget()
{
    deviceInfoWidget = new QWidget();

    // 标签
    QLabel *title = new QLabel(QString::fromLocal8Bit("增加电器"));
    title->setFixedHeight(40);
    QLabel *deviceTableLabel = new QLabel(QString::fromLocal8Bit("电器信息列表"));
    deviceTableLabel->setFixedHeight(40);
    QLabel *barCodeLabel = new QLabel(QString::fromLocal8Bit("条形码"));
    QLabel *dnameLabel = new QLabel(QString::fromLocal8Bit("电器名称"));
    QLabel *productLabel = new QLabel(QString::fromLocal8Bit("生产商"));
    QLabel *makedateLabel = new QLabel(QString::fromLocal8Bit("生产日期"));
    // 输入框
    barCodeEdit = new QLineEdit(deviceInfoWidget);
    dnameEdit = new QLineEdit(deviceInfoWidget);
    productEdit = new QLineEdit(deviceInfoWidget);
    makedateEdit = new QDateEdit(deviceInfoWidget);
    // 表格
    deviceInfoTable = new QTableWidget(deviceInfoWidget);
    deviceInfoTable->setColumnCount(4);
    QStringList tableHeader;
    tableHeader << QString::fromLocal8Bit("条形码")
                << QString::fromLocal8Bit("电器名称")
                << QString::fromLocal8Bit("生产商")
                << QString::fromLocal8Bit("生产日期");
    deviceInfoTable->setHorizontalHeaderLabels(tableHeader);
    deviceInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);    //设置不可编辑
    // 按钮
    QPushButton *submitButton = new QPushButton(deviceInfoWidget);
    submitButton->setText(QString::fromLocal8Bit("添加"));
    submitButton->setFixedWidth(100);
    QPushButton *resetButton = new QPushButton(deviceInfoWidget);
    resetButton->setText(QString::fromLocal8Bit("重置"));
    resetButton->setFixedWidth(100);

    title->setParent(deviceInfoWidget);
    barCodeLabel->setParent(deviceInfoWidget);
    dnameLabel->setParent(deviceInfoWidget);
    productLabel->setParent(deviceInfoWidget);
    makedateLabel->setParent(deviceInfoWidget);

    // 添加电器信息的布局
    QHBoxLayout *hLayout0 = new QHBoxLayout;
    hLayout0->addWidget(title);

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(barCodeLabel);
    hLayout1->addWidget(barCodeEdit);
    hLayout1->addWidget(dnameLabel);
    hLayout1->addWidget(dnameEdit);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(productLabel);
    hLayout2->addWidget(productEdit);
    hLayout2->addWidget(makedateLabel);
    hLayout2->addWidget(makedateEdit);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(submitButton);
    hLayout3->addWidget(resetButton);

    QVBoxLayout *vLayout1 = new QVBoxLayout;
    vLayout1->setGeometry(QRect(0, 0, this->width(), this->height()));
    vLayout1->addLayout(hLayout0, 1);
    vLayout1->addLayout(hLayout1, 2);
    vLayout1->addLayout(hLayout2, 2);
    vLayout1->addLayout(hLayout3, 3);

    // 电器信息列表的布局
    QVBoxLayout *vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(deviceTableLabel, 1);
    vLayout2->addWidget(deviceInfoTable, 7);

    // 电器信息页面的布局
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(vLayout1, 1);
    vLayout->addLayout(vLayout2, 5);

    deviceInfoWidget->setLayout(vLayout);

    // 设置信号槽
    connect(submitButton, &QPushButton::clicked,
            this, &DeviceWidget::getNewDeviceInfo);
    connect(resetButton, &QPushButton::clicked,
            this, &DeviceWidget::clearDeviceInfoInput);
}

void DeviceWidget::getNewDeviceInfo()
{
    QString code = barCodeEdit->text();
    QString name = dnameEdit->text();
    QString prod = productEdit->text();
    QString date = makedateEdit->text();

    if(code.isEmpty())
    {
        QMessageBox::critical(deviceInfoWidget, QString::fromLocal8Bit("条形码出错"),
                              QString::fromLocal8Bit("条形码不能为空"), QMessageBox::Yes);
        return ;
    }

    if(name.isEmpty())
    {
        QMessageBox::critical(deviceInfoWidget, QString::fromLocal8Bit("电器名称出错"),
                              QString::fromLocal8Bit("电器名称不能为空"), QMessageBox::Yes);
        return ;
    }

    if(date.isEmpty())
    {
        date = Utility::getCurDate();
    }

    if(!Device::insertNewDeviceToDB(name, prod, code, date))
    {
        QMessageBox::critical(deviceInfoWidget, QString::fromLocal8Bit("电器信息添加失败"),
                              QString::fromLocal8Bit("条形码已经存在"), QMessageBox::Yes);
    }
    else
    {
        int index = deviceInfoTable->rowCount();
        deviceInfoTable->setRowCount(index + 1);
        deviceInfoTable->setItem(index, 0, new QTableWidgetItem(code));
        deviceInfoTable->setItem(index, 1, new QTableWidgetItem(name));
        deviceInfoTable->setItem(index, 2, new QTableWidgetItem(prod));
        deviceInfoTable->setItem(index, 3, new QTableWidgetItem(date));
    }
}

void DeviceWidget::clearDeviceInfoInput()
{
    barCodeEdit->clear();
    dnameEdit->clear();
    productEdit->clear();
}
