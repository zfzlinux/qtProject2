#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <cmdconfig.h>

class CaptureThread : public QThread
{
    Q_OBJECT
public:
    explicit CaptureThread(QThread *parent = 0);
    void run();
    void setIp(QString _ip){ m_ipAddr = _ip;}
    void setPort(quint16 _port){m_port = _port;}
    void enableCapture();
private slots:
public:
    QTcpSocket *m_CaptureSocket;
    QTcpSocket *m_CMDSocket;
    QString m_ipAddr;
    quint16 m_port;
    QByteArray m_BeamBuf;
};

#endif // CAPTURETHREAD_H
