#include "capturethread.h"

CaptureThread::CaptureThread(QThread *parent) : QThread(parent)
{
    m_CaptureSocket = NULL;
    m_CMDSocket = NULL;
}

void CaptureThread::enableCapture()
{
    m_CMDSocket = new QTcpSocket();
    m_CMDSocket->connectToHost(m_ipAddr,m_port);

//    if(m_CMDSocket->state()!= QAbstractSocket::ConnectedState)
//    {
//        qDebug()<<"Can not connect";
//        return;
//    }
    char buf[120] = {0};
    int cmd = CMD_ENABLE_DATA_TRANSFER;
    int len =4;
    int data = true;
    ::memcpy(buf,(char *)&cmd,sizeof(int));
    ::memcpy(buf+4,(char *)&len,sizeof(int));
    ::memcpy(buf+8,&data,len);
    m_CMDSocket->write(buf,120);

    m_CMDSocket->waitForReadyRead(2000);
    len = m_CMDSocket->read(buf,120);
    qDebug()<<buf;
    //
   //this->start();

}

void CaptureThread::run()
{
    m_CaptureSocket = new QTcpSocket();
    m_CaptureSocket->connectToHost(m_ipAddr,m_port);

    if(m_CaptureSocket->waitForConnected())
    {
        qDebug()<<"connect is OK";
    }
    else{
        qDebug()<<"connect is fail";
        delete m_CaptureSocket;
        m_CaptureSocket = NULL;
        return ;
    }
   while(true)
    {
        QByteArray recv;
        m_CaptureSocket->waitForReadyRead(2000);
        recv = m_CaptureSocket->readAll();
        m_BeamBuf.append(recv);
        //find header
        int _headerIndex;
        _headerIndex = m_BeamBuf.indexOf("#####");
        if(_headerIndex>=0)
        {
            if(_headerIndex!=0)
            {
                m_BeamBuf = m_BeamBuf.mid(_headerIndex);
            }
            if(m_BeamBuf.size()>=9)
            {
                int _beamLength = *(int *)(m_BeamBuf.data()+5);
                if(m_BeamBuf.size()>=(_beamLength+9))
                {
                    //emit
                    qDebug()<<"BeamBuf size:"<<m_BeamBuf.size();
                    m_BeamBuf = m_BeamBuf.mid(_beamLength+9);
                    QThread::msleep(10);
                }
            }
        }
    }
}
