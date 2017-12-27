#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RunBtn_clicked()
{
//    CaptureThread* _capturThread = new CaptureThread();
//    _capturThread->setIp("192.168.1.6");
//    _capturThread->setPort(8000);
//    _capturThread->enableCapture();
    m_sendCMD = new SendCMD();
    m_sendCMD->setIp("192.168.1.108");
    m_sendCMD->setPort(8000);
    bool _bconnected = m_sendCMD->connected();
    if(_bconnected)
    {
        qDebug("connected");
    }
}

void MainWindow::on_StopBtn_clicked()
{

}

void MainWindow::on_SendCMD_clicked()
{
    if(m_sendCMD->connected())
    {
        //m_sendCMD->inspectConfig();
        //m_sendCMD->requestPointQty();
        m_sendCMD->scanInfo();
    }
}
