#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

class singleApplication : public QApplication
{
    Q_OBJECT
public:
   singleApplication(int &argc, char **argv,const QString uniqueKey);
   bool isRunning();
   bool sendMessage(const QString &message);

signals:
   void messageAvailable(QString message);

public slots:
   void receiveMessage();

private:
   bool _isRunning;
   QString _uniqueKey;
   QSharedMemory sharedMemory;
   QLocalServer* localServer;
   static const int timeout = 1000;
};

#endif // SINGLEAPPLICATION_H
