#ifndef OSCILLOSCOPEETHENET_H
#define OSCILLOSCOPEETHENET_H
#include "oscilloscope.h"
#include <QTcpSocket>
#include <QThread>
#include "oscilloscopeplot.h"
#include <QComboBox>

namespace SoundTest {

class OscilloscopeEthenet: public Oscilloscope
{
    Q_OBJECT

public:
    OscilloscopeEthenet(Ui_WidgetSoundTest* ui,QStringList* danweiList);
    void start_shibo();
    // void resetOscilloscope();
    void saveData();
    void saveDataBit();
    QThread* plotThread;
    OscilloscopePlot *oscilloscopePlot;
    void changeFs(int index);
    void setAcDcIepe(int channel,int index);


protected:
    void run() override;

private Q_SLOTS:
    void receiveData();


private:
    QTcpSocket* socket;    
    QList<QString> dataList;
    
    int countTcp=0;         //接收数据的次数，16次为1024点
    int countBlock=0;       //接收数据的块数，每块1024点

    int firstShibo=0;       //第1次示波，0是，1否
    int countShibo=0;       //指示是否显示图像的计数器
    void startOscilloscope();

    double d1,d2,d3,d4;
    void plotData2();
    int receivedata_running=0;
    int send_sig=0;
    int creat_socket=0;
    int cnt_send=0;
    int index_danwei;
    QString datax;
    QString datay1,datay2,datay3,datay4;
    void newSocket();



Q_SIGNALS:
    void sig_plot_data(int shiboState,int channel);
    void sig_finish_celibrate();

};
} // namespace SoundTest
#endif // OSCILLOSCOPEETHENET_H
