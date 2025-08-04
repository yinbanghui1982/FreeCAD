#include "analysis.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"

#include "matlab_files/codegen/lib/time_anslysis/rt_nonfinite.h"
#include "matlab_files/codegen/lib/time_anslysis/time_anslysis.h"
#include "matlab_files/codegen/lib/time_anslysis/time_anslysis_terminate.h"
#include "matlab_files/codegen/lib/time_anslysis/coder_array.h"
#include "matlab_files/codegen/dll/pingpu/pingpu.h"
#include "matlab_files/codegen/dll/psd_analysis/psd_analysis.h"
#include "matlab_files/codegen/dll/cpsd_analysis/cpsd_analysis.h"
#include "matlab_files/codegen/dll/onethird/onethird.h"
#include "matlab_files/codegen/dll/daopu_analysis/daopu_analysis.h"

#include <cstddef>
#include <cstdlib>
#include "corr.h"

#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QMessageBox>

using namespace SoundTest;

Analysis::Analysis(Ui_WidgetSoundTest* ui) :channelNames{"通道1","通道2","通道3","通道4"}
{
    this->ui=ui;
    

    xlist_time=new QList<double>();
    ylistlist_time=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_time)[i]=new QList<double>();
    channelUnitList_time=new QList<QString>();


    xlist_freq=new QList<double>();
    ylistlist_freq=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_freq)[i]=new QList<double>();
    channelUnitList_freq=new QList<QString>();

    xlist_psd=new QList<double>();
    ylistlist_psd=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_psd)[i]=new QList<double>();
    channelUnitList_psd=new QList<QString>();

    xlist_cpsd=new QList<double>();
    ylistlist_cpsd=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_cpsd)[i]=new QList<double>();
    channelUnitList_cpsd=new QList<QString>();

    xlist_corr=new QList<double>();
    ylistlist_corr=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_corr)[i]=new QList<double>();
    channelUnitList_corr=new QList<QString>();

    xlist_xcorr=new QList<double>();
    ylistlist_xcorr=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_xcorr)[i]=new QList<double>();
    channelUnitList_xcorr=new QList<QString>();

    xlist_onethird=new QList<double>();
    ylistlist_onethird=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_onethird)[i]=new QList<double>();
    channelUnitList_onethird=new QList<QString>();

    xlist_daopu=new QList<double>();
    ylistlist_daopu=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_daopu)[i]=new QList<double>();
    channelUnitList_daopu=new QList<QString>();

    xlistZhantieban=new QList<double>();
    ylistListZhantieban=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistListZhantieban)[i]=new QList<double>();

    xlist_time_step=new QList<double>(step_length);
    ylistlist_time_step=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_time_step)[i]=new QList<double>(step_length);

}


void Analysis::timeAnalysis(int channel)
{
    // 绘制时域图
    if (length_time<=8192)
        plotUtilsTime->chart_plot(xlist_time,(*ylistlist_time)[channel],length_time,channelNames[channel],"时间/s",(*channelUnitList_time)[channel]);
    else {
        xlist_time_step->resize(step_length);
        for (int i=0;i<4;i++)
            (*ylistlist_time_step)[i]->resize(step_length);

        for (int j=0;j<step_length;j++)
            (*xlist_time_step)[j] = (*xlist_time)[j+step_start];
        for (int i=0;i<4;i++)
            for (int j=0;j<step_length;j++)
                (*(*ylistlist_time_step)[i])[j]=(*(*ylistlist_time)[i])[j+step_start];

        plotUtilsTime->chart_plot(xlist_time_step,(*ylistlist_time_step)[channel],step_length,channelNames[channel],"时间/s",(*channelUnitList_time)[channel]);
    }
    // 时域分析
    coder::array<double, 2U> sig;
    double max_abs;
    double mean2;
    double mean_abs;
    double rms2;
    double rms_abs;
    double spl;
    double std2;
    double var2;
    double ppv;
    // Initialize function 'time_anslysis' input arguments.
    // Initialize function input argument 'sig'.
    // Set the size of the array.
    // Change this size to the value that the application requires.
    sig.set_size(1, length_time);
    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < 1; idx0++) {
        for (int idx1{0}; idx1 < length_time; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            sig[idx1] = (*(*ylistlist_time)[channel])[idx1];
        }
    }

    // Call the entry-point 'time_anslysis'.
    time_anslysis(sig, &rms2, &mean2, &max_abs, &mean_abs, &rms_abs, &var2,&std2,&spl,&ppv);

    //将时域分析结果输出到文本框
    if (state_time==0){         //时域分析
        QString res="";
        res=res+"有效值："+QString::number(rms2)+"\r\n";
        res=res+"平均值："+QString::number(mean2)+"\r\n";
        res=res+"最大幅值："+QString::number(max_abs)+"\r\n";
        res=res+"平均幅值："+QString::number(mean_abs)+"\r\n";
        res=res+"方根幅值："+QString::number(rms_abs)+"\r\n";
        res=res+"方差："+QString::number(var2)+"\r\n";
        res=res+"均方差："+QString::number(std2)+"\r\n";
        if((*channelUnitList_time)[channel]=="Sound Pressure/Pa"){
            res=res+"总声压级："+QString::number(spl)+"\r\n";
        }
        res=res+"峰峰值："+QString::number(ppv)+"\r\n";

        ui->textEditTimeAnalysis->setText(res);
    } else if(state_time==1){   //校准里的时域分析
        this->celiChannel=channel;
        this->celiPpv=ppv;
    }

}


void Analysis::freqAnalysis(int channel){

    // 频谱分析
    coder::array<double, 2U> f;
    coder::array<double, 2U> Y;
    coder::array<double, 2U> time_tmp;
    coder::array<double, 2U> data;
    double fs;
    // Initialize function 'pingpu' input arguments.
    // Initialize function input argument 'time'.

    // Set the size of the array.
    // Change this size to the value that the application requires.
    time_tmp.set_size(1,length_freq);
    data.set_size(1,length_freq);
    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < time_tmp.size(1); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        time_tmp[idx0] = (*xlist_freq)[idx0];
        data[idx0] = (*(*ylistlist_freq)[channel])[idx0];
    }

    // Initialize function input argument 'data'.
    // Call the entry-point 'pingpu'.
    double w = 0;   //不加窗
    pingpu(time_tmp,data,w, f, Y, &fs);

    // 绘制频谱图
    xl_freq.clear();
    yl_freq.clear();
    for (int i=0;i<length_freq/2;i++){
        xl_freq.append(f[0,i]);
        yl_freq.append(Y[i]);
    }

    if(state_freq==0){          //0 频域分析
        plotUtilsFreq->xlistPlot=&xl_freq;
        plotUtilsFreq->ylistPlot=&yl_freq;
        plotUtilsFreq->lengthPlotData=length_freq/2;
        plotUtilsFreq->chart_plot(&xl_freq,&yl_freq,length_freq/2,channelNames[channel],"频率/Hz",getChannelUnitInFile_freq(channelUnitList_freq,channel));
    } else if(state_freq==1){   //1 校准里面的频域分析
        plotUtilsCeliFreq->xlistPlot=&xl_freq;
        plotUtilsCeliFreq->ylistPlot=&yl_freq;
        plotUtilsCeliFreq->lengthPlotData=length_freq/2;
        if(danWeiList[channel]=="mV/Pa")
            plotUtilsCeliFreq->chart_plot(&xl_freq,&yl_freq,length_freq/2,channelNames[channel],"频率/Hz","声压幅值谱级/dB  ref=20e-6 Pa/Hz");
        else if(danWeiList[channel]=="mV/mV")
            plotUtilsCeliFreq->chart_plot(&xl_freq,&yl_freq,length_freq/2,channelNames[channel],"频率/Hz","电压幅值谱级/dB  ref=20e-6 mV/Hz");
        else if(danWeiList[channel]=="mV/(m/s^2)")
            plotUtilsCeliFreq->chart_plot(&xl_freq,&yl_freq,length_freq/2,channelNames[channel],"频率/Hz","加速度幅值谱级/dB  ref=20e-6 m/s^2/Hz");

    }

    // 打印相关信息
    int index=0;
    double max_y=yl_freq[0];
    for (int i=1;i<length_freq/2;i++){
        if(yl_freq[i]>max_y){
            index=i;
            max_y=yl_freq[i];
        }
    }
    double max_x=xl_freq[index];

    int index2=index+1;
    double max_y2=yl_freq[index+1];
    for (int i=index+2;i<length_freq/2;i++){
        if(yl_freq[i]>max_y2){
            index2=i;
            max_y2=yl_freq[i];
        }
    }
    double max_x2=xl_freq[index2];


    if(state_freq==0){
        QString str="";
        str=str+"主频频率:"+QString::number(max_x)+"Hz\r\n";
        str=str+"主频有效值:"+QString::number(max_y)+"dB\r\n";
        str=str+"次频频率:"+QString::number(max_x2)+"Hz\r\n";
        str=str+"次频有效值:"+QString::number(max_y2)+"dB\r\n";
        ui->textEditFreqAnalysis->setText(str);
    }
    else if (state_freq==1){
        QString str="";
        str=str+"主频频率:"+QString::number(max_x)+"Hz\t";
        str=str+"主频有效值:"+QString::number(max_y)+"dB\t";
        str=str+"次频频率:"+QString::number(max_x2)+"Hz\t";
        str=str+"次频有效值:"+QString::number(max_y2)+"dB\t";
        ui->textEditCeliRes->setText(str);
    }
}

QString Analysis::getChannelUnitInFile_freq(QList<QString>* channelUnitList,int channel){
    QString res;
    if((*channelUnitList)[channel]=="Sound Pressure/Pa"){
        res="声压幅值谱级/dB  ref=20e-6 Pa/Hz";
    } else if((*channelUnitList)[channel]=="Voltage/mV"){
        res="电压幅值谱级/dB  ref=20e-6 mV/Hz";
    } else if((*channelUnitList)[channel]=="Acceleration/(m/s^2)"){
        res="加速度幅值谱级/dB  ref=20e-6 m/s^2/Hz";
    }
    return res;
}

void Analysis::psdAnalysis(int channel){
    coder::array<double, 1U> noise;
    coder::array<double, 2U> psdestx;
    coder::array<double, 1U> Fxx;
    coder::array<double, 1U> time_tmp;

    // Initialize function 'psd_analysis' input arguments.
    // Initialize function input argument 'noise'.
    time_tmp.set_size(length_psd);
    noise.set_size(length_psd);
    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < noise.size(0); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        time_tmp[idx0] = (*xlist_psd)[idx0];
        noise[idx0] = (*(*ylistlist_psd)[channel])[idx0];
    }
    // Call the entry-point 'psd_analysis'.

    qDebug()<<"xlist_psd:"<<(*xlist_psd)[0]<<(*xlist_psd)[1]<<(*xlist_psd)[2];
    qDebug()<<"noise:"<<noise[0]<<noise[1]<<noise[2];

    double fs=1.0/(time_tmp[1]-time_tmp[0]);
    psd_analysis(noise, length_psd,fs , psdestx, Fxx);


    // 绘制频谱图
    xl_psd.clear();
    yl_psd.clear();
    for (int i=0;i<length_psd/2;i++){
        xl_psd.append(Fxx[i]);
        yl_psd.append(psdestx[0,i]);
    }
    plotUtilsPsd->xlistPlot=&xl_psd;
    plotUtilsPsd->ylistPlot=&yl_psd;
    plotUtilsPsd->lengthPlotData=length_psd/2;
    plotUtilsPsd->chart_plot(&xl_psd,&yl_psd,length_psd/2,channelNames[channel],"频率/Hz",getChannelUnitInFile_psd(channelUnitList_psd,channel));
}

QString Analysis::getChannelUnitInFile_psd(QList<QString>* channelUnitList,int channel){
    QString res;
    if((*channelUnitList)[channel]=="Sound Pressure/Pa"){
        res="自功率谱密度/dB,ref=1 Pa^2/Hz";
    } else if((*channelUnitList)[channel]=="Voltage/mV"){
        res="自功率谱密度/dB,ref=1 mV^2/Hz";
    } else if((*channelUnitList)[channel]=="Acceleration/(m/s^2)"){
        res="自功率谱密度/dB,ref=1 (m/s^2)^2/Hz";
    }
    return res;
}


void Analysis::cpsdAnalysis(QList<int>* channelList){

    coder::array<double, 2U> Pxy2;
    coder::array<double, 2U> arg2;
    coder::array<double, 2U> x_tmp;
    coder::array<double, 2U> y_tmp;
    coder::array<double, 1U> f;
    coder::array<double, 1U> time_tmp;
    // Initialize function 'cpsd_analysis' input arguments.
    // Initialize function input argument 'x'.
    time_tmp.set_size(length_cpsd);
    x_tmp.set_size(1,length_cpsd);
    y_tmp.set_size(1,length_cpsd);

    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < time_tmp.size(0); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        time_tmp[idx0] = (*xlist_cpsd)[idx0];
        x_tmp[idx0] = (*(*ylistlist_cpsd)[(*channelList)[0]])[idx0];
        y_tmp[idx0] = (*(*ylistlist_cpsd)[(*channelList)[1]])[idx0];
    }

    // Initialize function input argument 'y'.
    // Call the entry-point 'cpsd_analysis'.
    qDebug()<<"xlist_cpsd:"<<(*xlist_cpsd)[0]<<(*xlist_cpsd)[1]<<(*xlist_cpsd)[2];
    qDebug()<<"x_tmp:"<<x_tmp[0]<<x_tmp[1]<<x_tmp[2];

    double fs=1.0/(time_tmp[1]-time_tmp[0]);
    cpsd_analysis(x_tmp, y_tmp, fs, Pxy2, arg2, f);

    // 绘制频谱图
    xl_cpsd.clear();
    yl_cpsd.clear();
    yl2_cpsd.clear();

    for (int i=0;i<length_cpsd/2;i++){
        xl_cpsd.append(f[i]);
        yl_cpsd.append(Pxy2[0,i]);
        yl2_cpsd.append(arg2[0,i]);
    }

    qDebug()<<"xl:"<<xl_cpsd[0]<<xl_cpsd[1]<<xl_cpsd[2];
    qDebug()<<"yl:"<<yl_cpsd[0]<<yl_cpsd[1]<<yl_cpsd[2];
    qDebug()<<"yl2:"<<yl2_cpsd[0]<<yl2_cpsd[1]<<yl2_cpsd[2];
    plotUtilsCpsd1->xlistPlot=&xl_cpsd;
    plotUtilsCpsd1->ylistPlot=&yl_cpsd;
    plotUtilsCpsd1->chart_plot(&xl_cpsd,&yl_cpsd,40,channelNames[(*channelList)[0]]+"/"+channelNames[(*channelList)[1]],"频率/Hz","互功率谱密度/dB, ref=1");

    plotUtilsCpsd2->xlistPlot=&xl_cpsd;
    plotUtilsCpsd2->ylistPlot=&yl2_cpsd;
    plotUtilsCpsd2->chart_plot(&xl_cpsd,&yl2_cpsd,40,channelNames[(*channelList)[0]]+"/"+channelNames[(*channelList)[1]],"频率/Hz","相位角/rad");

}


void Analysis::corrAnalysis(int channel){

    int N=length_corr;
    // QList<double> xlist,ylist,data,t;
    xlistCorr.clear();
    ylistCorr.clear();
    dataCorr.clear();
    tCorr.clear();

    dataCorr.resize(N);
    tCorr.resize(N);
    xlistCorr.resize(N);
    ylistCorr.resize(N);

    for (int i=0;i<N;i++){
        tCorr[i]=(*xlist_corr)[i];
        dataCorr[i]=(*(*ylistlist_corr)[channel])[i];
    }
    double dt=tCorr[1]-tCorr[0];

    autoCorrelationAnalysis(dataCorr.data(), N, dt, xlistCorr.data(), ylistCorr.data());
    plotUtilsCorr->xlistPlot=&xlistCorr;
    plotUtilsCorr->ylistPlot=&ylistCorr;
    plotUtilsCorr->chart_plot(&xlistCorr,&ylistCorr,N,channelNames[channel],"时间/s",getChannelUnitInFile_corr(channelUnitList_corr,channel));
}

QString Analysis::getChannelUnitInFile_corr(QList<QString>* channelUnitList,int channel){
    QString res;
    if((*channelUnitList)[channel]=="Sound Pressure/Pa"){
        res="自相关函数/Pa^2";
    } else if((*channelUnitList)[channel]=="Voltage/mV"){
        res="自相关函数/mV^2";
    } else if((*channelUnitList)[channel]=="Acceleration/(m/s^2)"){
        res="自相关函数/(m/s^2)^2";
    }
    return res;
}

void Analysis::xcorrAnalysis(QList<int>* channelList){
    int N=length_xcorr;

    // QList<double> data1,data2,t,xlist,ylist;

    xlistXcorr.clear();
    ylistXcorr.clear();
    data1Xcorr.clear();
    data2Xcorr.clear();
    tXcorr.clear();

    data1Xcorr.resize(N);
    data2Xcorr.resize(N);
    tXcorr.resize(N);
    xlistXcorr.resize(N);
    ylistXcorr.resize(N);

    for (int i=0;i<N;i++){
        tXcorr[i]=(*xlist_xcorr)[i];
        data1Xcorr[i]=(*(*ylistlist_xcorr)[(*channelList)[0]])[i];
        data2Xcorr[i]=(*(*ylistlist_xcorr)[(*channelList)[1]])[i];
    }
    double dt=tXcorr[1]-tXcorr[0];
    qDebug()<<"data1"<<data1Xcorr[0]<<data1Xcorr[1];
    qDebug()<<"data2"<<data2Xcorr[0]<<data2Xcorr[1];

    crossCorrelationAnalysis(data1Xcorr.data(),data2Xcorr.data(), N, dt, xlistXcorr.data(), ylistXcorr.data());
    qDebug()<<"xlist"<<xlistXcorr[0]<<xlistXcorr[1];
    qDebug()<<"ylist"<<ylistXcorr[0]<<ylistXcorr[1];

    plotUtilsXcorr->chart_plot(&xlistXcorr,&ylistXcorr,N,channelNames[(*channelList)[0]]+"/"+channelNames[(*channelList)[1]],"时间/s","互相关函数");

}

void Analysis::onethirdAnalysis(int channel){
    coder::array<double, 2U> f;
    coder::array<double, 2U> t;
    coder::array<double, 1U> Ya_1;
    coder::array<double, 1U> x;
    double Ya_2[30];
    double fc[30];
    double nc;
    double nfft;

    // Initialize function 'onethird' input arguments.
    // Initialize function input argument 't'.
    t.set_size(1, length_onethird);
    // Loop over the array to initialize each element.

    for (int idx1{0}; idx1 < t.size(1); idx1++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        t[idx1] = (*(xlist_onethird))[idx1];
    }

    // Initialize function input argument 'x'.
    x.set_size(length_onethird);
    // Loop over the array to initialize each element.
    for (int idx0{0}; idx0 < x.size(0); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        x[idx0] = (*(*(ylistlist_onethird))[channel])[idx0];
    }

    // Call the entry-point 'onethird'.
    qDebug()<<"one third";
    qDebug()<<"t:"<<t[0]<<t[1];
    qDebug()<<"x:"<<x[0]<<x[1];

    onethird(t, x, Ya_1, Ya_2, f, fc, &nfft, &nc);    
    qDebug()<<"fc:"<<fc[0];


    // 绘制频谱图
    // QList<double> xl_onethird,yl_onethird;
    xl_onethird.resize(nc);
    yl_onethird.resize(nc);
    for (int i=0;i<nc;i++){
        xl_onethird[i]=fc[i];
        yl_onethird[i]=Ya_2[i];
    }
    plotUtilsOneThird->xlistPlot=&xl_onethird;
    plotUtilsOneThird->ylistPlot=&yl_onethird;
    plotUtilsOneThird->lengthPlotData=nc;
    plotUtilsOneThird->chart_plot(&xl_onethird,&yl_onethird,nc,channelNames[channel],"频率/Hz","声压级/dB");
    // plotUtilsOneThird->x_log();
}


void Analysis::daopuAnalysis(int channel){
    coder::array<creal_T, 2U> z;
    coder::array<double, 2U> y;
    coder::array<double, 1U> time_tmp;
    // Initialize function 'daopu_analysis' input arguments.
    // Initialize function input argument 'y'.
    time_tmp.set_size(length_daopu);
    y.set_size(1,length_daopu);

    for (int idx0{0}; idx0 < y.size(1); idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        time_tmp[idx0] = (*xlist_daopu)[idx0];
        y[idx0] = (*(*ylistlist_daopu)[channel])[idx0];
    }
    // Call the entry-point 'daopu_analysis'.
    daopu_analysis(y, z);
    qDebug()<<"y:"<<y[0]<<y[1];
    qDebug()<<"z:"<<z[0,0].re<<z[0,1].re;

    // 绘制频谱图
    // QList<double> xl_daopu,yl_daopu;
    xl_daopu.resize(length_daopu);
    yl_daopu.resize(length_daopu);
    for (int i=0;i<length_daopu;i++){
        xl_daopu[i]=time_tmp[i];
        yl_daopu[i]=sqrt(z[0,i].re*z[0,i].re+z[0,i].re*z[0,i].re);
    }
    qDebug()<<"xl:"<<xl_daopu[0]<<xl_daopu[1];
    qDebug()<<"yl:"<<yl_daopu[0]<<yl_daopu[1];
    plotUtilsDaopu->xlistPlot=&xl_daopu;
    plotUtilsDaopu->ylistPlot=&yl_daopu;
    plotUtilsDaopu->chart_plot(&xl_daopu,&yl_daopu,length_daopu,channelNames[channel],"倒频率/s","幅值");
}

void Analysis::on_pushButtonShowShuxian_clicked(){

    this->plotUtilsTime->showShuxian();

}

void Analysis::setZhantieban(double start, int length){
    startTimeZhantieban=start;
    lengthZhantieban=length;
    int startIndex;
    for (int i=0;i<length_time;i++){
        if ((*xlist_time)[i]>startTimeZhantieban){
            startIndex=i;
            break;
        }
    }

    xlistZhantieban->resize(length);
    ylistListZhantieban->resize(4);
    for (int i=0;i<4;i++){
        (*ylistListZhantieban)[i]->resize(length);
    }
    for (int i=0;i<length;i++){
        (*xlistZhantieban)[i]=(*xlist_time)[i+startIndex];
        for (int j=0;j<4;j++){
            (*(*ylistListZhantieban)[j])[i]=(*(*ylistlist_time)[j])[i+startIndex];
        }
    }
}

void Analysis::getZhantieban(int* lengthData,QList<double> *xlistData,QList<QList<double>*> *ylistList){
    *lengthData=lengthZhantieban;
    xlistData->resize(lengthZhantieban);
    ylistList->resize(4);
    for (int i=0;i<4;i++){
        (*(*ylistList)[i]).resize(lengthZhantieban);
    }
    for (int i=0;i<lengthZhantieban;i++){
        (*xlistData)[i]=(*xlistZhantieban)[i];
        for (int j=0;j<4;j++){
            (*(*ylistList)[j])[i]=(*(*ylistListZhantieban)[j])[i];
        }
    }
}

void Analysis::getZhantiebanTime(){
    getZhantieban(&length_time,xlist_time,ylistlist_time);
}

void Analysis::getZhantiebanFreq(){
    getZhantieban(&length_freq,xlist_freq,ylistlist_freq);
}

void Analysis::getZhantiebanPsd(){
    getZhantieban(&length_psd,xlist_psd,ylistlist_psd);
}

void Analysis::getZhantiebanCpsd(){
    getZhantieban(&length_cpsd,xlist_cpsd,ylistlist_cpsd);
}

void Analysis::getZhantiebanCorr(){
    getZhantieban(&length_corr,xlist_corr,ylistlist_corr);
}

void Analysis::getZhantiebanXcorr(){
    getZhantieban(&length_xcorr,xlist_xcorr,ylistlist_xcorr);
}

void Analysis::getZhantiebanOnethird(){
    getZhantieban(&length_onethird,xlist_onethird,ylistlist_onethird);
}

void Analysis::getZhantiebanDaopu(){
    getZhantieban(&length_daopu,xlist_daopu,ylistlist_daopu);
}

void Analysis::export_time(){
    // 显示文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"),
                                                    "", QObject::tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        // 用户取消了保存
        return;
    }

    // 如果文件后缀不是.txt，则添加后缀
    if (!fileName.endsWith(".txt")) {
        fileName += ".txt";
    }

    // 创建并打开文件进行写入
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        // 无法打开文件，可能的错误处理
        return;
    }

    // 将文本数据写入文件
    QTextStream out(&file);

    QString outStr="";
    for (int i=0;i<length_time;i++){
        outStr=outStr+QString::number((*xlist_time)[i])+"\t";
        for (int j=0;j<4;j++){
            outStr=outStr+QString::number((*(*ylistlist_time)[j])[i])+"\t";
        }
        if (i!=length_time-1)
            outStr=outStr+"\n";

    }


    out << outStr;
    file.close();
    QMessageBox::information(NULL,  "消息",  "已导出数据", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}
