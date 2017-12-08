#include "singleapplication.h"
#include <QLocalSocket>

singleApplication::singleApplication(int &argc, char **argv, const QString uniqueKey):
    QApplication(argc,argv),_uniqueKey(uniqueKey)
{
    sharedMemory.setKey(_uniqueKey);
    if(sharedMemory.attach()){
        _isRunning = true;
    }
    else{
        _isRunning = false;

        if(!sharedMemory.create(1)){
         qDebug("Unable to create single instance.");
         return ;
        }
        // create local server and listen to incomming message from other instance;
        localServer = new QLocalServer(this);
        connect(localServer,SIGNAL(newConnection()),this,SLOT(receiveMessage()));
        localServer->listen(_uniqueKey);
    }
}

bool singleApplication::isRunning()
{
    return _isRunning;
}

bool singleApplication::sendMessage(const QString &message)
{
    if(!_isRunning){
        return false;
    }
    QLocalSocket localSocket(this);
    localSocket.connectToServer(_uniqueKey,QIODevice::WriteOnly);

    if(!(localSocket.waitForConnected(timeout))){
        qDebug(localSocket.errorString().toLatin1());
        return false;
    }

    localSocket.write(message.toUtf8());
    if(!(localSocket.waitForBytesWritten(timeout))){
        qDebug(localSocket.errorString().toLatin1());
        return false;
    }

    localSocket.disconnectFromServer();
    return true;
}

//public slots:
void singleApplication::receiveMessage()
{
    QLocalSocket *localSocket = localServer->nextPendingConnection();
    if(!(localSocket->waitForReadyRead(timeout))){
        qDebug(localSocket->errorString().toLatin1());
        return ;
    }

    QByteArray  byteArray = localSocket->readAll();
    QString message = QString::fromUtf8(byteArray.constData());
    emit messageAvailable(message);
    localSocket->disconnectFromServer();
}

