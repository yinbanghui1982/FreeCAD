#include "inputdata.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QWidget>
#include <QtWidgets>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVector>
#include "libtdms-gpl-0.5/include/TdmsParser.h"
#include "libtdms-gpl-0.5/include/TdmsGroup.h"
#include "libtdms-gpl-0.5/include/TdmsChannel.h"
#include <math.h>
#include <string.h>
#include <cstdlib>

using namespace SoundTest;

InputData::InputData(QWidget *parent,Ui_WidgetSoundTest* ui) {
    this->parent=parent;
    this->ui=ui;
}

int InputData::readDataFile(){
    this->length=length;
    this->xlist=xlist;
    this->ylistList=ylistList;

    for (int i=0;i<ylistList->length();i++)
        (*ylistList)[i]->clear();
    // ylistList->clear();

    str_file = QFileDialog::getOpenFileName(parent, "打开", "data","XML 文件(*.xml);;tdms文件(*.tdms);;bit文件(*.bit);;All file(*.*)");
    qDebug() << str_file;
    if (str_file=="")
        return -1;

    file=new QFile(str_file);
    if (!file->open(QIODevice::ReadOnly))
        return -1;

    qStringList=new QStringList();
    // qStringList=str_file.split(".");
    split_str(qStringList,str_file,'.');

    if((*qStringList)[1]=="xml"){
        readXmlDataFile();
    } else if((*qStringList)[1]=="tdms"){
        QByteArray byteArray = str_file.toUtf8();
        std::string str2="";
        for (int i=0;i<byteArray.length();i++){
            str2=str2+byteArray[i];
        }
        fileName=str2;
        readTdmsDataFile();
    } else if((*qStringList)[1]=="bit"){
        readBitDataFile();
    }

    return 0;
}


void InputData::split_str(QStringList* qStringList,QString str_file, char c){
    qStringList->clear();
    int cnt=str_file.length();
    int i;
    int l=0;
    for (i=0;i<cnt;i++){
        if (str_file[i]==c){
            qStringList->append(str_file.mid(l,i-l));
            l=i+1;
        }
    }

    qStringList->append(str_file.mid(l,cnt-l));
    // QStringList s=str_file.split(".");
    // QString s="sdf";
    // qStringList->append(s);
}


void InputData::readXmlDataFile(){
    channelNameList.clear();
    channelDataList.clear();

    QXmlStreamReader reader(file);
    QString time;

    bool startChannel=false,startTime=false;

    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType type=reader.readNext();
        if(type==QXmlStreamReader::StartElement && reader.name().toString()=="time")
        {
            startTime=true;
        }

        if(startTime==true && type==QXmlStreamReader::Characters)
        {
            time=reader.text().toString();
            startTime=false;
        }

        if(type==QXmlStreamReader::StartElement && reader.name().toString()=="channel")
        {
            //channel name
            Q_FOREACH (const QXmlStreamAttribute & attribute, reader.attributes())
            {
                qDebug()<<attribute.name();
                qDebug()<<attribute.value();
                channelNameList.append(attribute.value().toString());
            }

            // channel data
            while(!reader.atEnd()) {
                QXmlStreamReader::TokenType type2=reader.readNext();

                if(type2==QXmlStreamReader::StartElement && reader.name().toString()=="data")
                {
                    startChannel=true;
                }
                if(startChannel==true && type2==QXmlStreamReader::Characters)
                {
                    qDebug()<<reader.text().toString();
                    channelDataList.append(reader.text().toString());
                }

                if(type2==QXmlStreamReader::EndElement){
                    startChannel=false;
                    break;
                }
            }

            // channel unit
            while(!reader.atEnd()) {
                QXmlStreamReader::TokenType type2=reader.readNext();

                if(type2==QXmlStreamReader::StartElement && reader.name().toString()=="unit")
                {
                    startChannel=true;
                }
                if(startChannel==true && type2==QXmlStreamReader::Characters)
                {
                    qDebug()<<reader.text().toString();
                    channelUnitList->append(reader.text().toString());
                }

                if(type2==QXmlStreamReader::EndElement){
                    startChannel=false;
                    break;
                }
            }


        }
    }
    if (reader.hasError())
    {
        qDebug()<<reader.errorString();
    }

    //解析时间数据
    timeStrList=new QStringList();
    split_str(timeStrList,time,',');
    // timeStrList=time.split(",");

    // 解析通道数据
    for(int i=0;i<4;i++){
        channelDataListArray[i]=new QStringList();
        split_str(channelDataListArray[i],channelDataList[i],',');
        // channelDataListArray[i]=channelDataList[i].split(",");
    }

    *length=(*timeStrList).length();

    ylist1_time.resize(*length);
    ylist2_time.resize(*length);
    ylist3_time.resize(*length);
    ylist4_time.resize(*length);

    xlist->clear();
    for(int i=0;i<*length;i++){
        xlist->append((*timeStrList)[i].toDouble());
        ylist1_time[i]=(*channelDataListArray[0])[i].toDouble();
        ylist2_time[i]=(*channelDataListArray[1])[i].toDouble();
        ylist3_time[i]=(*channelDataListArray[2])[i].toDouble();
        ylist4_time[i]=(*channelDataListArray[3])[i].toDouble();
    }

    qDebug()<<(*xlist)[1];
    qDebug()<<ylist1_time[1];
    qDebug()<<ylist2_time[1];

    // for (int i=0;i<ylistList->size();i++){
    //     (*ylistList)[i].clear();
    // }
    // ylistList->resize(4);

    // ylistList->append(ylist1_time);
    // ylistList->append(ylist2_time);
    // ylistList->append(ylist3_time);
    // ylistList->append(ylist4_time);

    (*ylistList)[0]=&ylist1_time;
    (*ylistList)[1]=&ylist2_time;
    (*ylistList)[2]=&ylist3_time;
    (*ylistList)[3]=&ylist4_time;

    file->close();
}

void InputData::errorMessage()
{
    std::cout << "\nInput error: please provide a single valid *.tdms file name!" << std::endl;
}
// 分组/通道
void InputData::readTdmsDataFile(){
    qDebug() << "start tdms:"<<fileName;
    xlist->clear();

    bool verbose = false, storeValues = true, showProperties = false;
    TdmsParser parser(fileName, storeValues);
    if (parser.fileOpeningError()){
        errorMessage();
        return;
    }

    parser.read(verbose);

    unsigned int groupCount = parser.getGroupCount();
    printf("\nNumber of groups: %d\n", groupCount);
    for (unsigned int i = 0; i < groupCount; i++){
        TdmsGroup *group = parser.getGroup(i);
        if (!group)
            continue;

        unsigned int channelsCount = group->getGroupSize();
        if (channelsCount)
            printf("\nGroup %s (%d/%d) has %d channels:\n\n", group->getName().c_str(), i + 1, groupCount, channelsCount);
        else
            printf("\nGroup %s (%d/%d) has 0 channels.\n", group->getName().c_str(), i + 1, groupCount);

        // 按通道循环
        for (unsigned int j = 0; j < channelsCount; j++){
            TdmsChannel *ch = group->getChannel(j);
            if (ch){
                unsigned long long dataCount = ch->getDataCount(), stringCount = ch->getStringCount();
                unsigned long long dataSize = (dataCount > 0) ? dataCount : stringCount;
                string unit = ch->getUnit();        //单位
                std::string s=ch->getProperty("wf_increment");
                printf("increment:%s\n",s.c_str());
                double increment = std::stod(s);    //采样周期

                if (unit.empty())
                    printf("%d) Channel %s has %lld values\n", j + 1, ch->getName().c_str(), dataSize);
                else
                    printf("%d) Channel %s (unit: %s) has %lld values\n", j + 1, ch->getName().c_str(), unit.c_str(), dataSize);

                unsigned int type = ch->getDataType();

                if (dataCount){
                    std::vector<double> data = ch->getDataVector();
                    double* data_ptr=data.data();
                    // QList<double> data2;
                    data2.resize(data.size());
                    (*(*ylistList)[j]).resize(data.size());
                    for (int k=0;k<data.size();k++){    //按通道长度循环
                        data2[k]=data[k];
                        if (j==0){
                            xlist->append(k*increment);                            
                        }
                        (*(*ylistList)[j])[k]=data[k];
                    }
                    // ylistList->append(&data2);
                    // (*ylistList)[j]=&data2;
                    *length=data.size();

                    printf("\tdata size is: %d\n",data.size());
                    if ((type == TdmsChannel::tdsTypeComplexSingleFloat) || (type == TdmsChannel::tdsTypeComplexDoubleFloat)){
                        std::vector<double> imData = ch->getImaginaryDataVector();
                        if (!imData.empty()){
                            double iVal1 = imData.front(), iVal2 = imData.back();
                            std::string fmt = "\t%g";
                            fmt.append((iVal1 < 0) ? "-i*%g ... %g" : "+i*%g ... %g");
                            fmt.append((iVal2 < 0) ? "-i*%g\n" : "+i*%g\n");
                            printf(fmt.c_str(), data.front(), fabs(iVal1), data.back(), fabs(iVal2));
                        }
                    } else {
                        if (!data.empty())
                            printf("\t[begin...end]: %g ... %g\n", data.front(), data.back());

                        printf("\t[min...max]: %g ... %g\n", ch->getMinDataValue(), ch->getMaxDataValue());

                        if (dataCount)
                            printf("\taverage data value: %g\n", ch->getDataSum()/dataCount);
                    }
                } else if (stringCount){
                    std::vector<std::string> strings = ch->getStringVector();
                    if (!strings.empty()){
                        string str1 = strings.front();
                        if (str1.empty())
                            str1 = "empty string";
                        string str2 = strings.back();
                        if (str2.empty())
                            str2 = "empty string";
                        printf(":\n\t%s ... %s\n", str1.c_str(), str2.c_str());
                    }
                }

                if (showProperties)
                    printf("and %d properties:\n%s\n", ch->getPropertyCount(), ch->propertiesToString().c_str());

                if (storeValues)
                    ch->freeMemory();
            }
        }
    }

    printf("\nSuccessfully parsed file '%s' (size: %lld bytes).\n", fileName.c_str(), parser.fileSize());
    printf("Done!\n");
}


void InputData::readBitDataFile(){
    QString str;
    qint32 qin;
    QDataStream stream(file);
    // qint32 int0,samplingLength,samplingRate;
    // stream>>int0>>samplingLength>>samplingRate;

    qDebug()<<"input 1:" << QDateTime::currentDateTime().toString("hh:mm:ss");

    stream.skipRawData(4);//跳过40个字节
    char ch_sampling_length[4];
    stream.readRawData(ch_sampling_length,4);//读取数据
    sampling_length=(int*)ch_sampling_length;
    // int sampling_length=atoi(ch_sampling_length);

    char ch_sampling_rate[4];
    stream.readRawData(ch_sampling_rate,4);//读取数据
    sampling_rate=(int*)ch_sampling_rate;
    // int sampling_rate=atoi(ch_sampling_rate);
    // qDebug()<<ch_sampling_length;

    int i,j;
    // char* ch1=new char(4*(*sampling_length));
    // char* ch2=new char(4*(*sampling_length));
    // char* ch3=new char(4*(*sampling_length));
    // char* ch4=new char(4*(*sampling_length));

    ch1.resize(4*(*sampling_length));
    ch2.resize(4*(*sampling_length));
    ch3.resize(4*(*sampling_length));
    ch4.resize(4*(*sampling_length));

    stream.readRawData(ch1.data(),4*(*sampling_length));
    stream.readRawData(ch2.data(),4*(*sampling_length));
    stream.readRawData(ch3.data(),4*(*sampling_length));
    stream.readRawData(ch4.data(),4*(*sampling_length));

    xlist->clear();
    *length=*sampling_length;
    xlist->resize(*length);
    ylistList->resize(4);
    (*ylistList)[0]->resize(*length);
    (*ylistList)[1]->resize(*length);
    (*ylistList)[2]->resize(*length);
    (*ylistList)[3]->resize(*length);


    ch1_int=(int*)ch1.data();
    ch2_int=(int*)ch2.data();
    ch3_int=(int*)ch3.data();
    ch4_int=(int*)ch4.data();

    qDebug()<<"input 2:" << QDateTime::currentDateTime().toString("hh:mm:ss");

    int2double();

    qDebug()<<"input 3:" << QDateTime::currentDateTime().toString("hh:mm:ss");
    file->close();

}

void InputData::int2double(){
    qDebug()<<"input 4:" << QDateTime::currentDateTime().toString("hh:mm:ss");
    int i;
    for (i=0;i<*sampling_length;i++){
        (*xlist)[i]=1.0*i/(*sampling_rate);
    }

    qDebug()<<"input 5:" << QDateTime::currentDateTime().toString("hh:mm:ss");

    // double m1=0,m2=0,m3=0,m4=0;
    // for (int i=0;i<*sampling_length;i++){
    //     m1+=ch1_int[i]/(*sampling_length);
    //     m2+=ch2_int[i]/(*sampling_length);
    //     m3+=ch3_int[i]/(*sampling_length);
    //     m4+=ch4_int[i]/(*sampling_length);
    // }

    // for (int i=0;i<*sampling_length;i++){
    //     (*(*ylistList)[0])[i]=ch1_int[i]-m1;
    //     (*(*ylistList)[1])[i]=ch2_int[i]-m2;
    //     (*(*ylistList)[2])[i]=ch3_int[i]-m3;
    //     (*(*ylistList)[3])[i]=ch4_int[i]-m4;
    // }

    // 灵敏度配置
    QModelIndex index1,index2,index3,index4,index5,index6,index7,index8;
    QString linmingdu1,linmingdu2,linmingdu3,linmingdu4;
    QString danwei1,danwei2,danwei3,danwei4;

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

    qDebug()<<"input 6:" << QDateTime::currentDateTime().toString("hh:mm:ss");
    double a1=1/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu1.toDouble();
    double a2=1/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu2.toDouble();
    double a3=1/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu3.toDouble();
    double a4=1/pow(2.0,24) * 4.1 * 2.0*1000.0/linmingdu4.toDouble();

    for (int i=0;i<*sampling_length;i++){
        (*(*ylistList)[0])[i]=ch1_int[i]*a1;
        (*(*ylistList)[1])[i]=ch2_int[i]*a2;
        (*(*ylistList)[2])[i]=ch3_int[i]*a3;
        (*(*ylistList)[3])[i]=ch4_int[i]*a4;
    }

    qDebug()<<"input 7:" << QDateTime::currentDateTime().toString("hh:mm:ss");

}









