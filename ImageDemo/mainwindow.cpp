#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_colorbar = ui->colorbarwidget;
    m_imagewidget = ui->image;
    m_imagewidget->setColor(m_colorbar);
}

MainWindow::~MainWindow()
{
    delete ui;
}
