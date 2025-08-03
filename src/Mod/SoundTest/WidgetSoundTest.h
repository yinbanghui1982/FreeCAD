
#ifndef WidgetSoundTest_H
#define WidgetSoundTest_H

// #pragma push_macro("Q_SLOTS")
// #undef Q_SLOTS
// #include "Python.h"
// #define Q_SLOTS Q_Q_SLOTS
// #pragma pop_macro("Q_SLOTS")

#include <memory>
#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QComboBox>
#include <QButtonGroup>
#include <QAbstractTableModel>
#include <QDialog>
#include <QItemDelegate>
#include <QList>
#include <QObject>

#include "device.h"
#include "calibration.h"
#include "oscilloscope.h"
#include "oscilloscopeethenet.h"
#include "inputdata.h"
#include "analysis.h"
#include "config.h"



namespace SoundTest {


class Ui_WidgetSoundTest;
class WidgetSoundTest : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSoundTest(QWidget* parent = nullptr);
    ~WidgetSoundTest() override;
    QStringList* danweiList;


private:
    Ui_WidgetSoundTest* ui;


    //配置对象
    Config *config;

    //连接对象
    Device* device;
    QStandardItemModel* modelShebei;
    QStandardItemModel* modelTongdao;

    //校准对象
    Calibration* calibration;

    //示波器对象
    Oscilloscope* oscilloscope;

    //读取数据对象
    InputData* inputData;

    //分析对象
    Analysis* analysis;

    //选择示波长度
    int selectedShiboLengthItem=0;
    int shiboLengthList[4]={1024,2048,4096,8192};


    //选择采样长度
    int selectedCaiyangLengthItem=0;
    int samplingLengthList[6]={1024,2048,4096,8192,0,0};


    QList<int> channelListCpsd;
    QList<int> channelListXcorr;
    QThread *oscilloscopeThread;

    void updateLingmingdu();

    QComboBox* comboBox[4];

    QButtonGroup *qButtonGroup1,*qButtonGroup2,*qButtonGroup3,*qButtonGroup4;

    int shibo_now;
    int openDataFile(int* length, QList<double>* xlist,QList<QList<double>*> *ylistList,QList<QString>* channelUnitList);


private Q_SLOTS:
    void on_pushButtonShaomiao_clicked();
    void on_pushButtonSellect_clicked();
    void on_pushButtonShibo_clicked();
//     void on_pushButtonCaiyang_clicked();

//     void on_pushButtonOpenTimeFile_clicked();

//     void on_radioButtonTimeChannel1_clicked();

//     void on_radioButtonFreqChannel1_clicked();

//     void on_radioButtonTimeChannel2_clicked();

//     void on_radioButtonTimeChannel3_clicked();

//     void on_radioButtonTimeChannel4_clicked();

//     void on_pushButtonOpenFreqFile_clicked();

//     void on_radioButtonFreqChannel2_clicked();

//     void on_radioButtonFreqChannel3_clicked();

//     void on_radioButtonFreqChannel4_clicked();

//     void on_pushButtonOpenPsdFile_clicked();

//     void on_radioButtonPsdChannel1_clicked();

//     void on_radioButtonPsdChannel2_clicked();

//     void on_radioButtonPsdChannel3_clicked();

//     void on_radioButtonPsdChannel4_clicked();

//     void on_pushButtonOpenCpsdFile_clicked();

//     void on_pushButtonCpsdAnalysis_clicked();

//     void on_pushButtonOpenCorrFile_clicked();

//     void on_radioButtonCorrChannel1_clicked();

//     void on_radioButtonCorrChannel2_clicked();

//     void on_radioButtonCorrChannel3_clicked();

//     void on_radioButtonCorrChannel4_clicked();

//     void on_pushButtonOpenXcorrFile_clicked();

//     void on_pushButtonXcorrAnalysis_clicked();

//     void on_pushButtonOpenOneThirdFile_clicked();

//     void on_radioButtonOneThirdChannel1_clicked();

//     void on_radioButtonOneThirdChannel2_clicked();

//     void on_radioButtonOneThirdChannel3_clicked();

//     void on_radioButtonOneThirdChannel4_clicked();

//     void on_pushButtonOpenDaopuFile_clicked();

//     // void on_pushButtonOpenDaopuFile2_clicked();

//     void on_radioButtonDaopuChannel1_clicked();

//     void on_radioButtonDaopuChannel2_clicked();

//     void on_radioButtonDaopuChannel3_clicked();

//     void on_radioButtonDaopuChannel4_clicked();

//     // void on_pushButtonXcorrAnalysis2_clicked();

//     void on_toolButtonBig_clicked();

//     void on_pushButtonXLog_clicked();

//     void on_pushButtonXLine_clicked();

//     void on_comboBoxShiboLength_currentIndexChanged(int index);

//     void on_comboBoxCaiyangLength_currentIndexChanged(int index);

//     void on_pushButtonShowShuxian_clicked();

//     void on_toolButtonSaveToZhantieban_clicked();

//     void on_toolButtonSaveToZhantieban_triggered(QAction *arg1);

//     void on_pushButtonZhantiebanTime_clicked();

//     void on_pushButtonZhantiebanFreq_clicked();

//     void on_pushButtonZhantiebanPsd_clicked();

//     void on_pushButtonZhantiebanCpsd_clicked();

//     void on_pushButtonZhantiebanCorr_clicked();

//     void on_pushButtonZhantiebanXcorr_clicked();

//     void on_pushButtonZhantiebanOnethird_clicked();

//     void on_pushButtonZhantiebanDaopu_clicked();

//     void on_horizontalSliderTime_valueChanged(int value);

//     void on_horizontalSliderTime_sliderReleased();

//     void on_pushButtonStopShibo_clicked();

//     void finish_caiyang();

//     void on_radioButtonCelibration1_clicked();
//     void on_radioButtonCelibration2_clicked();
//     void on_radioButtonCelibration3_clicked();
//     void on_radioButtonCelibration4_clicked();
//     void on_pushButtonStartCelibration_clicked();
//     void on_action_guanyu_triggered();
//     void on_action_help_triggered();
//     void on_comboBoxFs_currentIndexChanged(int index);
//     void on_pushButtonShowWave_clicked();

//     void finish_celibrate();
//     void on_pushButtonDaochu_clicked();
//     void on_radioButtonAC1_clicked();
//     void on_radioButtonDC1_clicked();
//     void on_radioButtonIepe1_clicked();
//     void on_radioButtonAC2_clicked();
//     void on_radioButtonDC2_clicked();
//     void on_radioButtonIepe2_clicked();
//     void on_radioButtonAC3_clicked();
//     void on_radioButtonDC3_clicked();
//     void on_radioButtonIepe3_clicked();
//     void on_radioButtonAC4_clicked();
//     void on_radioButtonDC4_clicked();
//     void on_radioButtonIepe4_clicked();


Q_SIGNALS:
    void sig_shibo();
//     void sig_change_fs(int index);
//     void sig_start_calibrate();
//     void sig_set_ac_dc_iepe(int channel,int index);


};

} // namespace SoundTest

#endif // WidgetSoundTest_H
