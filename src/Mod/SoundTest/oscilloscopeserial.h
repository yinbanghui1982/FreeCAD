/*
串口示波器
*/

#ifndef OSCILLOSCOPESERIAL_H
#define OSCILLOSCOPESERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include "oscilloscope.h"

namespace SoundTest {

class Ui_WidgetSoundTest;
class OscilloscopeSerial: public Oscilloscope
{
    Q_OBJECT

public:
    OscilloscopeSerial(Ui_WidgetSoundTest* ui);
    void start_shibo();
    void resetOscilloscope();
    void on_pushButtonCaiyang_clicked();
    void saveData();

private Q_SLOTS:
    void receiveData();

private:
    // 串口
    QSerialPort*  myPort;

};
} // namespace SoundTest
#endif // OSCILLOSCOPESERIAL_H
