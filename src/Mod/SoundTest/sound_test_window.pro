QT       += core gui printsupport charts serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console

win32:CONFIG(debug, debug|release): {
    QMAKE_CFLAGS_DEBUG += -MT
    QMAKE_CXXFLAGS_DEBUG += -MT
}
else:win32:CONFIG(release, debug|release): {
    QMAKE_CFLAGS_RELEASE += -MT
    QMAKE_CXXFLAGS_RELEASE += -MT
}

CONFIG(debug, debug|release) {
    # debug
    LIBS += -lonethird
} else {
    # release
    LIBS += -lonethird
}


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysis.cpp \
    calibration.cpp \
    config.cpp \
    corr.cpp \
    device.cpp \
    inputdata.cpp \
    iputils.cpp \
    libtdms-gpl-0.5/src/TdmsChannel.cpp \
    libtdms-gpl-0.5/src/TdmsGroup.cpp \
    libtdms-gpl-0.5/src/TdmsLeadIn.cpp \
    libtdms-gpl-0.5/src/TdmsMetaData.cpp \
    libtdms-gpl-0.5/src/TdmsObject.cpp \
    libtdms-gpl-0.5/src/TdmsParser.cpp \
    libtdms-gpl-0.5/src/TdmsSegment.cpp \
    main.cpp \
    mainwindow.cpp \
    matlab_files/codegen/lib/cpsd_analysis/FFTImplementationCallback.cpp \
    matlab_files/codegen/lib/cpsd_analysis/bsxfun.cpp \
    matlab_files/codegen/lib/cpsd_analysis/computeDFT.cpp \
    matlab_files/codegen/lib/cpsd_analysis/computepsd.cpp \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis.cpp \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_data.cpp \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_initialize.cpp \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_rtwutil.cpp \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_terminate.cpp \
    matlab_files/codegen/lib/cpsd_analysis/psdfreqvec.cpp \
    matlab_files/codegen/lib/cpsd_analysis/rtGetInf.cpp \
    matlab_files/codegen/lib/cpsd_analysis/rtGetNaN.cpp \
    matlab_files/codegen/lib/cpsd_analysis/rt_nonfinite.cpp \
    matlab_files/codegen/lib/cpsd_analysis/welch.cpp \
    matlab_files/codegen/lib/pingpu/FFTImplementationCallback.cpp \
    matlab_files/codegen/lib/pingpu/pingpu.cpp \
    matlab_files/codegen/lib/pingpu/pingpu_data.cpp \
    matlab_files/codegen/lib/pingpu/pingpu_initialize.cpp \
    matlab_files/codegen/lib/pingpu/pingpu_terminate.cpp \
    matlab_files/codegen/lib/psd_analysis/FFTImplementationCallback.cpp \
    matlab_files/codegen/lib/psd_analysis/bsxfun.cpp \
    matlab_files/codegen/lib/psd_analysis/computeDFT.cpp \
    matlab_files/codegen/lib/psd_analysis/computeperiodogram.cpp \
    matlab_files/codegen/lib/psd_analysis/psd_analysis.cpp \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_data.cpp \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_initialize.cpp \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_terminate.cpp \
    matlab_files/codegen/lib/psd_analysis/rtGetInf.cpp \
    matlab_files/codegen/lib/psd_analysis/rtGetNaN.cpp \
    matlab_files/codegen/lib/psd_analysis/rt_nonfinite.cpp \
    matlab_files/codegen/lib/time_anslysis/combineVectorElements.cpp \
    matlab_files/codegen/lib/time_anslysis/mean.cpp \
    matlab_files/codegen/lib/time_anslysis/minOrMax.cpp \
    matlab_files/codegen/lib/time_anslysis/rtGetInf.cpp \
    matlab_files/codegen/lib/time_anslysis/rtGetNaN.cpp \
    matlab_files/codegen/lib/time_anslysis/rt_nonfinite.cpp \
    matlab_files/codegen/lib/time_anslysis/time_anslysis.cpp \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_data.cpp \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_initialize.cpp \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_terminate.cpp \
    oscilloscope.cpp \
    oscilloscopeethenet.cpp \
    oscilloscopeplot.cpp \
    oscilloscopeserial.cpp \
    plotutils.cpp

HEADERS += \
    analysis.h \
    calibration.h \
    config.h \
    corr.h \
    device.h \
    inputdata.h \
    iputils.h \
    libtdms-gpl-0.5/include/TdmsChannel.h \
    libtdms-gpl-0.5/include/TdmsGroup.h \
    libtdms-gpl-0.5/include/TdmsLeadIn.h \
    libtdms-gpl-0.5/include/TdmsMetaData.h \
    libtdms-gpl-0.5/include/TdmsObject.h \
    libtdms-gpl-0.5/include/TdmsParser.h \
    libtdms-gpl-0.5/include/TdmsSegment.h \
    libtdms-gpl-0.5/include/endianfstream.hh \
    mainwindow.h \
    matlab_files/codegen/lib/cpsd_analysis/FFTImplementationCallback.h \
    matlab_files/codegen/lib/cpsd_analysis/bsxfun.h \
    matlab_files/codegen/lib/cpsd_analysis/coder_array.h \
    matlab_files/codegen/lib/cpsd_analysis/computeDFT.h \
    matlab_files/codegen/lib/cpsd_analysis/computepsd.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_data.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_initialize.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_rtwutil.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_terminate.h \
    matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_types.h \
    matlab_files/codegen/lib/cpsd_analysis/psdfreqvec.h \
    matlab_files/codegen/lib/cpsd_analysis/rtGetInf.h \
    matlab_files/codegen/lib/cpsd_analysis/rtGetNaN.h \
    matlab_files/codegen/lib/cpsd_analysis/rt_defines.h \
    matlab_files/codegen/lib/cpsd_analysis/rt_nonfinite.h \
    matlab_files/codegen/lib/cpsd_analysis/rtwtypes.h \
    matlab_files/codegen/lib/cpsd_analysis/welch.h \
    matlab_files/codegen/lib/onethird/FFTImplementationCallback.h \
    matlab_files/codegen/lib/onethird/coder_array.h \
    matlab_files/codegen/lib/onethird/fft.h \
    matlab_files/codegen/lib/onethird/ifft.h \
    matlab_files/codegen/lib/onethird/onethird.h \
    matlab_files/codegen/lib/onethird/onethird_data.h \
    matlab_files/codegen/lib/onethird/onethird_initialize.h \
    matlab_files/codegen/lib/onethird/onethird_terminate.h \
    matlab_files/codegen/lib/onethird/onethird_types.h \
    matlab_files/codegen/lib/onethird/rtGetInf.h \
    matlab_files/codegen/lib/onethird/rtGetNaN.h \
    matlab_files/codegen/lib/onethird/rt_nonfinite.h \
    matlab_files/codegen/lib/onethird/rtwtypes.h \
    matlab_files/codegen/lib/pingpu/FFTImplementationCallback.h \
    matlab_files/codegen/lib/pingpu/coder_array.h \
    matlab_files/codegen/lib/pingpu/pingpu.h \
    matlab_files/codegen/lib/pingpu/pingpu_data.h \
    matlab_files/codegen/lib/pingpu/pingpu_initialize.h \
    matlab_files/codegen/lib/pingpu/pingpu_terminate.h \
    matlab_files/codegen/lib/pingpu/pingpu_types.h \
    matlab_files/codegen/lib/pingpu/rtwtypes.h \
    matlab_files/codegen/lib/psd_analysis/FFTImplementationCallback.h \
    matlab_files/codegen/lib/psd_analysis/bsxfun.h \
    matlab_files/codegen/lib/psd_analysis/coder_array.h \
    matlab_files/codegen/lib/psd_analysis/computeDFT.h \
    matlab_files/codegen/lib/psd_analysis/computeperiodogram.h \
    matlab_files/codegen/lib/psd_analysis/psd_analysis.h \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_data.h \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_initialize.h \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_terminate.h \
    matlab_files/codegen/lib/psd_analysis/psd_analysis_types.h \
    matlab_files/codegen/lib/psd_analysis/rtGetInf.h \
    matlab_files/codegen/lib/psd_analysis/rtGetNaN.h \
    matlab_files/codegen/lib/psd_analysis/rt_nonfinite.h \
    matlab_files/codegen/lib/psd_analysis/rtwtypes.h \
    matlab_files/codegen/lib/time_anslysis/coder_array.h \
    matlab_files/codegen/lib/time_anslysis/combineVectorElements.h \
    matlab_files/codegen/lib/time_anslysis/mean.h \
    matlab_files/codegen/lib/time_anslysis/minOrMax.h \
    matlab_files/codegen/lib/time_anslysis/rtGetInf.h \
    matlab_files/codegen/lib/time_anslysis/rtGetNaN.h \
    matlab_files/codegen/lib/time_anslysis/rt_nonfinite.h \
    matlab_files/codegen/lib/time_anslysis/rtwtypes.h \
    matlab_files/codegen/lib/time_anslysis/time_anslysis.h \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_data.h \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_initialize.h \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_terminate.h \
    matlab_files/codegen/lib/time_anslysis/time_anslysis_types.h \
    matlab_files/codegen/lib/time_anslysis/tmwtypes.h \
    oscilloscope.h \
    oscilloscopeethenet.h \
    oscilloscopeplot.h \
    oscilloscopeserial.h \
    plotutils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


INCLUDEPATH +=$$quote(D:/Program Files/MATLAB/R2022b/extern/include)
INCLUDEPATH +=$$quote(D:/Program Files/MATLAB/R2022b/extern/include/win64)

INCLUDEPATH +=$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft)
DEPENDPATH +=$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft)

LIBS += -L$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft) -llibmx
LIBS += -L$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft) -llibmat
LIBS += -L$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft) -llibeng
LIBS += -L$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft) -lmclmcr
LIBS += -L$$quote(D:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft) -lmclmcrrt


win32: LIBS += -L$$PWD/matlab_files/codegen/lib/onethird/ -lonethird

INCLUDEPATH += $$PWD/matlab_files/codegen/lib/onethird
DEPENDPATH += $$PWD/matlab_files/codegen/lib/onethird

win32: LIBS += -L$$PWD/matlab_files/codegen/lib/daopu_analysis/ -ldaopu_analysis

INCLUDEPATH += $$PWD/matlab_files/codegen/lib/daopu_analysis
DEPENDPATH += $$PWD/matlab_files/codegen/lib/daopu_analysis

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/matlab_files/codegen/lib/daopu_analysis/daopu_analysis.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/matlab_files/codegen/lib/daopu_analysis/libdaopu_analysis.a

INCLUDEPATH += $$PWD/libtdms-gpl-0.5/include

LIBS += -LD:\Python\Python312\libs -lpython312
INCLUDEPATH += D:\Python\Python312\include
DEPENDPATH += D:\Python\Python312\libs

INCLUDEPATH +=D:\Python\Python312\Lib\site-packages\numpy\_core\include

DISTFILES += \
    add2.py
