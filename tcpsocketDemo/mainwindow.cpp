#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->tcpsocket = new Tcpsocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    QString _ip = ui->ipAddress->text();
    quint16 _port = ui->ipPort->text().toShort();
    this->tcpsocket->setIpAddress(_ip);
    this->tcpsocket->setIpPort(_port);
    this->tcpsocket->connect();
}

void MainWindow::on_closeBtn_clicked()
{
    this->tcpsocket->disconnect();
}
