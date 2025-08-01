#include "oscilloscope.h"
#include "WidgetSoundTest.h"
#include "ui_WidgetSoundTest.h"

using namespace SoundTest;


Oscilloscope::Oscilloscope(Ui_WidgetSoundTest* ui) {
    this->ui=ui;
    this->shiboLengthIndex=1;
    this->samplingLengthIndex=1;
}


void Oscilloscope::start_shibo(){}
void Oscilloscope::resetOscilloscope(){}
void Oscilloscope::receiveData(){}
void Oscilloscope::saveData(){}
void Oscilloscope::run(){}
void Oscilloscope::changeFs(int index){}
void Oscilloscope::setAcDcIepe(int channel,int index){}
