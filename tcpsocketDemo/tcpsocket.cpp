#include "tcpsocket.h"

Tcpsocket::Tcpsocket(QObject *parent) : QObject(parent)
{
    m_tcpsocket = new QTcpSocket();
}

Tcpsocket::~Tcpsocket()
{

}

void Tcpsocket::setIpAddress(const QString &ip)
{
    this->m_ip = ip;
}

QString Tcpsocket::getIpAddress()
{
    return this->m_ip;
}

void Tcpsocket::setIpPort(const quint16 &port)
{
    this->m_port = port;
}

quint16 Tcpsocket::getIpPort()
{
    return this->m_port;
}

bool Tcpsocket::connect()
{
    if(m_tcpsocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    m_tcpsocket->connectToHost(m_ip,m_port);

    if(!m_tcpsocket->waitForConnected(1000))
    {
        qDebug()<<"Can't connect :"<<m_tcpsocket;
    }
//    //等待服务器应答 10s
//    bool bReady = m_tcpsocket->waitForReadyRead(10000);
    //发送数据,需要服务器来接收
    QByteArray data = "this is tcp client.";
    m_tcpsocket->write(data);
    return true;
}

void Tcpsocket::disconnect()
{

    this->m_tcpsocket->disconnectFromHost();
}


