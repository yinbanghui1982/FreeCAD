#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <QStandardItemModel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QSerialPort>
#include <QSerialPortInfo>


namespace SoundTest {

class Ui_WidgetSoundTest;
class InputData
{
public:
    InputData(QWidget *parent,Ui_WidgetSoundTest* ui);
    int readDataFile();
    int* length;
    QList<double>* xlist;
    QList<QList<double>*> *ylistList;
    QList<QString>* channelUnitList;


private:
    QWidget *parent;
    Ui_WidgetSoundTest* ui;

    void readXmlDataFile();
    void readTdmsDataFile();
    void errorMessage();

    QList<QString> channelNameList;
    QList<QString> channelDataList;    
    QList<double> ylist1_time,ylist2_time,ylist3_time,ylist4_time;

    QStringList* timeStrList;
    QStringList* channelDataListArray[4];

    QStringList* qStringList;
    QString str_file;
    void split_str(QStringList* qStringList,QString str_file,char c);

    QList<double> data2;
    QList<char> ch1,ch2,ch3,ch4;

    void readBitDataFile();
    void int2double();
    int* sampling_length;
    int* sampling_rate;
    int *ch1_int,*ch2_int,*ch3_int,*ch4_int;

    QFile* file;
    std::string fileName;


};

} // namespace SoundTest
#endif // INPUTDATA_H
