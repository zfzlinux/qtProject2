#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->group1->setlabeltext("group1");
    ui->group2->setlabeltext("group2");
    ui->group3->setlabeltext("group3");
    ui->group4->setlabeltext("group4");
}

MainWindow::~MainWindow()
{
    delete ui;
}
