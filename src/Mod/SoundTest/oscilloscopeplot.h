#ifndef OSCILLOSCOPEPLOT_H
#define OSCILLOSCOPEPLOT_H

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QByteArray>
#include "analysis.h"
#include <QStandardItemModel>

namespace SoundTest {

typedef struct {
    unsigned char byte0;
    unsigned char byte1;
    unsigned char byte2;
} uint24;

class OscilloscopePlot: public QObject {
    Q_OBJECT
public:
    OscilloscopePlot();    
    Analysis* analysis; //分析对象
    // 示波数据，x轴和4通道y轴
    QList<double> *xlist,*ylist1,*ylist2,*ylist3,*ylist4;
    QList<double> *xlist_freq;
    QList<QList<double>*> *ylistlist_freq;

    // 灵敏度配置
    QString danwei1,danwei2,danwei3,danwei4;
    double d1,d2,d3,d4;
    int ploting=0;      //0-绘制完成  1-正在绘制
    int shiboLength;    // 示波长度
    int samplingRate;
    QByteArray ch1_2,ch2_2,ch3_2,ch4_2;
    int cntBlock_2;
    int connCount=0;

    int finish_celibrate=0;     //0 校准未完成，1 校准完成
    double d=1.0/pow(2.0,24) * 5 * 2.0*1000.0;

public Q_SLOTS:
    void plotData(int shiboState,int celiChannel);

};


} // namespace SoundTest
#endif // OSCILLOSCOPEPLOT_H
