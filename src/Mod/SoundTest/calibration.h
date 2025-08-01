#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "config.h"


namespace SoundTest {


class Ui_WidgetSoundTest;
class Calibration{

public:
    Calibration(Ui_WidgetSoundTest* ui,QStandardItemModel* modelTongdao,Config* config);
    void saveConfig();
    int selectedChannel;         //选定通道ip
    Config* config;

// private Q_SLOTS:
//     void on_comboBoxFs_currentIndexChanged(int index);

private:
    Ui_WidgetSoundTest* ui;
    int selectedChannelIndex;
    QStandardItemModel* modelTongdao;
};

} // namespace SoundTest
#endif // CALIBRATION_H
