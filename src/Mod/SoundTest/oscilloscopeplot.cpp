#include "oscilloscopeplot.h"

using namespace SoundTest;

OscilloscopePlot::OscilloscopePlot() {
    xlist_freq=new QList<double>();
    ylistlist_freq=new QList<QList<double>*>(4);
    for (int i=0;i<4;i++)
        (*ylistlist_freq)[i]=new QList<double>();

}

void OscilloscopePlot::plotData(int shiboState,int celiChannel){
    // 通道数据绘图
    ploting=1;
    int* ch1_ptr=(int*)ch1_2.data();
    int* ch2_ptr=(int*)ch2_2.data();
    int* ch3_ptr=(int*)ch3_2.data();
    int* ch4_ptr=(int*)ch4_2.data();

    int *ch1_ptr_1,*ch2_ptr_1,*ch3_ptr_1,*ch4_ptr_1;

    if (shiboLength<=8192){
        ch1_ptr_1=new int[cntBlock_2*1024];
        ch2_ptr_1=new int[cntBlock_2*1024];
        ch3_ptr_1=new int[cntBlock_2*1024];
        ch4_ptr_1=new int[cntBlock_2*1024];

        for (int i=0;i<cntBlock_2*1024;i++){
            ch1_ptr_1[i]=ch1_ptr[i]/256;
            ch2_ptr_1[i]=ch2_ptr[i]/256;
            ch3_ptr_1[i]=ch3_ptr[i]/256;
            ch4_ptr_1[i]=ch4_ptr[i]/256;
        }
    } else {
        ch1_ptr_1=new int[1024];
        ch2_ptr_1=new int[1024];
        ch3_ptr_1=new int[1024];
        ch4_ptr_1=new int[1024];

        for (int i=0;i<1024;i++){
            ch1_ptr_1[i]=ch1_ptr[i]/256;
            ch2_ptr_1[i]=ch2_ptr[i]/256;
            ch3_ptr_1[i]=ch3_ptr[i]/256;
            ch4_ptr_1[i]=ch4_ptr[i]/256;
        }
    }

    int m1=0,m2=0,m3=0,m4=0;
    int blockCount=shiboLength<=8192?cntBlock_2:1;

    // for (int i=0;i<blockCount*1024;i++){
    //     m1+=ch1_ptr_1[i];
    //     m2+=ch2_ptr_1[i];
    //     m3+=ch3_ptr_1[i];
    //     m4+=ch4_ptr_1[i];
    // }

    // m1/=(blockCount*1024);
    // m2/=(blockCount*1024);
    // m3/=(blockCount*1024);
    // m4/=(blockCount*1024);

    // for (int i=0;i<(blockCount*1024);i++){
    //     ch1_ptr_1[i]-=m1;
    //     ch2_ptr_1[i]-=m2;
    //     ch3_ptr_1[i]-=m3;
    //     ch4_ptr_1[i]-=m4;
    // }

    int shiboLength2=shiboLength<=8192?shiboLength:1024;

    for (int i=0;i<shiboLength2;i++){
        (*xlist)[i]=shiboLength<=8192?(double)i/samplingRate:((double)i+(cntBlock_2-1)*1024)/samplingRate;
        if (i<blockCount*1024){
            // (*ylist1)[i]=(ch1_ptr_1[i]*d1-1705.50)/29.87;
            //(*ylist1)[i]=(ch1_ptr_1[i]*d+2468.864)*d1/0.8898;

            // 单端接线
            // (*ylist1)[i]=(ch1_ptr_1[i]*d)*d1-1035.08;
            // (*ylist2)[i]=(ch2_ptr_1[i]*d)*d2-1035.08-0.01;
            // (*ylist3)[i]=(ch3_ptr_1[i]*d)*d3-1035.08-0.085;
            // (*ylist4)[i]=(ch4_ptr_1[i]*d)*d4-1035.08-1.15;

            // 差分接线
            (*ylist1)[i]=(ch1_ptr_1[i]*d)*d1;
            (*ylist2)[i]=(ch2_ptr_1[i]*d)*d2;
            (*ylist3)[i]=(ch3_ptr_1[i]*d)*d3;
            (*ylist4)[i]=(ch4_ptr_1[i]*d)*d4;
        }
    }

    //示波或采样
    if (shiboState==0 || shiboState==1){
        if (danwei1=="mV/Pa"){
            analysis->plotUtilsChannel1->chart_plot(xlist, ylist1, shiboLength2,"通道1","时间/s","声压/Pa");
        } else if (danwei1=="mV/mV"){
            analysis->plotUtilsChannel1->chart_plot(xlist, ylist1, shiboLength2,"通道1","时间/s","电压/mV");
        } else if (danwei1=="mV/(m/s^2)"){
            analysis->plotUtilsChannel1->chart_plot(xlist, ylist1, shiboLength2,"通道1","时间/s","加速度/m/s^2");
        }

        if (danwei2=="mV/Pa"){
            analysis->plotUtilsChannel2->chart_plot(xlist, ylist2, shiboLength2,"通道2","时间/s","声压/Pa");
        } else if (danwei2=="mV/mV"){
            analysis->plotUtilsChannel2->chart_plot(xlist, ylist2, shiboLength2,"通道2","时间/s","电压/mV");
        } else if (danwei2=="mV/(m/s^2)"){
            analysis->plotUtilsChannel2->chart_plot(xlist, ylist2, shiboLength2,"通道2","时间/s","加速度/m/s^2");
        }


        if (danwei3=="mV/Pa"){
            analysis->plotUtilsChannel3->chart_plot(xlist, ylist3, shiboLength2,"通道3","时间/s","声压/Pa");
        } else if (danwei3=="mV/mV"){
            analysis->plotUtilsChannel3->chart_plot(xlist, ylist3, shiboLength2,"通道3","时间/s","电压/mV");
        } else if (danwei3=="mV/(m/s^2)"){
            analysis->plotUtilsChannel3->chart_plot(xlist, ylist3, shiboLength2,"通道3","时间/s","加速度/m/s^2");
        }

        if (danwei4=="mV/Pa"){
            analysis->plotUtilsChannel4->chart_plot(xlist, ylist4, shiboLength2,"通道4","时间/s","声压/Pa");
        } else if (danwei4=="mV/mV"){
            analysis->plotUtilsChannel4->chart_plot(xlist, ylist4, shiboLength2,"通道4","时间/s","电压/mV");
        } else if (danwei4=="mV/(m/s^2)"){
            analysis->plotUtilsChannel4->chart_plot(xlist, ylist4, shiboLength2,"通道4","时间/s","加速度/m/s^2");
        }

    //传感器校准(示波)、传感器校准（校准）
    } else if (shiboState==2||shiboState==3){
        QString dw;
        if (danwei1=="mV/Pa")
            dw="声压/Pa";
        else if (danwei1=="mV/(m/s^2)")
            dw="加速度/m/s^2";
        else
            dw="电压/mV";

        if (celiChannel==1){
            analysis->plotUtilsCeliTime->chart_plot(xlist, ylist1, shiboLength2,"通道1","时间/s",dw);
        } else if (celiChannel==2){
            analysis->plotUtilsCeliTime->chart_plot(xlist, ylist2, shiboLength2,"通道2","时间/s",dw);
        } else if (celiChannel==3){
            analysis->plotUtilsCeliTime->chart_plot(xlist, ylist3, shiboLength2,"通道3","时间/s",dw);
        } else if (celiChannel==4){
            analysis->plotUtilsCeliTime->chart_plot(xlist, ylist4, shiboLength2,"通道4","时间/s",dw);
        }

        //频域分析
        analysis->state_freq=1;
        xlist_freq=xlist;
        (*ylistlist_freq)[0]=ylist1;
        (*ylistlist_freq)[1]=ylist2;
        (*ylistlist_freq)[2]=ylist3;
        (*ylistlist_freq)[3]=ylist4;
        analysis->xlist_freq=xlist_freq;
        analysis->ylistlist_freq=ylistlist_freq;
        analysis->length_freq=1024;
        analysis->freqAnalysis(celiChannel-1);

        //时域分析
        if (shiboState==3){
            analysis->state_time=1;
            analysis->xlist_time=xlist_freq;
            analysis->ylistlist_time=ylistlist_freq;
            analysis->length_time=1024;
            analysis->timeAnalysis(celiChannel-1);

            //校准完成
            finish_celibrate=1;
        }

    }

    delete[] ch1_ptr_1;
    delete[] ch2_ptr_1;
    delete[] ch3_ptr_1;
    delete[] ch4_ptr_1;
    ploting=0;
    connCount--;
}

