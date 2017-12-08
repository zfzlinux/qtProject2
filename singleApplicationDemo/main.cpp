#include "mainwindow.h"
#include <QApplication>
#include "singleapplication.h"

int main(int argc, char *argv[])
{
    singleApplication a(argc,argv,"SingleApplication");
    if(a.isRunning())
    {
        a.sendMessage("recevie message from other instance.");
     return 0;
    }
    MainWindow w;
    QObject::connect(&a,SIGNAL(messageAvailable(QString)),&w,SLOT(receiveMessage(QString)));
    w.show();

    return a.exec();
}
