#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <capturethread.h>
#include <sendcmd.h>

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
    void on_RunBtn_clicked();

    void on_StopBtn_clicked();

    void on_SendCMD_clicked();

private:
    Ui::MainWindow *ui;
    SendCMD* m_sendCMD;
};

#endif // MAINWINDOW_H
