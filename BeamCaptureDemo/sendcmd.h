#ifndef SENDCMD_H
#define SENDCMD_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <cmdconfig.h>
#include <configure/dopplerdatafileconfigure.h>

#define MIN_BUFFER_SIZE (8)
class SendCMD : public QObject
{
    Q_OBJECT
public:
    explicit SendCMD(QObject *parent = 0);
    void setIp(QString _ip){ m_ipAddr = _ip;}
    void setPort(quint16 _port){m_port = _port;}
    bool connected();
    void disconnect();
    void dispatchCMD(int cmd, char *data,int len);

private:
    void keepLastCMD(int cmd){m_LastCMD = cmd;}
    int  getLastCMD(){return m_LastCMD;}
    void clearLastCMD(){m_LastCMD = 0;}
private slots:
    void slotReadData();
    void slotReadInspectConfig(QByteArray _recvData);
    void slotReadPointQty(QByteArray _recvData);
    void slotReadResetEncoder(QByteArray _recvData);
    void slotReadScanInfo(QByteArray _recvData);
    void slotReadFocalLawInfo(QByteArray _recvData);
    void slotReadConfigPart(QByteArray _recvData);
    void slotReadExitPoint(QByteArray _recvData);
    void slotReadScanStart(QByteArray _recvData);
    void slotReadGroupQty(QByteArray _recvData);
    void slotReadGroupDataOffset(QByteArray _recvData);
    void slotReadBeamDataOffset(QByteArray _recvData);

public:
    void inspectConfig();
    void requestPointQty();
    void resetEncoder();
    void scanInfo();
    void focalLawInfo(int group);
    void ConfigPart();
    void ExitPoints(int group);
    void GroupQty();
    void GroupDataOffset();
    void BeamDataOffset();
    void setScanStart();

private:
    void UpdateInspectDataFile(QByteArray _InspectDataFile);
    void UpdateDrawInfoPack(QByteArray _DrawInfoPack);
    void UpdateGroupInfo(QByteArray _GroupInfo, int groupNum);
public:
    INSPEC_DATA_FILE getInspectDataFile(){return m_inspectDataFile;}
    DRAW_INFO_PACK getDrawInfoPack(){return m_drawInfoPack;}
    int getGroupNum(){return m_drawInfoPack.nGroupNum;}
    GROUP_INFO getGroupInfo(int groupIndex) {return m_groupInfo[groupIndex];}
public:
    QTcpSocket* m_tcpSocket;
    QString m_ipAddr;
    quint16 m_port;
    QByteArray m_recvData;
private:
    int m_LastCMD;
    int m_GroupNum;
    CONFIG_SCAN m_scanInfo;
    CONFIG_PART_INFO m_partInfo;
    INSPEC_DATA_FILE m_inspectDataFile;
    DRAW_INFO_PACK m_drawInfoPack;
    CONFIG_FOCALLAW m_focallaw[setup_MAX_GROUP_QTY];
    GROUP_INFO m_groupInfo[setup_MAX_GROUP_QTY];

};

#endif // SENDCMD_H
