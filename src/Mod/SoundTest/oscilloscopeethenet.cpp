#include "oscilloscopeethenet.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDataStream>

using namespace SoundTest;

OscilloscopeEthenet::OscilloscopeEthenet(Ui_WidgetSoundTest* ui, QStringList* danweiList)
    :Oscilloscope(ui)
{

    // oscilloscopePlot->moveToThread(plotThread);
    // connect(plotThread, &QThread::finished, oscilloscopePlot, &QObject::deleteLater);
    // connect(this,&OscilloscopeEthenet::startPlotData, oscilloscopePlot,&OscilloscopePlot::plotData);
    // plotThread->start();
    // oscilloscopePlot->xlist=&xlist;
    // oscilloscopePlot->ylist1=&ylist1;
    // oscilloscopePlot->ylist2=&ylist2;
    // oscilloscopePlot->ylist3=&ylist3;
    // oscilloscopePlot->ylist4=&ylist4;

    stopShibo=0;
    this->danweiList=danweiList;

    datax = "";

}


/*开始进行示波*/
void OscilloscopeEthenet::start_shibo()
{
    stopShibo=0;
    // shiboState=0;

    qDebug() << device->selectedIp;
    socket = new QTcpSocket();
    socket->connectToHost(device->selectedIp, 7);       //端口为7
    creat_socket=1;

    //等待连接成功
    if(!socket->waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        return;
    }
    qDebug() << "Connect successfully!";
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()),Qt::QueuedConnection);
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()));


    // 开始进行数据传输
    xlist.clear();
    ylist1.clear();
    ylist2.clear();
    ylist3.clear();
    ylist4.clear();

    xlist.resize(shiboLength);
    ylist1.resize(shiboLength);
    ylist2.resize(shiboLength);
    ylist3.resize(shiboLength);
    ylist4.resize(shiboLength);

    changedShiboLength=0;
    startOscilloscope();



    index1=ui->tableViewTongdao->model()->index(0,1);
    linmingdu1 = ui->tableViewTongdao->model()->data(index1).toString();
    // index2=ui->tableViewTongdao->model()->index(0,2);
    // danwei1 = ui->tableViewTongdao->model()->data(index2).toString();
    index_danwei = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(0, 2))))->currentIndex();
    danwei1=(*danweiList)[index_danwei];

    index3=ui->tableViewTongdao->model()->index(1,1);
    linmingdu2 = ui->tableViewTongdao->model()->data(index3).toString();
    // index4=ui->tableViewTongdao->model()->index(1,2);
    // danwei2 = ui->tableViewTongdao->model()->data(index4).toString();
    index_danwei = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(1, 2))))->currentIndex();
    danwei2=(*danweiList)[index_danwei];

    index5=ui->tableViewTongdao->model()->index(2,1);
    linmingdu3 = ui->tableViewTongdao->model()->data(index5).toString();
    // index6=ui->tableViewTongdao->model()->index(2,2);
    // danwei3 = ui->tableViewTongdao->model()->data(index6).toString();
    index_danwei = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(2, 2))))->currentIndex();
    danwei3=(*danweiList)[index_danwei];

    index7=ui->tableViewTongdao->model()->index(3,1);
    linmingdu4 = ui->tableViewTongdao->model()->data(index7).toString();
    // index8=ui->tableViewTongdao->model()->index(3,2);
    // danwei4 = ui->tableViewTongdao->model()->data(index8).toString();
    index_danwei = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(3, 2))))->currentIndex();
    danwei4=(*danweiList)[index_danwei];

    // d1=1.0/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu1.toDouble();
    // d2=1.0/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu2.toDouble();
    // d3=1.0/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu3.toDouble();
    // d4=1.0/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu4.toDouble();

    d1=1/linmingdu1.toDouble();
    d2=1/linmingdu2.toDouble();
    d3=1/linmingdu3.toDouble();
    d4=1/linmingdu4.toDouble();

    oscilloscopePlot->danwei1=danwei1;
    oscilloscopePlot->danwei2=danwei2;
    oscilloscopePlot->danwei3=danwei3;
    oscilloscopePlot->danwei4=danwei4;

    analysis->danWeiList[0]=danwei1;
    analysis->danWeiList[1]=danwei2;
    analysis->danWeiList[2]=danwei3;
    analysis->danWeiList[3]=danwei4;

    oscilloscopePlot->d1=d1;
    oscilloscopePlot->d2=d2;
    oscilloscopePlot->d3=d3;
    oscilloscopePlot->d4=d4;

    oscilloscopePlot->shiboLength=shiboLength;
    oscilloscopePlot->samplingRate=samplingRate;
    oscilloscopePlot->analysis=analysis;
}


/*接收函数
不断接收数据，不断更新图像
每次接收1k byte，接收16次之后，再将接收到的数据拼起来。
*/
void OscilloscopeEthenet::receiveData()
{
    qDebug()<<"start receive data:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
    while(receivedata_running==1){}
    receivedata_running=1;
    qDebug()<<"end recerve data waiting:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
    if(changedShiboLength==1){
        changedShiboLength=0;
        receivedata_running=0;
        return;
    }

    channel_buffer_one_step = socket->readAll();
    // qDebug()<<channel_buffer_one_step;


    if(channel_buffer_one_step[0]=='s' && channel_buffer_one_step[1]=='o'){     // 开始采集发送完毕
        socket->write("ss",2);      //start sample，开始采集
        receivedata_running=0;
        return;
    }

    if(channel_buffer_one_step.count()==1 && channel_buffer_one_step[0]=='b'){  //读超过写
        socket->write("a",1);
        qDebug()<<"read cross write";
        receivedata_running=0;
        return;
    }

    // if (countReceive<100){
    //     channel_buffer.append(channel_buffer_one_step);
    //     qDebug()<<countReceive<<":"<<channel_buffer.size();
    //     countReceive++;
    //     receivedata_running=0;
    //     return;
    // }

    channel_buffer.append(channel_buffer_one_step);

    // 1024点数据，1k*4*4=16k

    if (countTcp<15){
        socket->write("a",1);
        countTcp++;
        qDebug()<<"a";
    } else if (countTcp==15) {

        // 提取通道数据，1个通道数据24位，3字节，还有1字节为0
        qDebug()<<"start copy data from channel_buffer to ch1-4:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
        for (int i=0;i<channel_buffer.length();i++){
            if(i%16==0||i%16==1||i%16==2||i%16==3){
                ch1.append(channel_buffer[i]);
            }
            if(i%16==4||i%16==5||i%16==6||i%16==7){
                ch2.append(channel_buffer[i]);
            }
            if(i%16==8||i%16==9||i%16==10||i%16==11){
                ch3.append(channel_buffer[i]);
            }
            if(i%16==12||i%16==13||i%16==14||i%16==15){
                ch4.append(channel_buffer[i]);
            }
        }
        qDebug()<<"end copy data from channel_buffer to ch1-4:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
        channel_buffer.clear();

        countTcp=0;
        countBlock++;

        if (countBlock<shiboLength/1024){         //获取最后一块数据之前的数据
            if (shiboState==1){   //采集
                if (countShibo==100){
                    if (oscilloscopePlot->ploting==0)
                        plotData2();
                    countShibo=0;
                } else {
                    countShibo++;
                }
            }

            socket->write("a",1);
        } else {                                    //最后一块数据
            qDebug()<<"ch1.size:"<<ch1.size();

            qDebug()<<"start plot time:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
            if (oscilloscopePlot->ploting==0)       //如果绘制完成，则进行绘制
            {
                plotData2();
                qDebug()<<"plot";
            }
            qDebug()<<"finish plot time:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");

            if (shiboState==0){
                startOscilloscope();
            } else if (shiboState==1){
                qDebug() << "start save data";
                if(shiboLength<=8192){
                    QThread::msleep(100);
                    saveData();
                } else {
                    saveDataBit();
                }
                qDebug() << "end save data";
            }
        }
    }
    qDebug()<<"end receive data:" << QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s.zzz");
    receivedata_running=0;
}


// 绘制图形
void OscilloscopeEthenet::plotData2(){
    qDebug() << "plotData2";

    // oscilloscopePlot->ch1_2=QByteArray::fromRawData(ch1.data(),ch1.size());
    // oscilloscopePlot->ch2_2=QByteArray::fromRawData(ch2.data(),ch2.size());
    // oscilloscopePlot->ch3_2=QByteArray::fromRawData(ch3.data(),ch3.size());
    // oscilloscopePlot->ch4_2=QByteArray::fromRawData(ch4.data(),ch4.size());

    int size1=ch1.size();
    int size2=ch2.size();
    int size3=ch3.size();
    int size4=ch4.size();

    oscilloscopePlot->ch1_2.resize(size1);
    oscilloscopePlot->ch2_2.resize(size2);
    oscilloscopePlot->ch3_2.resize(size3);
    oscilloscopePlot->ch4_2.resize(size4);

    for (int i=0;i<ch1.size();i++){
        oscilloscopePlot->ch1_2[i]=ch1[i];
        oscilloscopePlot->ch2_2[i]=ch2[i];
        oscilloscopePlot->ch3_2[i]=ch3[i];
        oscilloscopePlot->ch4_2[i]=ch4[i];
    }


    oscilloscopePlot->cntBlock_2=countBlock;

    // Q_EMIT this->startPlotData();
    oscilloscopePlot->ploting=1;
    send_sig=1;
    // Q_EMIT this->startPlotData(2);
    // QMetaObject::invokeMethod(this, "startPlotData", Qt::QueuedConnection, Q_ARG(int, 2000));
}

// 开始示波
void OscilloscopeEthenet::startOscilloscope(){    
    channel_buffer.clear();
    ch1.clear();
    ch2.clear();
    ch3.clear();
    ch4.clear();
    countTcp=0;
    countBlock=0;

    // s表示start,s1,s2,s3...
    if(stopShibo==0){
        char send_chars[2];
        send_chars[0]='s';
        send_chars[1]=shiboLengthIndex+49;
        socket->write(send_chars,2);
    }
}

// 保存数据
void OscilloscopeEthenet:: saveData(){
    qDebug() << "save data 1";
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyyMMddhhmmss");
    QFile file("./data/"+formattedTime+".xml");
    file.open(QFile::WriteOnly | QFile::Truncate);
    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("chnnels");

    qDebug() << "save data 2";

    // 时间数据
    // QString datax="";
    datax.clear();

    // QList<QString> dataList;
    // QString datay1,datay2,datay3,datay4;
    datay1.clear();
    datay2.clear();
    datay3.clear();
    datay4.clear();

    for (int i=0;i<samplingLength;i++){
        if (i%1000==0)
            qDebug() << i;

        if (i!=samplingLength-1){
            datax=datax+QString::number(xlist[i])+",";

            if(datax.startsWith("0,0")){
                int j=0;
            }

            datay1=datay1+QString::number(ylist1[i])+",";
            datay2=datay2+QString::number(ylist2[i])+",";
            datay3=datay3+QString::number(ylist3[i])+",";
            datay4=datay4+QString::number(ylist4[i])+",";
        }else{
            datax=datax+QString::number(xlist[i]);
            datay1=datay1+QString::number(ylist1[i]);
            datay2=datay2+QString::number(ylist2[i]);
            datay3=datay3+QString::number(ylist3[i]);
            datay4=datay4+QString::number(ylist4[i]);
        }
    }

    // double* datax_double=xlist.data();
    // QByteArray array = QByteArray::fromRawData(reinterpret_cast<char*>(datax_double),samplingLength*sizeof(double));

    qDebug() << "save data 3";

    // datax=formattedTime+"_datax.dat";
    // datay1=formattedTime+"_datay1.dat";
    // datay2=formattedTime+"_datay2.dat";
    // datay3=formattedTime+"_datay3.dat";
    // datay4=formattedTime+"_datay4.dat";

    dataList.append(datay1);
    dataList.append(datay2);
    dataList.append(datay3);
    dataList.append(datay4);

    stream.writeTextElement("time",datax);

    if(datax.startsWith("0,0")){
        int j=0;
    }


    // 通道数据
    for(int i=0;i<4;i++){
        stream.writeStartElement("channel");
        stream.writeAttribute("id", QString::number(i+1));
        stream.writeTextElement("data",dataList[i]);
        // stream.writeEndElement();
        if (i==0){
            if (danwei1=="mV/mV")
                stream.writeTextElement("unit","Voltage/mV");
            else if (danwei1=="mV/Pa")
                stream.writeTextElement("unit","Sound Pressure/Pa");
            else if (danwei1=="mV/(m/s^2)")
                stream.writeTextElement("unit","Acceleration/(m/s^2)");
        }
        else if (i==1){
            if (danwei2=="mV/mV")
                stream.writeTextElement("unit","Voltage/mV");
            else if (danwei2=="mV/Pa")
                stream.writeTextElement("unit","Sound Pressure/Pa");
            else if (danwei2=="mV/(m/s^2)")
                stream.writeTextElement("unit","Acceleration/(m/s^2)");
        }
        else if (i==2){
            if (danwei3=="mV/mV")
                stream.writeTextElement("unit","Voltage/mV");
            else if (danwei3=="mV/Pa")
                stream.writeTextElement("unit","Sound Pressure/Pa");
            else if (danwei3=="mV/(m/s^2)")
                stream.writeTextElement("unit","Acceleration/(m/s^2)");
        }
        else if (i==3){
            if (danwei4=="mV/mV")
                stream.writeTextElement("unit","Voltage/mV");
            else if (danwei4=="mV/Pa")
                stream.writeTextElement("unit","Sound Pressure/Pa");
            else if (danwei4=="mV/(m/s^2)")
                stream.writeTextElement("unit","Acceleration/(m/s^2)");
        }

        stream.writeEndElement();
    }

    qDebug() << "save data 4";

    stream.writeEndElement();
    stream.writeEndDocument();

    file.close();
    dataList.clear();

    //QMessageBox::information(NULL,  "Title",  "采样完成", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    Q_EMIT sig_finish_caiyang();
}


void OscilloscopeEthenet:: saveDataBit(){
    qDebug() << "save data 1";
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyyMMddhhmmss");
    QFile file("./data/"+formattedTime+".bit");
    file.open(QFile::WriteOnly | QFile::Truncate);

    QByteArray qByteArray;

    QByteArray lengthArray = QByteArray::fromRawData(reinterpret_cast<char*>(&samplingLength),sizeof(int));
    qByteArray.append(lengthArray);

    QByteArray samplingRateArray = QByteArray::fromRawData(reinterpret_cast<char*>(&samplingRate),sizeof(int));
    qByteArray.append(samplingRateArray);

    // double* datax_double=xlist.data();
    // QByteArray dataxArray = QByteArray::fromRawData(reinterpret_cast<char*>(datax_double),samplingLength*sizeof(double));
    // fileArray.append(dataxArray);

    // double* ylist1_double=ylist1.data();
    // QByteArray ylist1Array = QByteArray::fromRawData(reinterpret_cast<char*>(ylist1_double),samplingLength*sizeof(double));
    // fileArray.append(ylist1Array);

    // double* ylist2_double=ylist2.data();
    // QByteArray ylist2Array = QByteArray::fromRawData(reinterpret_cast<char*>(ylist2_double),samplingLength*sizeof(double));
    // fileArray.append(ylist2Array);

    // double* ylist3_double=ylist3.data();
    // QByteArray ylist3Array = QByteArray::fromRawData(reinterpret_cast<char*>(ylist3_double),samplingLength*sizeof(double));
    // fileArray.append(ylist3Array);

    // double* ylist4_double=ylist4.data();
    // QByteArray ylist4Array = QByteArray::fromRawData(reinterpret_cast<char*>(ylist4_double),samplingLength*sizeof(double));
    // fileArray.append(ylist4Array);

    qByteArray.append(ch1);
    qByteArray.append(ch2);
    qByteArray.append(ch3);
    qByteArray.append(ch4);


    QDataStream out(&file);
    out<<qByteArray;

    file.close();
    QMessageBox::information(NULL,  "Title",  "采样完成", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}

//绘图线程
void OscilloscopeEthenet::run(){    
    // shiboState=0;
    // qDebug() <<device->selectedIp;
    // socket = new QTcpSocket();
    // socket->connectToHost(device->selectedIp, 7);       //端口为7

    // //等待连接成功
    // if(!socket->waitForConnected(3000))
    // {
    //     qDebug() << "Connection failed!";
    //     // return;
    // }
    // qDebug() << "Connect successfully!";
    // connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()),Qt::QueuedConnection);
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()));

    while(true){
        // if(creat_socket==1){
        //     if(socket->waitForReadyRead(3000)) {
        //         receiveData();
        //     }
        // }

        if (send_sig==1){
            if (cnt_send==50){                
                Q_EMIT this->sig_plot_data(shiboState,celiChannel);
                qDebug()<<"Q_EMIT this->startPlotData";
                send_sig=0;
                cnt_send=0;
            } else{
                cnt_send++;
            }

        }

        //完成校准
        if (this->oscilloscopePlot->finish_celibrate==1){
            this->oscilloscopePlot->finish_celibrate=0;
            Q_EMIT this->sig_finish_celibrate();

        }

    }
}

void OscilloscopeEthenet::changeFs(int index)
{
    newSocket();

    char send_chars[2];
    send_chars[0]='f';
    send_chars[1]=index+48;
    socket->write(send_chars,2);

    if (index==0)
        samplingRate=128*1000;
    else if (index==1)
        samplingRate=64*1000;
    else if (index==2)
        samplingRate=32*1000;
    else if (index==3)
        samplingRate=16*1000;
    else if (index==4)
        samplingRate=8*1000;
    else if (index==5)
        samplingRate=4*1000;
    else if (index==6)
        samplingRate=2*1000;
    else if (index==7)
        samplingRate=1*1000;
}


void OscilloscopeEthenet::setAcDcIepe(int channel,int index)
{
    newSocket();
    char send_chars[3];
    send_chars[0]='c';
    send_chars[1]=channel+48;
    send_chars[2]=index+48;
    socket->write(send_chars,3);
}

void OscilloscopeEthenet::newSocket()
{
    socket = new QTcpSocket();
    socket->connectToHost(device->selectedIp, 7);       //端口为7
    creat_socket=1;

    //等待连接成功
    if(!socket->waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        return;
    }
    qDebug() << "Connect successfully!";
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()),Qt::QueuedConnection);
    // connect(this, SIGNAL(startPlotData()), this, SLOT(plotData()));
}




