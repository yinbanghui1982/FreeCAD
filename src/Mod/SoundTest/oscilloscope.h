/*
示波器
*/

#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QThread>
#include <QStandardItemModel>
#include "analysis.h"
#include "device.h"


namespace SoundTest {

class Ui_WidgetSoundTest;

//示波器，父类为线程
class Oscilloscope: public QThread
{
    Q_OBJECT

public:
    Oscilloscope(Ui_WidgetSoundTest* ui);
    virtual void start_shibo();
    Device* device;
    int shiboLength;    // 示波长度
    int shiboLengthIndex;
    Analysis* analysis; //分析对象
    virtual void resetOscilloscope();

    virtual void saveData();
    int samplingRate=128*1000;      //采样率，现在配置为128ksps
    int samplingLength;             //采样长度
    int samplingLengthIndex;
    int changedShiboLength=0;       //是否改变了示波长度，0未改变，1改变

    /*  示波器状态
     *  0 示波，需要反复采集示波
     *  1 采样，采集1次，显示一次
     *  2 传感器校准(示波)
     *  3 传感器校准（校准）
    */
    int shiboState=0;

    // 示波数据，x轴和4通道y轴
    QList<double> xlist,ylist1,ylist2,ylist3,ylist4;

    //是否停止示波
    int stopShibo;
    int celiChannel;
    QStringList* danweiList;

    // 设置AC/DC/IEPE
    virtual void setAcDcIepe(int channel,int index);

private Q_SLOTS:
    virtual void receiveData();

public Q_SLOTS:
    virtual void changeFs(int index);

protected:
    Ui_WidgetSoundTest* ui;

    // 灵敏度配置
    QModelIndex index1,index2,index3,index4,index5,index6,index7,index8;
    QString linmingdu1,linmingdu2,linmingdu3,linmingdu4;
    QString danwei1,danwei2,danwei3,danwei4;    

    // 接收数据
    QByteArray channel_buffer;   // 总的数据缓冲
    QByteArray channel_buffer_one_step;         // 每次接收到的数据
    QByteArray data;
    QByteArray ch1,ch2,ch3,ch4;

    void run() override;


Q_SIGNALS:
    void sig_finish_caiyang();

};


} // namespace SoundTest
#endif // OSCILLOSCOPE_H
