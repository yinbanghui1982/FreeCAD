#include "plotutils.h"

using namespace SoundTest;

PlotUtils::PlotUtils() {
    // axisxLog =  new  QLogValueAxis();
    // series =new QLineSeries();  //line为系列，即线条对象

}

void PlotUtils::chart_plot(QList<double>* xlist,QList<double>* ylist, int length,QString title,
                           QString xlable,QString ylable){


    qDebug() << "plot1";

    this->xlistPlot->fromList(*xlist);
    this->ylistPlot->fromList(*ylist);
    this->xlable=xlable;
    this->ylable=ylable;

    qChartView->chart()->removeAllSeries();

    // QChart *m_chart = new QChart();

    // m_chart->setTheme(QChart::ChartThemeBlueIcy); //改变主题
    // m_chart->setDropShadowEnabled(true);//背景阴影
    // m_chart->setAutoFillBackground(true);  //设置背景自动填充

    qChartView->chart()->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    qChartView->chart()->setTitleFont(QFont("微软雅黑"));//设置标题字体
    qChartView->chart()->setTitle(title);

    // 本身QChart是不可见的 需要用QChartView是渲染显示 没有这一行 就什么都看不到
    // gv->setChart(m_chart);


    //   //修改说明样式  设置线条对象的说明文字 格式大小颜色 对齐位置等 就是指标签
    qChartView->chart()->legend()->setVisible(false);
    //    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    //    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    //    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    //    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    //    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色

    /*添加系列到chart上*/
    qDebug() << "plot2";
    series =new QLineSeries();  //line为系列，即线条对象
    // series->clear();

    // QList<QLineSeries *> m_series;
    // m_series.append(series);  //把系列传入list表中
    // series->setName(QString("line"+QString::number(m_series.count())));

    seriesData.clear();
    // series->setUseOpenGL(true);
    int offset = qChartView->chart()->series().count(); //计算偏移量 即1，2，3，4系列的顺序
    for(int i=0;i<length;i++)
    {
        seriesData.append(QPointF(xlist->data()[i], ylist->data()[i]));
    }

    qDebug() << "plot3";
    series->append(seriesData);  //把数据传入系列上

    qChartView->chart()->addSeries(series);   /*添加系列到chart上*/

    //    if (m_series.count() == 1)
    //        m_chart->createDefaultAxes();  //画轴

    /*设置横纵坐标的刻度值*/
    QValueAxis  *axisx =  new  QValueAxis();
    QValueAxis  *axisy =  new  QValueAxis();

    axisx->setTitleText(xlable);
    axisy->setTitleText(ylable);

    qDebug() << "plot4";

    double minx=(*xlist)[0],maxx=(*xlist)[0],miny=(*ylist)[0],maxy=(*ylist)[0];
    for(int i=1;i<length;i++){
        if((*xlist)[i]<minx){
            minx=(*xlist)[i];
        }
        if((*xlist)[i]>maxx){
            maxx=(*xlist)[i];
        }
        if((*ylist)[i]<miny){
            miny=(*ylist)[i];
        }
        if((*ylist)[i]>maxy){
            maxy=(*ylist)[i];
        }
    }
    miny=miny-0.001;
    maxy=maxy+0.001;

    qDebug() << "plot5";
    axisx->setRange(minx,maxx);   //设置x轴范围
    axisy->setRange(miny,maxy); //设置y轴范围

    qChartView->chart()->setAxisX(axisx); //把刻度值传入进视图m_chart中显示
    qChartView->chart()->setAxisY(axisy);

    qDebug() << "plot6";

}


void PlotUtils::x_log(){

    axisxLog->setTitleText(xlable);

    double minx=(*xlistPlot)[0],maxx=(*xlistPlot)[0],miny=(*ylistPlot)[0],maxy=(*ylistPlot)[0];
    for(int i=1;i<lengthPlotData;i++){
        if((*xlistPlot)[i]<minx){
            minx=(*xlistPlot)[i];
        }
        if((*xlistPlot)[i]>maxx){
            maxx=(*xlistPlot)[i];
        }
        if((*ylistPlot)[i]<miny){
            miny=(*ylistPlot)[i];
        }
        if((*ylistPlot)[i]>maxy){
            maxy=(*ylistPlot)[i];
        }
    }

    axisxLog->setRange(minx,maxx);   //设置x轴范围
    axisxLog->setBase(10.0);
    qChartView->chart()->setAxisX(axisxLog); //把刻度值传入进视图m_chart中显示
    qChartView->chart()->series()[0]->attachAxis(axisxLog);
}


void PlotUtils::x_line(){



    axisx->setTitleText(xlable);

    double minx=(*xlistPlot)[0],maxx=(*xlistPlot)[0],miny=(*ylistPlot)[0],maxy=(*ylistPlot)[0];
    for(int i=1;i<lengthPlotData;i++){
        if((*xlistPlot)[i]<minx){
            minx=(*xlistPlot)[i];
        }
        if((*xlistPlot)[i]>maxx){
            maxx=(*xlistPlot)[i];
        }
        if((*ylistPlot)[i]<miny){
            miny=(*ylistPlot)[i];
        }
        if((*ylistPlot)[i]>maxy){
            maxy=(*ylistPlot)[i];
        }
    }

    axisx->setRange(minx,maxx);   //设置x轴范围
    qChartView->chart()->setAxisX(axisx); //把刻度值传入进视图m_chart中显示
    qChartView->chart()->series()[0]->attachAxis(axisx);
}

//显示竖线
void PlotUtils::showShuxian(){
    seriesLine =new QLineSeries();
    seriesDataLine.append(QPointF(0, 0));
    seriesDataLine.append(QPointF(1, 1));
    seriesLine->append(seriesDataLine);
    qChartView->chart()->addSeries(seriesLine);
}







