#include "oscilloscopeserial.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include <QThread>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

using namespace SoundTest;

OscilloscopeSerial::OscilloscopeSerial(Ui_WidgetSoundTest* ui)
    :Oscilloscope(ui)
{
    myPort = new QSerialPort;
}



void OscilloscopeSerial::start_shibo()
{

    if (myPort!=0 && myPort->isOpen()){
        myPort->clear();
        myPort->close();
        QThread::msleep(5);
    }

    int i,serialState=0;
    for (i=1;i<20;i++){
        myPort = new QSerialPort;
        QString portname="COM"+QString::number(i, 10);
        myPort->setPortName(portname);
        myPort->setBaudRate(QSerialPort::Baud115200); //设置波特率
        myPort->setParity(QSerialPort::NoParity);    //设置校验位
        myPort->setDataBits(QSerialPort::Data8);     //设置数据位
        myPort->setStopBits(QSerialPort::OneStop);   //设置停止位
        myPort->open(QIODevice::ReadWrite);
        if(myPort->isOpen()){

            // 接收数据，接收50次，里面有"start"则为需要的串口号
            QByteArray buffer1;
            while (buffer1.length() < 1024*4*4+10){
                if(!myPort->waitForReadyRead(10)){
                    //串口打开，但是不能建立握手
                    qDebug() << portname<<"串口打开，接收数据超时";
                    myPort->clear();
                    break;
                } else {
                    buffer1.append(myPort->readAll());
                }
            }
            QByteArray start("start");
            qDebug()<<"length of buffer1:"<<buffer1.length();
            int start_location=buffer1.indexOf(start);
            if(start_location==-1){
                qDebug() << portname<<"串口打开，但是不能建立握手";
                myPort->clear();
                continue;
            } else {
                // 正确建立连接
                qDebug()<<portname<<"串口打开成功";
                serialState=1;
                myPort->clear();
                break;
            }

        } else {
            // 串口没打开
            qDebug() << portname<<"串口未打开";
            myPort->clear();
            continue;
        }
    }

    // 没有能建立通信的串口
    if (i==20){
        qDebug()<<"没有能建立通信的串口";
        QMessageBox::information(NULL,  "Title",  "串口连接失败", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    if (serialState==1){
        //先建立信号槽
        connect(myPort,SIGNAL(readyRead()),this,SLOT(receiveData()));


        shiboLength=1024;

        // for (int i=0;i<length;i++){
        //     xlist[i]=i;
        //     ylist1[i]=qSin(2.0 * 3.141592 * i / 360.0);
        //     ylist2[i]=qSin(2.0 * 3.141592 * i / 360.0);
        //     ylist3[i]=qSin(2.0 * 3.141592 * i / 360.0);
        //     ylist4[i]=qSin(2.0 * 3.141592 * i / 360.0);
        // }

        // chart_plot(ui->graphicsView1,xlist,ylist1,length,"通道1","时间/s","声压/Pa");
        // chart_plot(ui->graphicsView2,xlist,ylist2,length,"通道2","时间/s","声压/Pa");
        // chart_plot(ui->graphicsView3,xlist,ylist3,length,"通道3","时间/s","声压/Pa");
        // chart_plot(ui->graphicsView4,xlist,ylist4,length,"通道4","时间/s","声压/Pa");
    }
}


//接收函数
void OscilloscopeSerial::receiveData()
{
    channel_buffer_one_step = myPort->readAll();

    channel_buffer.append(channel_buffer_one_step);
    if (channel_buffer.length() > 10000 * 100) {
        channel_buffer.clear();
    }

    QByteArray start("start");
    QByteArray end("end");
    int start_location=-1,end_location=-1;


    if(channel_buffer.length()>2*8*1024*2){
        start_location=channel_buffer.indexOf(start);
        qDebug()<<channel_buffer.mid(start_location, 18);
        end_location=channel_buffer.indexOf(end,start_location);
        qDebug()<<channel_buffer.mid(end_location-12, 18);
        int size=end_location-start_location-5;
        qDebug()<<"size:"<<size;
        data.append(channel_buffer.mid(start_location+5,size));
        qDebug()<<data.left(32);
        qDebug()<<data.right(32);
        channel_buffer.remove(0,end_location+3);
        qDebug()<<channel_buffer.left(15);

        // 提取通道数据
        for (int i=0;i<data.length();i++){
            if(i%16==0||i%16==1||i%16==2||i%16==3){
                ch1.append(data[i]);
            }
            if(i%16==4||i%16==5||i%16==6||i%16==7){
                ch2.append(data[i]);
            }
            if(i%16==8||i%16==9||i%16==10||i%16==11){
                ch3.append(data[i]);
            }
            if(i%16==12||i%16==13||i%16==14||i%16==15){
                ch4.append(data[i]);
            }
        }

        qDebug()<<"channel data:";
        qDebug()<<ch1.left(15);
        qDebug()<<ch2.left(15);
        qDebug()<<ch3.left(15);
        qDebug()<<ch4.left(15);

        // 通道数据绘图
        int* ch1_ptr=(int*)ch1.data();
        int* ch2_ptr=(int*)ch2.data();
        int* ch3_ptr=(int*)ch3.data();
        int* ch4_ptr=(int*)ch4.data();

        index1=ui->tableViewTongdao->model()->index(0,1);
        linmingdu1 = ui->tableViewTongdao->model()->data(index1).toString();
        index2=ui->tableViewTongdao->model()->index(0,2);
        danwei1 = ui->tableViewTongdao->model()->data(index2).toString();

        index3=ui->tableViewTongdao->model()->index(1,1);
        linmingdu2 = ui->tableViewTongdao->model()->data(index3).toString();
        index4=ui->tableViewTongdao->model()->index(1,2);
        danwei2 = ui->tableViewTongdao->model()->data(index4).toString();

        index5=ui->tableViewTongdao->model()->index(2,1);
        linmingdu3 = ui->tableViewTongdao->model()->data(index5).toString();
        index6=ui->tableViewTongdao->model()->index(2,2);
        danwei3 = ui->tableViewTongdao->model()->data(index6).toString();

        index7=ui->tableViewTongdao->model()->index(3,1);
        linmingdu4 = ui->tableViewTongdao->model()->data(index7).toString();
        index8=ui->tableViewTongdao->model()->index(3,2);
        danwei4 = ui->tableViewTongdao->model()->data(index8).toString();

        double m1=0,m2=0,m3=0,m4=0;
        for (int i=0;i<shiboLength;i++){
            m1+=ch1_ptr[i];
            m2+=ch2_ptr[i];
            m3+=ch3_ptr[i];
            m4+=ch4_ptr[i];
        }

        m1/=shiboLength;
        m2/=shiboLength;
        m3/=shiboLength;
        m4/=shiboLength;

        for (int i=0;i<shiboLength;i++){
            ch1_ptr[i]-=m1;
            ch2_ptr[i]-=m2;
            ch3_ptr[i]-=m3;
            ch4_ptr[i]-=m4;
        }

        for (int i=0;i<shiboLength;i++){
            xlist[i]=i*3.1250e-05;
            ylist1[i]=(ch1_ptr[i]/pow(2.0,24) * 4.1 * 2.0*1000.0)/50.0/linmingdu1.toDouble();   //1通道放大倍数取50
            ylist2[i]=ch2_ptr[i]/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu2.toDouble();
            ylist3[i]=ch3_ptr[i]/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu3.toDouble();
            ylist4[i]=ch4_ptr[i]/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu4.toDouble();
        }


        if (danwei1=="mV/Pa"){
            analysis->plotUtilsChannel1->chart_plot(&xlist, &ylist1, 1024,"通道1","时间/s","声压/Pa");
        }

        if (danwei2=="mV/Pa"){
            analysis->plotUtilsChannel2->chart_plot(&xlist, &ylist2, 1024,"通道2","时间/s","声压/Pa");
        }

        if (danwei3=="mV/Pa"){
            analysis->plotUtilsChannel3->chart_plot(&xlist, &ylist3, 1024,"通道3","时间/s","声压/Pa");
        }

        if (danwei4=="mV/Pa"){
            analysis->plotUtilsChannel4->chart_plot(&xlist, &ylist4, 1024,"通道4","时间/s","声压/Pa");
        }

        qDebug() << ylist4[0];

        ch1.clear();
        ch2.clear();
        ch3.clear();
        ch4.clear();
        data.clear();
    }
}



void OscilloscopeSerial::resetOscilloscope(){}
void OscilloscopeSerial::on_pushButtonCaiyang_clicked(){}
void OscilloscopeSerial::saveData(){}






