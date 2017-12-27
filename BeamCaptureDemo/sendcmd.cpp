#include "sendcmd.h"

SendCMD::SendCMD(QObject *parent) : QObject(parent)
{
    m_tcpSocket = new QTcpSocket();
    connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(slotReadData()));
}

bool SendCMD::connected()
{
    if(m_tcpSocket->state() ==QAbstractSocket::ConnectedState)
    {
        return true;
    }
    m_tcpSocket->connectToHost(m_ipAddr,m_port);

    if ( !m_tcpSocket->waitForConnected(1000) ) {
        qWarning() << "Can't connect"<<m_tcpSocket;
    }


    if(m_tcpSocket->state() != QAbstractSocket::ConnectedState)
    {
        return false;
    }
    //wait for server response;
//    bool _bReady = m_tcpSocket->waitForReadyRead(2000);
//    Q_ASSERT_X(_bReady, "Device::connect", "tcp connect failed");
//    m_tcpSocket->readAll();
    return true;
}

void SendCMD::disconnect()
{
    m_tcpSocket->disconnectFromHost();
}

void SendCMD::dispatchCMD(int cmd, char *data,int len)
{
//    if(m_tcpSocket->state() != QAbstractSocket::ConnectedState)
//    {
//        return ;
//    }
    if(len<0)return;

    this->keepLastCMD(cmd);
    QByteArray BData;
    BData.resize(len+MIN_BUFFER_SIZE);
    qDebug()<<BData.size();

   char *buf = BData.data();
    ::memcpy(buf,(char*)&cmd,sizeof(int));
    ::memcpy(buf+4,(char*)&len,sizeof(int));
    ::memcpy(buf+8,data,len);
    m_tcpSocket->write(BData);
}

void SendCMD::inspectConfig()
{
    if(m_tcpSocket->state()!= QAbstractSocket::ConnectedState)
    {
        qDebug("NO connected");
        return ;
    }
    char buf[1024]={0};
    int cmd = CMD_GET_INSPECT_CONFIG;
    this->keepLastCMD(cmd);
    int len =4;
    int data = true;
    ::memcpy(buf,(char *)&cmd,sizeof(int));
    ::memcpy(buf+4,(char *)&len,sizeof(int));
    ::memcpy(buf+8,&data,len);
    m_tcpSocket->write(buf,12);
    return ;
}

void SendCMD::requestPointQty()
{
    int cmd = CMD_GET_VAL_POINT_QTY;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::resetEncoder()
{
    int cmd = CMD_RESET_ENCODER;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::scanInfo()
{
    int cmd = CMD_GET_CONFIG_SCAN;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::focalLawInfo(int group)
{
    int cmd = CMD_GET_CONFIG_FOCALLAW;
    int len =4;
    int data=group;
    m_GroupNum = group;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::ConfigPart()
{
    int cmd = CMD_GET_CONFIG_PART;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::ExitPoints(int group)
{
    int cmd = CMD_GET_EXITPOINTE;
    int len =4;
    int data=group;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::setScanStart()
{
    int cmd = CMD_SET_SCAN_START;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}


void SendCMD::GroupQty()
{
    int cmd = CMD_GET_VAL_GROUP_QTY;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::GroupDataOffset()
{
    int cmd = CMD_GET_VAL_GROUP_DATA_OFFSET;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}

void SendCMD::BeamDataOffset()
{
    int cmd = CMD_GET_VAL_GROUP_BEAM_OFFSET;
    int len =4;
    int data=1;
    this->dispatchCMD(cmd,(char*)&data,len);
}
//read and dispatch
void SendCMD::slotReadData()
{
    QByteArray _recv = m_tcpSocket->readAll();
    //
    int _cmd = this->getLastCMD();
    switch(_cmd)
    {
    case CMD_GET_INSPECT_CONFIG:
        emit slotReadInspectConfig(_recv);
        break;
    case CMD_GET_VAL_POINT_QTY:
        emit slotReadPointQty(_recv);
        break;
    case CMD_GET_CONFIG_SCAN:
        emit slotReadScanInfo(_recv);
        break;
    case CMD_GET_CONFIG_FOCALLAW:
        emit slotReadFocalLawInfo(_recv);
        break;
    case CMD_GET_CONFIG_PART:
        emit slotReadConfigPart(_recv);
        break;
    case CMD_GET_EXITPOINTE:
        emit slotReadExitPoint(_recv);
        break;
    case CMD_SET_SCAN_START:
        emit slotReadScanStart(_recv);
        break;
    case CMD_GET_VAL_GROUP_QTY:
        emit slotReadGroupQty(_recv);
        break;
    case CMD_GET_VAL_GROUP_DATA_OFFSET:
        emit slotReadGroupDataOffset(_recv);
        break;
    case CMD_GET_VAL_GROUP_BEAM_OFFSET:
        emit slotReadBeamDataOffset(_recv);
        break;
    default:
        break;
    }

}

void SendCMD::slotReadInspectConfig(QByteArray _recvData)
{
    static int totalLen =0;
    static int _index =0;
    QByteArray temp ;

    m_recvData.append(_recvData);
    //
    totalLen = m_recvData.size();
    qDebug()<<"totalLen"<<totalLen;
    while(totalLen)
    {
        _index = m_recvData.indexOf("#####");
        qDebug()<<"index:"<<_index;
        if(_index <0 )
        {
            //继续接收
            break;
        }
        m_recvData = m_recvData.mid(_index);

        if(m_recvData.size()<(9))
        {
            break;
        }

        totalLen = m_recvData.size();
        qDebug()<<m_recvData.data();
        int size = *(int *)(m_recvData.data()+5);
        qDebug()<<"size:"<<size;
        if(totalLen < size)
        {
            break;
        }
        qDebug()<<"Finsh";
        temp = m_recvData.mid(_index+5,size);
        //update parameter;
        temp = m_recvData.mid(0,sizeof(INSPEC_DATA_FILE));
        UpdateInspectDataFile(temp);
        temp = m_recvData.mid(sizeof(INSPEC_DATA_FILE),sizeof(DRAW_INFO_PACK));
        UpdateDrawInfoPack(temp);

        int _grupNum = getGroupNum();
        temp = m_recvData.mid(sizeof(INSPEC_DATA_FILE)+sizeof(DRAW_INFO_PACK));
        UpdateGroupInfo(temp,_grupNum);
        //
        m_recvData = m_recvData.mid(size+9);
        totalLen = m_recvData.size();
    }
}

void SendCMD::slotReadPointQty(QByteArray _recvData)
{
    QByteArray RecvBuf;
    RecvBuf.append(_recvData);
    qDebug()<<RecvBuf;
    RecvBuf.clear();
}

void SendCMD::slotReadResetEncoder(QByteArray _recvData)
{
    QByteArray RecvBuf;
    RecvBuf.append(_recvData);
    qDebug()<<RecvBuf;
    RecvBuf.clear();
}

void SendCMD::slotReadScanInfo(QByteArray _recvData)
{
    if(_recvData.size())
    {
        ::memset(&m_scanInfo,0,sizeof(CONFIG_SCAN));
        ::memcpy(&m_scanInfo,_recvData,sizeof(CONFIG_SCAN));
        qDebug()<<"scan start:"<<m_scanInfo.fScanStart;
        this->clearLastCMD();
    }
}

void SendCMD::slotReadFocalLawInfo(QByteArray _recvData)
{
    CONFIG_FOCALLAW  focallawInfo;
    if(_recvData.size())
    {
        ::memset(&focallawInfo,0,sizeof(CONFIG_FOCALLAW));
        ::memcpy(&focallawInfo,_recvData,sizeof(CONFIG_FOCALLAW));
        m_focallaw[m_GroupNum]=focallawInfo;
        this->clearLastCMD();
    }
}

void SendCMD::slotReadConfigPart(QByteArray _recvData)
{
    if(_recvData.size())
    {
        ::memset(&m_partInfo,0,sizeof(CONFIG_PART_INFO));
        ::memcpy(&m_partInfo,_recvData,sizeof(CONFIG_PART_INFO));
        this->clearLastCMD();
    }
}

void SendCMD::slotReadExitPoint(QByteArray _recvData)
{

}

void SendCMD::slotReadScanStart(QByteArray _recvData)
{

}

void SendCMD::slotReadGroupQty(QByteArray _recvData)
{

}

void SendCMD::slotReadGroupDataOffset(QByteArray _recvData)
{

}

void SendCMD::slotReadBeamDataOffset(QByteArray _recvData)
{

}
//
void SendCMD::UpdateInspectDataFile(QByteArray _InspectDataFile)
{
    if(_InspectDataFile.size())
    {
        m_inspectDataFile = *(INSPEC_DATA_FILE *)_InspectDataFile.data();
    }
}

void SendCMD::UpdateDrawInfoPack(QByteArray _DrawInfoPack)
{
    m_drawInfoPack = *(DRAW_INFO_PACK*)_DrawInfoPack.data();
}
void SendCMD::UpdateGroupInfo(QByteArray _GroupInfo,int groupNum)
{
    QByteArray oneGroup;
    for(int i=0;i<groupNum;i++)
    {
        int size = sizeof(GROUP_INFO);
        int startPos = i*size;
        oneGroup = _GroupInfo.mid(startPos,size);
        ::memset(&m_groupInfo[i],0,size);
        ::memcpy(&m_groupInfo[i],oneGroup,size);
    }
}

