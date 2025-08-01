#ifndef PLOTUTILS_H
#define PLOTUTILS_H
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>

namespace SoundTest {

class PlotUtils
{
public:
    PlotUtils();
    void chart_plot(QList<double>* xlist,QList<double>* ylist, int length,QString title,
                    QString xlable,QString ylable);
    void x_log();
    void x_line();
    void showShuxian();
    QChartView* qChartView;

    //----------------------------------
    //数据
    int lengthData;             //数据长度
    QList<double> *xlistData;
    QList<QList<double>*> *ylistList;

    //绘图
    int lengthPlotData;
    QList<double>* xlistPlot;
    QList<double>* ylistPlot;

    QValueAxis  *axisx =  new  QValueAxis();
    QLogValueAxis  *axisxLog =  new  QLogValueAxis();


private:

    //绘图
    QLineSeries *series;        //图片上的线
    QList<QPointF> seriesData;  //数据列表
    QString title;
    QString xlable;
    QString ylable;


    //直线
    QLineSeries *seriesLine;
    QList<QPointF> seriesDataLine;

    // QLogValueAxis  *axisxLog;

};
} // namespace SoundTest
#endif // PLOTUTILS_H
