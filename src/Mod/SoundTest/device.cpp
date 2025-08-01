#include "device.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include "iputils.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QTcpSocket>
#include <QThread>

using namespace SoundTest;

Device::Device(Ui_WidgetSoundTest* ui, QStandardItemModel* modelShebei)
{
    this->ui=ui;
    this->modelShebei=modelShebei;

    //----------------------------------------------------------------
    //设备扫描
    sender = new QUdpSocket(this);// 在未来发送数据的时候，明确ip和port即可
    reciver = new QUdpSocket(this);// 需要绑定一下接受数据的ip和port，根据情况不同，还需要加入广播组

    // 广播代码
    reciver->bind(9000,QUdpSocket::ReuseAddressHint);   // 端口号 套接字形式
    // reciver->bind(9000);

    // 组播代码
    // reciver->bind(QHostAddress::AnyIPv4,9001,QUdpSocket::ReuseAddressHint);  //组播地址 端口号 套接字形式
    // reciver->joinMulticastGroup(QHostAddress("224.0.0.1"));                  //广播接收方接收来自地址发出的信号

    QObject::connect(reciver,SIGNAL(readyRead()),this,SLOT(onReadyRead()));  //获取信号：void QIODevice::readyRead()后，执行自定义的槽函数

    //----------------------------------------------------------------
    ipList=IpUtils::getIPAddresses();

    //----------------------------------------------------------------
    //填充设备表
    on_pushButtonShaomiao_clicked();


}

void Device::onReadyRead()  // 自定义槽函数的实现
{
    int size = reciver->pendingDatagramSize(); //获取接受到的数据的大小，QTcpSocket是bytesAvalible ， qint64 QUdpSocket::pendingDatagramSize() const
    char *buf = (char *) malloc( (size + 1) * sizeof(char) );
    memset( buf, 0, (size + 1)*sizeof(int) );

    QHostAddress senderAddress;
    quint16 senderPort;

    reciver->readDatagram(buf,size,&senderAddress,&senderPort); //接收数据，限定大小 qint64 QUdpSocket::readDatagram(char *data, qint64 maxSize, QHostAddress *address = Q_NULLPTR, quint16 *port = Q_NULLPTR)

    QString str = QString::fromLocal8Bit(buf); //将字符数组转化QString类型 QString QString::fromLocal8Bit(const char *str, int size = -1)
    qDebug()<<str;

    qDebug()<<senderAddress.toString();
    qDebug()<<senderPort;
    qDebug()<<senderAddress.toIPv4Address();

    // 获取发送方的IP地址并判断该ip是不是ipList成员
    bool isLocalIp=false;
    bool inDeviceIpList=false;
    for (int i=0;i<ipList.count();i++){
        if(senderAddress.toIPv4Address()==ipList[i].toIPv4Address()){
            isLocalIp=true;
            break;
        }
    }
    if (!isLocalIp){
        qDebug()<<"device ip";
        for (int j=0;j<ipDeviceList.count();j++){
            if (senderAddress.toIPv4Address()==ipDeviceList[j].toIPv4Address()){
                inDeviceIpList=true;
                break;
            }
        }
        if(!inDeviceIpList){
            ipDeviceList.append(senderAddress);
            updateDeviceTable();
        }
    }

}


void Device::on_pushButtonShaomiao_clicked()
{
    qDebug()<<"senderPort";
    QString str = "a";                    //获取行编辑器中的文字
    // 广播
    sender->writeDatagram(str.toLocal8Bit(),QHostAddress::Broadcast,9000); //qint64 QUdpSocket::writeDatagram(const char *data, qint64 size, const QHostAddress &address, quint16 port)
    // sender->writeDatagram(str.toUtf8(),QHostAddress("192.168.1.10"),9000);
    // 组播
    // sender->writeDatagram(str.toLocal8Bit(),QHostAddress("224.0.0.1"),12345);   //发送信号 字符串转化成本地八位表示，QByteArray QString::toLocal8Bit() const
    // reciver->close();                    // 广播方，也就是数据发送方，不通过reciver接受数据,直接通过本地获取数据
}

void Device::updateDeviceTable()
{
    //------------------------------------------------------------------------------------
    // 更新设备表

    /*设置列字段名*/
    modelShebei->clear();
    modelShebei->setColumnCount(4);
    modelShebei->setHeaderData(0,Qt::Horizontal, "ip");
    modelShebei->setHeaderData(1,Qt::Horizontal, "端口号");
    modelShebei->setHeaderData(2,Qt::Horizontal, "设为采集");
    modelShebei->setHeaderData(3,Qt::Horizontal, "设备类型");

    /*设置数据*/
    for (int i=0;i<ipDeviceList.count();i++)
    {
        modelShebei->setItem(i, 0, new QStandardItem(IpUtils::ipToQString(ipDeviceList[i])));

        modelShebei->setItem(i, 1, new QStandardItem("9000"));
        if (i==0)
            modelShebei->setItem(i, 2, new QStandardItem("是"));
        else
            modelShebei->setItem(i, 2, new QStandardItem("否"));
        modelShebei->setItem(i, 3, new QStandardItem("网口"));
    }

    if(ipDeviceList.count()>0){
        selectedIp=IpUtils::ipToQString(ipDeviceList[0]);
        ui->tableViewShebei->setModel(modelShebei);
    }


}


void Device::on_pushButtonSellect_clicked()
{
    // 设置当前连接设备
    //获取选择模型的指针
    QItemSelectionModel *selections =  ui->tableViewShebei->selectionModel();
    //获取被选中的指针列表
    QModelIndexList selected = selections->selectedIndexes();
    QList<int> rowList;
    QMap <int, int> rowMap;
    Q_FOREACH (QModelIndex index, selected) {
        rowMap.insert(index.row(), 0); //QModelIndex 有更多数据可用
        if(!rowList.contains(index.row()))
            rowList.append(index.row());
    }

    if (rowList.length()==1){
        selectedDeviceIndex=rowList[0];
        for (int i=0;i<modelShebei->rowCount();i++){
            modelShebei->setItem(i, 2, new QStandardItem("否"));
        }
        modelShebei->setItem(selectedDeviceIndex, 2, new QStandardItem("是"));
    } else {
        QMessageBox msgBox;   // 生成对象
        msgBox.setText("选择了多行或未选择，请选择1行");    // 设置文本
        msgBox.exec();  // 执行
        return;
    }

    qDebug()<<selectedDeviceIndex;
    selectedIp=modelShebei->item(selectedDeviceIndex,0)->text();
    qDebug()<<selectedIp;
}





