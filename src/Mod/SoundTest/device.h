#ifndef DEVICE_H
#define DEVICE_H

#include <QStandardItemModel>
#include <QUdpSocket>

#include "iputils.h"


namespace SoundTest {

class Ui_WidgetSoundTest;
class Device:public QObject
{
    Q_OBJECT

public:
    Device(Ui_WidgetSoundTest* ui,QStandardItemModel* modelShebei);
    void on_pushButtonShaomiao_clicked();
    void on_pushButtonSellect_clicked();
    QString selectedIp;         //选定设备的ip

private Q_SLOTS:
    void onReadyRead();    //自定义的槽函数，当接收方接收到信号时触发

private:
    Ui_WidgetSoundTest* ui;
    int selectedDeviceIndex;    // 选定设备编号
    QStandardItemModel* modelShebei;
    QUdpSocket* reciver;     //QUdpSocket对象,接收
    QUdpSocket* sender;     //QUdpSocket对象, 发送
    QList<QHostAddress> ipList;
    QList<QHostAddress> ipDeviceList;
    void updateDeviceTable();

};

} // namespace SoundTest

#endif // DEVICE_H
