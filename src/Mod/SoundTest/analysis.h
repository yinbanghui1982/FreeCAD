#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <QList>
#include "plotutils.h"

/*
Analysis->Model,ModelView
PlotUtils->View

*/


namespace SoundTest {

class Ui_WidgetSoundTest;
class Analysis
{
public:
    Analysis(Ui_WidgetSoundTest* ui);

    // 画图控件
    PlotUtils* plotUtilsChannel1;       //4个通道的示波控件
    PlotUtils* plotUtilsChannel2;
    PlotUtils* plotUtilsChannel3;
    PlotUtils* plotUtilsChannel4;
    PlotUtils* plotUtilsTime;           //时域分析
    PlotUtils* plotUtilsFreq;           //频域分析
    PlotUtils* plotUtilsPsd;            //自功率谱密度分析
    PlotUtils* plotUtilsCpsd1;          //互功率谱密度分析
    PlotUtils* plotUtilsCpsd2;
    PlotUtils* plotUtilsCorr;           //自相关分析
    PlotUtils* plotUtilsXcorr;          //互相关分析
    PlotUtils* plotUtilsOneThird;       //1/3倍频程分析
    PlotUtils* plotUtilsDaopu;          //倒谱分析

    PlotUtils* plotUtilsCeliTime;
    PlotUtils* plotUtilsCeliFreq;

    // 时域分析数据
    int length_time;
    QList<double> *xlist_time;
    QList<QList<double>*> *ylistlist_time;
    QList<double> *xlist_time_step;
    QList<QList<double>*> *ylistlist_time_step;
    int step_start=0;
    int step_length=1024;
    void timeAnalysis(int channel);
    QString channelNames[4];
    void on_pushButtonShowShuxian_clicked();
    int channel=0;
    int state_time=0;       //0 时域分析，1 校准里面的时域分析
    QList<QString>* channelUnitList_time;

    // 频域分析数据
    int state_freq=0;       //0 频域分析，1 校准里面的频域分析
    int length_freq;
    QList<double> *xlist_freq;
    QList<QList<double>*> *ylistlist_freq;
    void freqAnalysis(int channel);
    QList<double> xl_freq,yl_freq;
    QList<QString>* channelUnitList_freq;

    // 自功率谱密度分析数据
    int length_psd;
    QList<double> *xlist_psd;
    QList<QList<double>*> *ylistlist_psd;
    void psdAnalysis(int channel);
    QList<double> xl_psd,yl_psd;
    QList<QString>* channelUnitList_psd;

    // 互功率谱密度分析数据
    int length_cpsd;
    QList<double> *xlist_cpsd;
    QList<QList<double>*> *ylistlist_cpsd;
    void cpsdAnalysis(QList<int>* channelList);
    QList<double> xl_cpsd,yl_cpsd,yl2_cpsd;
    QList<QString>* channelUnitList_cpsd;

    // 自相关分析数据
    int length_corr;
    QList<double> *xlist_corr;
    QList<QList<double>*> *ylistlist_corr;
    void corrAnalysis(int channel);
    QList<double> xlistCorr,ylistCorr,dataCorr,tCorr;
    QList<QString>* channelUnitList_corr;

    // 互相关分析数据
    int length_xcorr;
    QList<double> *xlist_xcorr;
    QList<QList<double>*> *ylistlist_xcorr;
    void xcorrAnalysis(QList<int>* channelList);
    QList<double> data1Xcorr,data2Xcorr,tXcorr,xlistXcorr,ylistXcorr;
    QList<QString>* channelUnitList_xcorr;

    // 1/3倍频程分析数据
    int length_onethird;
    QList<double> *xlist_onethird;
    QList<QList<double>*> *ylistlist_onethird;
    void onethirdAnalysis(int channel);
    QList<double> xl_onethird,yl_onethird;
    QList<QString>* channelUnitList_onethird;

    // 倒谱
    int length_daopu;
    QList<double> *xlist_daopu;
    QList<QList<double>*> *ylistlist_daopu;
    void daopuAnalysis(int channel);
    QList<double> xl_daopu,yl_daopu;
    QList<QString>* channelUnitList_daopu;

    //粘贴板
    void setZhantieban(double start, int length);
    void getZhantiebanTime();
    void getZhantiebanFreq();
    void getZhantiebanPsd();
    void getZhantiebanCpsd();
    void getZhantiebanCorr();
    void getZhantiebanXcorr();
    void getZhantiebanOnethird();
    void getZhantiebanDaopu();
    void getZhantieban(int* lengthData,QList<double> *xlistData,QList<QList<double>*> *ylistList);

    // 导出时域数据
    void export_time();

    QString danWeiList[4];
    QString getChannelUnitInFile_freq(QList<QString>* channelUnitList,int channel);
    QString getChannelUnitInFile_psd(QList<QString>* channelUnitList,int channel);
    QString getChannelUnitInFile_corr(QList<QString>* channelUnitList,int channel);

private Q_SLOTS:
    void on_pushButtonShowWave_clicked();

private:
    Ui_WidgetSoundTest* ui;

    //粘贴板
    double startTimeZhantieban;
    int lengthZhantieban;
    QList<double> *xlistZhantieban;
    QList<QList<double>*> *ylistListZhantieban;

public:
    int celiChannel;
    double celiPpv;

};

} // namespace SoundTest
#endif // ANALYSIS_H
