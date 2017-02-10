#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("电器商城管理系统"));
    this->resize(600, 600);

    tabWidget = new QTabWidget(this);
    tabWidget->resize(600, 600);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->setTabShape(QTabWidget::Triangular);

    InitDeviceInfoWidget();
    InitSupplierWidget();
    InitPurchaseWidget();
    InitSalesWidget();
    InitStoreWidget();

    tabWidget->addTab(devicePage->deviceInfoWidget, QIcon(), QString::fromLocal8Bit("电器信息"));
    tabWidget->addTab(supplierPage->supplierWidget, QIcon(), QString::fromLocal8Bit("供应商"));
    tabWidget->addTab(purchasePage->purchaseWidget, QIcon(), QString::fromLocal8Bit("进货"));
    tabWidget->addTab(salesPage->salesWidget, QIcon(), QString::fromLocal8Bit("销售"));
    tabWidget->addTab(storePage->storeWidget, QIcon(), QString::fromLocal8Bit("库存"));


    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(tabWidget);
    this->setLayout(hLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tabWidget;
}


void MainWindow::InitDeviceInfoWidget()
{
    devicePage = new DeviceWidget(this);
    // 从数据库加载原有记录到进货表格中
}

void MainWindow::InitSupplierWidget()
{
    supplierPage = new SupplierWidget(this);
}

void MainWindow::InitSalesWidget()
{
    salesPage = new SalesWidget(this);
}

void MainWindow::InitPurchaseWidget()
{
    purchasePage = new PurchaseWidget();
}

void MainWindow::InitStoreWidget()
{
    storePage = new StoreWidget();
}
