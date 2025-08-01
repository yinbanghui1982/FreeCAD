#include "calibration.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"
#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QFile>


using namespace SoundTest;


Calibration::Calibration(Ui_WidgetSoundTest* ui,QStandardItemModel* modelTongdao,Config* config)
{
    this->ui=ui;
    this->modelTongdao=modelTongdao;
    selectedChannel=1;
    this->config=config;    
}

void Calibration::saveConfig()
{
    //将通道设置保存到文件
    QFile file(config->filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 处理错误，例如可以抛出异常或者返回错误标志
        return;
    }

    QTextStream out(&file);
    QString outText="";
    for(int i=0;i<4;i++){
        QModelIndex index1=ui->tableViewTongdao->model()->index(i,1);
        QString linmingdu1 = ui->tableViewTongdao->model()->data(index1).toString();
        // QModelIndex index2=ui->tableViewTongdao->model()->index(i,2);
        int j = ((QComboBox*)(ui->tableViewTongdao->indexWidget(ui->tableViewTongdao->model()->index(i, 2))))->currentIndex();
        // QString danwei1 = ui->tableViewTongdao->model()->data(index2).toString();
        QString danwei1 =QString::number(j);

        if (i!=3)
            outText=outText+linmingdu1+","+danwei1+"\n";
        else
            outText=outText+linmingdu1+","+danwei1;
    }

    out << outText;
    file.close();
}

// #include "moc_calibration.cpp"



