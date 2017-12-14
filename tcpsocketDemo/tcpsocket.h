#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>

class Tcpsocket : public QObject
{
    Q_OBJECT
public:
    Tcpsocket(QObject *parent = NULL);
    ~Tcpsocket();

    void setIpAddress(const QString &ip);
    QString getIpAddress();
    void setIpPort(const quint16 &port);
    quint16 getIpPort();
    bool connect();
    void disconnect();

private:
    QString m_ip;
    quint16 m_port;
    QTcpSocket* m_tcpsocket;

};

#endif // TCPSOCKET_H
