
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include <iostream>
#include <Base/Console.h>

using namespace SoundTest;


// --------------------------------------------------------------

/* TRANSLATOR Gui::WidgetSoundTest */

WidgetSoundTest::WidgetSoundTest(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui_WidgetSoundTest)
{
    ui->setupUi(this);  
    // connect(ui->pushButton, &QPushButton::clicked, this, &WidgetSoundTest::on_pushButton_clicked);

    //----------------------------------------------------------------
    // python test

    // Py_Initialize();
    // PyRun_SimpleString("import sys");
    // PyRun_SimpleString("sys.argv = ['python.py']");
    // PyRun_SimpleString("sys.path.append('./')");

    // PyRun_SimpleString("print('success')");
    // qDebug()<<("python:"+std::string(Py_GetVersion())+"\n");
    // import_array();

    // uchar *CArrays = nullptr;
    // int x=2;
    // int y=2;
    // int z=2;
    // CArrays = new uchar[(x+1000)*(y+1)*(z+1)];
    // CArrays[0]=50;

    // npy_intp Dims[3] = {x, y, z};
    // PyObject *PyArray = PyArray_SimpleNewFromData(3, Dims, NPY_UBYTE, CArrays);
    // delete[] CArrays;

    // PyObject* pModule = PyImport_ImportModule("add2");
    // PyObject* pFunc= PyObject_GetAttrString(pModule,"add3");

    // PyObject *ArgArray = nullptr;
    // ArgArray = PyTuple_New(2);
    // PyTuple_SetItem(ArgArray, 0, PyLong_FromLong(1L));
    // PyTuple_SetItem(ArgArray, 1, PyLong_FromLong(1L));

    // PyObject *pResult = PyObject_CallObject(pFunc, ArgArray);

    // int size = PyList_Size(pResult);
    // PyObject *list_item = PyList_GetItem(pResult, 0);
    // float upper_left_coord_x;
    // PyArg_Parse(list_item, "f", &upper_left_coord_x);

    // Py_Finalize();


    //----------------------------------------------------------------
    // 读取配置文件
    config=new Config();
    danweiList=new QStringList();
    danweiList->append("mV/Pa");
    danweiList->append("mV/mV");
    danweiList->append("mV/(m/s^2)");


    //----------------------------------------------------------------
    //设备对象
    modelShebei=new QStandardItemModel(this);
    modelTongdao=new QStandardItemModel(this);
    device=new Device(ui,modelShebei);


     //----------------------------------------------------------------
     //校准对象
     calibration=new Calibration(ui,modelTongdao,config);

     updateLingmingdu();

    // //----------------------------------------------------------------
    // //示波器对象
    // // oscilloscope=new OscilloscopeSerial(ui);
    // oscilloscope=new OscilloscopeEthenet(ui,danweiList);
    // oscilloscope->device=device;
    // oscilloscope->shiboLength=shiboLengthList[0];

    // // 采样长度列表
    // int caiyangTime[2]={2,10};
    // for (int i=4;i<6;i++){
    //     samplingLengthList[i]=qPow(2,ceil(qLn(caiyangTime[i-4]*60*oscilloscope->samplingRate)/qLn(2)));
    // }

    // oscilloscope->samplingLength=samplingLengthList[0];

    // oscilloscope->start();

    // oscilloscopeThread=new QThread();
    // oscilloscopeThread->start();
    // oscilloscope->moveToThread(oscilloscopeThread);
    // //----------------------------------------------------------------
    // //示波器绘图对象

    // OscilloscopePlot *oscilloscopePlot = new OscilloscopePlot();
    // ((OscilloscopeEthenet*)oscilloscope)->oscilloscopePlot=oscilloscopePlot;

    // oscilloscopePlot->xlist=&oscilloscope->xlist;
    // oscilloscopePlot->ylist1=&oscilloscope->ylist1;
    // oscilloscopePlot->ylist2=&oscilloscope->ylist2;
    // oscilloscopePlot->ylist3=&oscilloscope->ylist3;
    // oscilloscopePlot->ylist4=&oscilloscope->ylist4;

    // connect((OscilloscopeEthenet*)oscilloscope, &OscilloscopeEthenet::sig_plot_data,
    //         oscilloscopePlot,&OscilloscopePlot::plotData,Qt::QueuedConnection);

    // connect(this,&WidgetSoundTest::sig_shibo,
    //         (OscilloscopeEthenet*)oscilloscope, &OscilloscopeEthenet::start_shibo);

    // connect(oscilloscope,&Oscilloscope::sig_finish_caiyang,
    //         this, &WidgetSoundTest::finish_caiyang);

    // connect(this, &WidgetSoundTest::sig_change_fs,
    //         oscilloscope, &Oscilloscope::changeFs);

    // connect((OscilloscopeEthenet*)oscilloscope, &OscilloscopeEthenet::sig_finish_celibrate,
    //         this, &WidgetSoundTest::finish_celibrate);

    // //------------------------------------------------------------
    // // 分析控件
    // analysis=new Analysis(ui);

    // analysis->plotUtilsChannel1=new PlotUtils();
    // analysis->plotUtilsChannel1->qChartView=ui->graphicsView1;

    // analysis->plotUtilsChannel2=new PlotUtils();
    // analysis->plotUtilsChannel2->qChartView=ui->graphicsView2;

    // analysis->plotUtilsChannel3=new PlotUtils();
    // analysis->plotUtilsChannel3->qChartView=ui->graphicsView3;

    // analysis->plotUtilsChannel4=new PlotUtils();
    // analysis->plotUtilsChannel4->qChartView=ui->graphicsView4;

    // analysis->plotUtilsTime=new PlotUtils();
    // analysis->plotUtilsTime->qChartView=ui->graphicsViewTimeAnalysis;

    // analysis->plotUtilsFreq=new PlotUtils();
    // analysis->plotUtilsFreq->qChartView=ui->graphicsViewFreqAnalysis;

    // analysis->plotUtilsPsd=new PlotUtils();
    // analysis->plotUtilsPsd->qChartView=ui->graphicsViewPsdAnalysis;

    // analysis->plotUtilsCpsd1=new PlotUtils();
    // analysis->plotUtilsCpsd1->qChartView=ui->graphicsViewCpsdAnalysis1;

    // analysis->plotUtilsCpsd2=new PlotUtils();
    // analysis->plotUtilsCpsd2->qChartView=ui->graphicsViewCpsdAnalysis2;

    // analysis->plotUtilsCorr=new PlotUtils();
    // analysis->plotUtilsCorr->qChartView=ui->graphicsViewCorrAnalysis;

    // analysis->plotUtilsXcorr=new PlotUtils();
    // analysis->plotUtilsXcorr->qChartView=ui->graphicsViewXcorrAnalysis;

    // analysis->plotUtilsOneThird=new PlotUtils();
    // analysis->plotUtilsOneThird->qChartView=ui->graphicsViewOneThirdAnalys;

    // analysis->plotUtilsDaopu=new PlotUtils();
    // analysis->plotUtilsDaopu->qChartView=ui->graphicsViewDaopuAnalys;

    // analysis->plotUtilsCeliTime=new PlotUtils();
    // analysis->plotUtilsCeliTime->qChartView=ui->graphicsViewCeliTime;

    // analysis->plotUtilsCeliFreq=new PlotUtils();
    // analysis->plotUtilsCeliFreq->qChartView=ui->graphicsViewCeliFreq;

    // oscilloscope->analysis=analysis;



    // //------------------------------------------------------------
    // // 读取数据对象
    // inputData=new InputData(this,ui);

    // //------------------------------------------------------------
    // // 通道设置ratiobutton分组
    // qButtonGroup1=new QButtonGroup(this);
    // qButtonGroup1->addButton(ui->radioButtonIepe1,0);
    // qButtonGroup1->addButton(ui->radioButtonAC1,1);
    // qButtonGroup1->addButton(ui->radioButtonDC1,2);

    // qButtonGroup2=new QButtonGroup(this);
    // qButtonGroup2->addButton(ui->radioButtonIepe2,0);
    // qButtonGroup2->addButton(ui->radioButtonAC2,1);
    // qButtonGroup2->addButton(ui->radioButtonDC2,2);

    // qButtonGroup3=new QButtonGroup(this);
    // qButtonGroup3->addButton(ui->radioButtonIepe3,0);
    // qButtonGroup3->addButton(ui->radioButtonAC3,1);
    // qButtonGroup3->addButton(ui->radioButtonDC3,2);

    // qButtonGroup4=new QButtonGroup(this);
    // qButtonGroup4->addButton(ui->radioButtonIepe4,0);
    // qButtonGroup4->addButton(ui->radioButtonAC4,1);
    // qButtonGroup4->addButton(ui->radioButtonDC4,2);

    // connect(this,&WidgetSoundTest::sig_set_ac_dc_iepe,
    //         (OscilloscopeEthenet*)oscilloscope, &OscilloscopeEthenet::setAcDcIepe);

    // ui->radioButtonIepe1->click();
    // ui->radioButtonIepe2->click();
    // ui->radioButtonIepe3->click();
    // ui->radioButtonIepe4->click();
}

 WidgetSoundTest::~WidgetSoundTest()
 {
     //calibration->saveConfig();
     //delete ui;
 }


void WidgetSoundTest::on_pushButtonShaomiao_clicked()
{
    device->on_pushButtonShaomiao_clicked();
}


void WidgetSoundTest::on_pushButtonSellect_clicked()
{
    device->on_pushButtonSellect_clicked();
}

void WidgetSoundTest::on_pushButtonShibo_clicked()
{
    // oscilloscope->on_pushButtonShibo_clicked();
    if(shibo_now==1)
        return;

    oscilloscope->shiboState=0;
    shibo_now=1;    //正在示波
    Q_EMIT sig_shibo();
}

// void WidgetSoundTest::on_pushButtonCaiyang_clicked()
// {
//     if (shibo_now==1){
//         on_pushButtonStopShibo_clicked();
//         QThread::msleep(100);
//     }
//     // oscilloscope->on_pushButtonCaiyang_clicked();
//     oscilloscope->shiboState=1;
//     oscilloscope->shiboLength=oscilloscope->samplingLength;
//     oscilloscope->shiboLengthIndex=oscilloscope->samplingLengthIndex;
//     Q_EMIT sig_shibo();
// }


// void WidgetSoundTest::on_pushButtonOpenTimeFile_clicked()
// {
//     int i=openDataFile(&analysis->length_time,analysis->xlist_time,analysis->ylistlist_time,analysis->channelUnitList_time);

//     if (i==0){
//         analysis->timeAnalysis(0);
//         analysis->channel=0;
//         ui->radioButtonTimeChannel1->click();
//     }
// }

// int WidgetSoundTest::openDataFile(int* length, QList<double>* xlist,QList<QList<double>*> *ylistList,QList<QString>* channelUnitList)
// {
//     inputData->length=length;
//     inputData->xlist=xlist;
//     inputData->ylistList=ylistList;
//     inputData->channelUnitList=channelUnitList;
//     int i=inputData->readDataFile();

//     return i;
// }

// void WidgetSoundTest::on_radioButtonTimeChannel1_clicked()
// {
//     analysis->timeAnalysis(0);
//     analysis->channel=0;
// }


// void WidgetSoundTest::on_radioButtonTimeChannel2_clicked()
// {
//     analysis->timeAnalysis(1);
//     analysis->channel=1;
// }


// void WidgetSoundTest::on_radioButtonTimeChannel3_clicked()
// {
//     analysis->timeAnalysis(2);
//     analysis->channel=2;
// }


// void WidgetSoundTest::on_radioButtonTimeChannel4_clicked()
// {
//     analysis->timeAnalysis(3);
//     analysis->channel=3;
// }


// void WidgetSoundTest::on_pushButtonOpenFreqFile_clicked()
// {
//     int i=openDataFile(&analysis->length_freq,analysis->xlist_freq,analysis->ylistlist_freq,analysis->channelUnitList_freq);

//     if (i==0){
//         analysis->state_freq=0;
//         analysis->freqAnalysis(0);
//         ui->radioButtonFreqChannel1->click();
//     }
// }

// void WidgetSoundTest::on_radioButtonFreqChannel1_clicked()
// {
//     analysis->state_freq=0;
//     analysis->freqAnalysis(0);
// }

// void WidgetSoundTest::on_radioButtonFreqChannel2_clicked()
// {
//     analysis->state_freq=0;
//     analysis->freqAnalysis(1);
// }


// void WidgetSoundTest::on_radioButtonFreqChannel3_clicked()
// {
//     analysis->state_freq=0;
//     analysis->freqAnalysis(2);
// }


// void WidgetSoundTest::on_radioButtonFreqChannel4_clicked()
// {
//     analysis->state_freq=0;
//     analysis->freqAnalysis(3);
// }

// void WidgetSoundTest::on_pushButtonOpenPsdFile_clicked()
// {

//     int i=openDataFile(&analysis->length_psd,analysis->xlist_psd,analysis->ylistlist_psd,analysis->channelUnitList_psd);

//     if (i==0){
//         analysis->psdAnalysis(0);
//         ui->radioButtonPsdChannel1->click();
//     }
// }


// void WidgetSoundTest::on_radioButtonPsdChannel1_clicked()
// {
//     analysis->psdAnalysis(0);
// }


// void WidgetSoundTest::on_radioButtonPsdChannel2_clicked()
// {
//     analysis->psdAnalysis(1);
// }


// void WidgetSoundTest::on_radioButtonPsdChannel3_clicked()
// {
//     analysis->psdAnalysis(2);
// }


// void WidgetSoundTest::on_radioButtonPsdChannel4_clicked()
// {
//     analysis->psdAnalysis(3);
// }


// void WidgetSoundTest::on_pushButtonOpenCpsdFile_clicked()
// {                                                                                               
//     int i=openDataFile(&analysis->length_cpsd,analysis->xlist_cpsd,analysis->ylistlist_cpsd,analysis->channelUnitList_cpsd);

//     if (i==0){
//         QMessageBox::information(NULL,  "消息",  "已打开数据", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//     }
// }


// void WidgetSoundTest::on_pushButtonCpsdAnalysis_clicked()
// {
//     channelListCpsd.clear();
//     if (ui->checkBoxCpsdChannel1->isChecked())
//         channelListCpsd.append(0);
//     if (ui->checkBoxCpsdChannel2->isChecked())
//         channelListCpsd.append(1);
//     if (ui->checkBoxCpsdChannel3->isChecked())
//         channelListCpsd.append(2);
//     if (ui->checkBoxCpsdChannel4->isChecked())
//         channelListCpsd.append(3);

//     if (channelListCpsd.count()!=2){
//         QMessageBox::information(NULL,  "Title",  "请选择2个通道", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//         return;
//     } else {
//         analysis->cpsdAnalysis(&channelListCpsd);
//     }
// }



// void WidgetSoundTest::on_pushButtonOpenCorrFile_clicked()
// {
//     int i=openDataFile(&analysis->length_corr,analysis->xlist_corr,analysis->ylistlist_corr,analysis->channelUnitList_corr);

//     if (i==0){
//         analysis->corrAnalysis(0);
//         ui->radioButtonCorrChannel1->click();
//     }
// }


// void WidgetSoundTest::on_radioButtonCorrChannel1_clicked()
// {
//     analysis->corrAnalysis(0);
// }


// void WidgetSoundTest::on_radioButtonCorrChannel2_clicked()
// {
//     analysis->corrAnalysis(1);
// }


// void WidgetSoundTest::on_radioButtonCorrChannel3_clicked()
// {
//     analysis->corrAnalysis(2);
// }


// void WidgetSoundTest::on_radioButtonCorrChannel4_clicked()
// {
//     analysis->corrAnalysis(3);
// }


// void WidgetSoundTest::on_pushButtonOpenXcorrFile_clicked()
// {  
//     int i=openDataFile(&analysis->length_xcorr,analysis->xlist_xcorr,analysis->ylistlist_xcorr,analysis->channelUnitList_xcorr);

//     if (i==0){
//         QMessageBox::information(NULL,  "Title",  "已打开数据", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//     }
// }


// void WidgetSoundTest::on_pushButtonXcorrAnalysis_clicked()
// {
//     qDebug()<<"xcorr";
//     // QList<int> channelListXcorr;
//     channelListXcorr.clear();
//     if (ui->checkBoxXcorrChannel1->isChecked())
//         channelListXcorr.append(0);
//     if (ui->checkBoxXcorrChannel2->isChecked())
//         channelListXcorr.append(1);
//     if (ui->checkBoxXcorrChannel3->isChecked())
//         channelListXcorr.append(2);
//     if (ui->checkBoxXcorrChannel4->isChecked())
//         channelListXcorr.append(3);

//     if (channelListXcorr.count()!=2){
//         QMessageBox::information(NULL,  "Title",  "请选择2个通道", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//         return;
//     } else {
//         analysis->xcorrAnalysis(&channelListXcorr);
//     }
// }


// void WidgetSoundTest::on_pushButtonOpenOneThirdFile_clicked()
// {
//     int i=openDataFile(&analysis->length_onethird,analysis->xlist_onethird,analysis->ylistlist_onethird,analysis->channelUnitList_onethird);

//     if (i==0){
//         analysis->onethirdAnalysis(0);
//         ui->radioButtonOneThirdChannel1->click();
//     }
// }


// void WidgetSoundTest::on_radioButtonOneThirdChannel1_clicked()
// {
//     analysis->onethirdAnalysis(0);
// }


// void WidgetSoundTest::on_radioButtonOneThirdChannel2_clicked()
// {
//     analysis->onethirdAnalysis(1);
// }


// void WidgetSoundTest::on_radioButtonOneThirdChannel3_clicked()
// {
//     analysis->onethirdAnalysis(2);
// }


// void WidgetSoundTest::on_radioButtonOneThirdChannel4_clicked()
// {
//     analysis->onethirdAnalysis(3);
// }


// void WidgetSoundTest::on_pushButtonOpenDaopuFile_clicked()
// {
//     int i=openDataFile(&analysis->length_daopu,analysis->xlist_daopu,analysis->ylistlist_daopu,analysis->channelUnitList_daopu);

//     if (i==0){
//         analysis->daopuAnalysis(0);
//         ui->radioButtonDaopuChannel1->click();
//     }
// }


// // void WidgetSoundTest::on_pushButtonOpenDaopuFile2_clicked()
// // {
// //     qDebug()<<"daopu";
// // }


// void WidgetSoundTest::on_radioButtonDaopuChannel1_clicked()
// {
//     analysis->daopuAnalysis(0);
// }

// void WidgetSoundTest::on_radioButtonDaopuChannel2_clicked()
// {
//     analysis->daopuAnalysis(1);
// }

// void WidgetSoundTest::on_radioButtonDaopuChannel3_clicked()
// {
//     analysis->daopuAnalysis(2);
// }


// void WidgetSoundTest::on_radioButtonDaopuChannel4_clicked()
// {
//     analysis->daopuAnalysis(3);
// }


// // void WidgetSoundTest::on_pushButtonXcorrAnalysis2_clicked()
// // {

// // }


// void WidgetSoundTest::on_toolButtonBig_clicked()
// {

// }


// void WidgetSoundTest::on_pushButtonXLog_clicked()
// {
//     analysis->plotUtilsOneThird->x_log();
// }


// void WidgetSoundTest::on_pushButtonXLine_clicked()
// {
//     analysis->plotUtilsOneThird->x_line();
// }

// /*
//     选择示波长度
// */
// void WidgetSoundTest::on_comboBoxShiboLength_currentIndexChanged(int index)
// {
//     qDebug()<<index;
//     selectedShiboLengthItem=index;
//     oscilloscope->shiboLengthIndex=index;
//     oscilloscope->shiboLength=shiboLengthList[selectedShiboLengthItem];
//     oscilloscope->changedShiboLength=1;
// }

// /*
//     选择采样长度
// */
// void WidgetSoundTest::on_comboBoxCaiyangLength_currentIndexChanged(int index)
// {
//     qDebug()<<index;
//     selectedCaiyangLengthItem=index;
//     oscilloscope->samplingLength=samplingLengthList[index];
//     oscilloscope->samplingLengthIndex=index;
// }


// void WidgetSoundTest::on_pushButtonShowShuxian_clicked()
// {
//     qDebug()<<"显示竖线";
//     analysis->on_pushButtonShowShuxian_clicked();

// }


// void WidgetSoundTest::on_toolButtonSaveToZhantieban_clicked()
// {
//     QString startText=this->ui->lineEditStartTime->text();
//     qDebug()<<startText;

//     double startTime=startText.toDouble();
//     int length;
//     int lengthList[4]={1024,2048,4096,8192};
//     int lengthIndex=ui->comboBoxPoints->currentIndex();
//     length=lengthList[lengthIndex];

//     qDebug()<<length;
//     analysis->setZhantieban(startTime,length);

// }


// void WidgetSoundTest::on_toolButtonSaveToZhantieban_triggered(QAction *arg1){}


// //从粘贴板读取数据，然后重新进行绘图
// void WidgetSoundTest::on_pushButtonZhantiebanTime_clicked()
// {
//     analysis->getZhantiebanTime();
//     analysis->timeAnalysis(0);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanFreq_clicked()
// {
//     analysis->getZhantiebanFreq();
//     analysis->freqAnalysis(0);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanPsd_clicked()
// {
//     analysis->getZhantiebanPsd();
//     analysis->psdAnalysis(0);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanCpsd_clicked()
// {
//     analysis->getZhantiebanCpsd();
//     QMessageBox::information(NULL,  "Title",  "已打开数据", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanCorr_clicked()
// {
//     analysis->getZhantiebanCorr();
//     analysis->corrAnalysis(0);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanXcorr_clicked()
// {
//     analysis->getZhantiebanXcorr();
//     QMessageBox::information(NULL,  "Title",  "已打开数据", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanOnethird_clicked()
// {
//     analysis->getZhantiebanOnethird();
//     analysis->onethirdAnalysis(0);
// }


// void WidgetSoundTest::on_pushButtonZhantiebanDaopu_clicked()
// {
//     analysis->getZhantiebanDaopu();
//     analysis->daopuAnalysis(0);
// }


// void WidgetSoundTest::on_horizontalSliderTime_valueChanged(int value)
// {

// }


// void WidgetSoundTest::on_horizontalSliderTime_sliderReleased()
// {
//     analysis->step_start=analysis->length_time*ui->horizontalSliderTime->value()/100;
//     analysis->timeAnalysis(analysis->channel);
// }


// void WidgetSoundTest::on_pushButtonStopShibo_clicked()
// {
//     oscilloscope->stopShibo=1;
//     shibo_now=0;
// }

// void WidgetSoundTest::finish_caiyang()
// {
//     QMessageBox::information(NULL,  "Title",  "采样完成", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
// }


// void WidgetSoundTest::on_radioButtonCelibration1_clicked()
// {
//     calibration->selectedChannel=1;
// }


// void WidgetSoundTest::on_radioButtonCelibration2_clicked()
// {
//     calibration->selectedChannel=2;
// }


// void WidgetSoundTest::on_radioButtonCelibration3_clicked()
// {
//     calibration->selectedChannel=3;
// }


// void WidgetSoundTest::on_radioButtonCelibration4_clicked()
// {
//     calibration->selectedChannel=4;
// }


// void WidgetSoundTest::on_action_guanyu_triggered()
// {
//     QMessageBox::information(NULL,  "关于",  "振动噪声测试分析仪1.0");
// }


// void WidgetSoundTest::on_action_help_triggered()
// {
//     QString currentPath = QCoreApplication::applicationDirPath(); //获取当前项目路径
//     QString filePath = QString("%1/help.pdf").arg(currentPath); //文件绝对路径
//     QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
// }

// void WidgetSoundTest::on_comboBoxFs_currentIndexChanged(int index)
// {
//     if (shibo_now==1){
//         on_pushButtonStopShibo_clicked();
//         QThread::msleep(100);
//     }

//     int i=this->ui->comboBoxFs->currentIndex();
//     Q_EMIT sig_change_fs(i);
//     // QThread::msleep(300);
//     // on_pushButtonStopShibo_clicked();

// }

// void WidgetSoundTest::on_pushButtonShowWave_clicked()
// {
//     oscilloscope->shiboState=2;
//     oscilloscope->shiboLength=1024;
//     oscilloscope->shiboLengthIndex=0;
//     oscilloscope->celiChannel=calibration->selectedChannel;
//     Q_EMIT sig_shibo();
// }

// void WidgetSoundTest::on_pushButtonStartCelibration_clicked()
// {
//     oscilloscope->shiboState=3;
//     oscilloscope->shiboLength=1024;
//     oscilloscope->shiboLengthIndex=0;
//     oscilloscope->celiChannel=calibration->selectedChannel;
//     Q_EMIT sig_shibo();

// }


// void WidgetSoundTest::finish_celibrate()
// {
//     int channel=analysis->celiChannel;
//     double ppv=analysis->celiPpv;

//     QModelIndex index1=ui->tableViewTongdao->model()->index(channel,1);
//     QString linmingdu1 = ui->tableViewTongdao->model()->data(index1).toString();
//     // QModelIndex index2=ui->tableViewTongdao->model()->index(channel,2);
//     // QString danwei1 = ui->tableViewTongdao->model()->data(index2).toString();

//     int index_danwei = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(channel, 2))))->currentIndex();
//     QString danwei1=(*danweiList)[index_danwei];

//     if (danwei1=="mV/Pa"){
//         QString res="";
//         res=res+"测试峰峰值："+QString::number(ppv)+"Pa\t";
//         res=res+"校准器峰峰值：10.0237Pa\t";
//         res=res+"校准前灵敏度："+linmingdu1+danwei1+"\t";
//         double lingmingdu2=linmingdu1.toDouble()*ppv/10.0237;
//         config->lingmingduList[channel]=QString::number(lingmingdu2);
//         res=res+"校准后灵敏度:"+QString::number(lingmingdu2)+danwei1+"\t";
//         modelTongdao->setItem(channel, 1, new QStandardItem(config->lingmingduList[channel]));
//         ui->textEditCeliRes->setText(res);
//     }  else if (danwei1=="mV/(m/s^2)"){
//         QString res="";
//         res=res+"测试峰峰值："+QString::number(ppv)+"m/s^2\t";
//         res=res+"校准器峰峰值：4 m/s^2\t";
//         res=res+"校准前灵敏度："+linmingdu1+danwei1+"\t";
//         double lingmingdu2=linmingdu1.toDouble()*ppv/4;
//         config->lingmingduList[channel]=QString::number(lingmingdu2);
//         res=res+"校准后灵敏度:"+QString::number(lingmingdu2)+danwei1+"\t";
//         modelTongdao->setItem(channel, 1, new QStandardItem(config->lingmingduList[channel]));
//         ui->textEditCeliRes->setText(res);
//     }

// }


void WidgetSoundTest::updateLingmingdu()
{
    Config* config=calibration->config;

    //----------------------------------------------------------------
    //填充通道表
    /*设置列字段名*/
    modelTongdao->setColumnCount(3);
    modelTongdao->setHeaderData(0,Qt::Horizontal, "通道ID");
    modelTongdao->setHeaderData(1,Qt::Horizontal, "灵敏度");
    modelTongdao->setHeaderData(2,Qt::Horizontal, "灵敏度单位");

    /*设置行字段名*/
    // modelTongdao->setRowCount(3);
    // modelTongdao->setHeaderData(0,Qt::Vertical, "记录一");
    // modelTongdao->setHeaderData(1,Qt::Vertical, "记录二");
    // modelTongdao->setHeaderData(2,Qt::Vertical, "记录三");

    /*设置数据*/
    modelTongdao->setItem(0, 0, new QStandardItem("通道1"));
    modelTongdao->setItem(0, 1, new QStandardItem(config->lingmingduList[0]));
    modelTongdao->setItem(0, 2, new QStandardItem(config->lingmingduDanweiList[0]));

    modelTongdao->setItem(1, 0, new QStandardItem("通道2"));
    modelTongdao->setItem(1, 1, new QStandardItem(config->lingmingduList[1]));
    modelTongdao->setItem(1, 2, new QStandardItem(config->lingmingduDanweiList[1]));

    modelTongdao->setItem(2, 0, new QStandardItem("通道3"));
    modelTongdao->setItem(2, 1, new QStandardItem(config->lingmingduList[2]));
    modelTongdao->setItem(2, 2, new QStandardItem(config->lingmingduDanweiList[2]));

    modelTongdao->setItem(3, 0, new QStandardItem("通道4"));
    modelTongdao->setItem(3, 1, new QStandardItem(config->lingmingduList[3]));
    modelTongdao->setItem(3, 2, new QStandardItem(config->lingmingduDanweiList[3]));

    ui->tableViewTongdao->setModel(modelTongdao);

    int index;

    for (int i=0;i<4;i++){
        comboBox[i]=new QComboBox();
        for (int j=0;j<danweiList->length();j++){
            comboBox[i]->addItem((*danweiList)[j]);
        }
        index=config->lingmingduDanweiList[i].toInt();
        comboBox[i]->setCurrentIndex(index);
        ui->tableViewTongdao->setIndexWidget(modelTongdao->index(i, 2), comboBox[i]);
    }

}

// // 导出文本文件
// void WidgetSoundTest::on_pushButtonDaochu_clicked()
// {
//     analysis->export_time();
// }


// void WidgetSoundTest::on_radioButtonAC1_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(0,0);
// }


// void WidgetSoundTest::on_radioButtonDC1_clicked()
// {
//     Q_EMITIT sig_set_ac_dc_iepe(0,1);
// }


// void WidgetSoundTest::on_radioButtonIepe1_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(0,2);
// }


// void WidgetSoundTest::on_radioButtonAC2_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(1,0);
// }


// void WidgetSoundTest::on_radioButtonDC2_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(1,1);
// }


// void WidgetSoundTest::on_radioButtonIepe2_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(1,2);
// }


// void WidgetSoundTest::on_radioButtonAC3_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(2,0);
// }


// void WidgetSoundTest::on_radioButtonDC3_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(2,1);
// }


// void WidgetSoundTest::on_radioButtonIepe3_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(2,2);
// }


// void WidgetSoundTest::on_radioButtonAC4_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(3,0);
// }


// void WidgetSoundTest::on_radioButtonDC4_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(3,1);
// }


// void WidgetSoundTest::on_radioButtonIepe4_clicked()
// {
//     Q_EMIT sig_set_ac_dc_iepe(3,2);
// }



#include "moc_WidgetSoundTest.cpp"