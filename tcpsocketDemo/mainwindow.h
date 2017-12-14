#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpsocket.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::MainWindow *ui;
    Tcpsocket* tcpsocket;

};

#endif // MAINWINDOW_H
