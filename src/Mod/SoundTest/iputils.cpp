#include "iputils.h"
#include<QList>

using namespace SoundTest;

IpUtils::IpUtils() {}

QList<QHostAddress> IpUtils::getIPAddresses()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    QList<QHostAddress> addList=hostInfo.addresses();
    return addList;
}

QString IpUtils::ipToQString(QHostAddress addr){
    quint32 int32_addr=addr.toIPv4Address();
    quint8* ptr_int8_addr=(quint8*)&int32_addr;
    QString r1=QString::number(*ptr_int8_addr);
    ptr_int8_addr++;
    QString r2=QString::number(*ptr_int8_addr);
    ptr_int8_addr++;
    QString r3=QString::number(*ptr_int8_addr);
    ptr_int8_addr++;
    QString r4=QString::number(*ptr_int8_addr);
    QString res=r4+"."+r3+"."+r2+"."+r1;
    return res;
}
