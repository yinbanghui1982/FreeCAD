
configure_file(freecad.rc.cmake ${CMAKE_CURRENT_BINARY_DIR}/freecad.rc)
configure_file(freecadCmd.rc.cmake ${CMAKE_CURRENT_BINARY_DIR}/freecadCmd.rc)
file(COPY icon.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt6 COMPONENTS Core Gui Widgets PrintSupport Charts SerialPort Network REQUIRED) 


if(BUILD_GUI)
    include_directories(
        SYSTEM
        ${Boost_INCLUDE_DIRS}
        ${COIN3D_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${QT_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
else(BUILD_GUI)
    include_directories(
        SYSTEM
        ${Boost_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${QT_INCLUDE_DIR}
        ${PYTHON_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
endif(BUILD_GUI)



SET(Gui_UIC_SRCS
    WidgetSoundTest.ui
)

######################## SoundTestGuiPy ########################
if(BUILD_GUI)

    SET(SoundTestGuiPy_SRCS 
        analysis.cpp
        calibration.cpp
        config.cpp
        corr.cpp
        device.cpp
        inputdata.cpp
        iputils.cpp
        SoundTestView.cpp
        SoundTestGuiPy.cpp        
        WidgetSoundTest.cpp         
        oscilloscope.cpp 
        oscilloscopeethenet.cpp
        oscilloscopeplot.cpp
        # oscilloscopeserial.cpp
        plotutils.cpp
        libtdms-gpl-0.5/src/TdmsChannel.cpp
        libtdms-gpl-0.5/src/TdmsGroup.cpp
        libtdms-gpl-0.5/src/TdmsLeadIn.cpp
        libtdms-gpl-0.5/src/TdmsMetaData.cpp
        libtdms-gpl-0.5/src/TdmsObject.cpp
        libtdms-gpl-0.5/src/TdmsParser.cpp
        libtdms-gpl-0.5/src/TdmsSegment.cpp        
        # matlab_files/codegen/lib/cpsd_analysis/FFTImplementationCallback.cpp
        # matlab_files/codegen/lib/cpsd_analysis/bsxfun.cpp
        # matlab_files/codegen/lib/cpsd_analysis/computeDFT.cpp
        # matlab_files/codegen/lib/cpsd_analysis/computepsd.cpp
        # matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis.cpp
        # matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_data.cpp
        # matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_initialize.cpp
        # matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_rtwutil.cpp
        # matlab_files/codegen/lib/cpsd_analysis/cpsd_analysis_terminate.cpp
        # matlab_files/codegen/lib/cpsd_analysis/psdfreqvec.cpp
        # matlab_files/codegen/lib/cpsd_analysis/rtGetInf.cpp
        # matlab_files/codegen/lib/cpsd_analysis/rtGetNaN.cpp
        # matlab_files/codegen/lib/cpsd_analysis/rt_nonfinite.cpp
        # matlab_files/codegen/lib/cpsd_analysis/welch.cpp
        # matlab_files/codegen/lib/pingpu/FFTImplementationCallback.cpp
        # matlab_files/codegen/lib/pingpu/pingpu.cpp
        # matlab_files/codegen/lib/pingpu/pingpu_data.cpp
        # matlab_files/codegen/lib/pingpu/pingpu_initialize.cpp
        # matlab_files/codegen/lib/pingpu/pingpu_terminate.cpp
        # matlab_files/codegen/lib/psd_analysis/FFTImplementationCallback.cpp
        # matlab_files/codegen/lib/psd_analysis/bsxfun.cpp
        # matlab_files/codegen/lib/psd_analysis/computeDFT.cpp
        # matlab_files/codegen/lib/psd_analysis/computeperiodogram.cpp
        # matlab_files/codegen/lib/psd_analysis/psd_analysis.cpp
        # matlab_files/codegen/lib/psd_analysis/psd_analysis_data.cpp
        # matlab_files/codegen/lib/psd_analysis/psd_analysis_initialize.cpp
        # matlab_files/codegen/lib/psd_analysis/psd_analysis_terminate.cpp
        # matlab_files/codegen/lib/psd_analysis/rtGetInf.cpp
        # matlab_files/codegen/lib/psd_analysis/rtGetNaN.cpp
        # matlab_files/codegen/lib/psd_analysis/rt_nonfinite.cpp
        # matlab_files/codegen/lib/time_anslysis/combineVectorElements.cpp
        # matlab_files/codegen/lib/time_anslysis/mean.cpp
        # matlab_files/codegen/lib/time_anslysis/minOrMax.cpp
        # matlab_files/codegen/lib/time_anslysis/rtGetInf.cpp
        # matlab_files/codegen/lib/time_anslysis/rtGetNaN.cpp
        # matlab_files/codegen/lib/time_anslysis/rt_nonfinite.cpp
        # matlab_files/codegen/lib/time_anslysis/time_anslysis.cpp
        # matlab_files/codegen/lib/time_anslysis/time_anslysis_data.cpp
        # matlab_files/codegen/lib/time_anslysis/time_anslysis_initialize.cpp
        # matlab_files/codegen/lib/time_anslysis/time_anslysis_terminate.cpp
    )

    add_library(SoundTestGuiPy SHARED ${SoundTestGuiPy_SRCS})

    # target_include_directories(SoundTestGuiPy PRIVATE
    #     "${CMAKE_CURRENT_SOURCE_DIR}"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/libtdms-gpl-0.5/include"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/matlab_files/codegen/lib/onethird"
    #     "${CMAKE_CURRENT_SOURCE_DIR}/matlab_files/codegen/lib/daopu_analysis"
        
    #     # MATLAB路径
    #     "D:/Program Files/Polyspace/R2020b/extern/include"
    #     "D:/Program Files/Polyspace/R2020b/extern/include/win64"
    #     "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft"
        
    #     # Python路径
    #     "D:/Anaconda3/envs/freecad/include"
    #     "D:/Anaconda3/envs/freecad/Lib/site-packages/numpy/_core/include"
    # )
    target_link_libraries(SoundTestGuiPy 
        FreeCADGui 
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
        Qt6::Charts
        Qt6::SerialPort
        Qt6::Network
        "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft/libmx.lib"
        "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft/libmat.lib"
        "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft/libeng.lib"
        "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft/mclmcr.lib"
        "D:/Program Files/Polyspace/R2020b/extern/lib/win64/microsoft/mclmcrrt.lib"
    )
    if (FREECAD_WARN_ERROR)
        target_compile_warn_error(SoundTestGuiPy)
    endif()

    SET_BIN_DIR(SoundTestGuiPy SoundTestGui)
    SET_PYTHON_PREFIX_SUFFIX(SoundTestGuiPy)
    if(WIN32)
        # Name clash with target "FreeCADGui"
        # Must be called "SoundTestGuiPy_d" and "SoundTestGuiPy" to work so override default
        set_target_properties(SoundTestGuiPy PROPERTIES PDB_NAME_DEBUG "SoundTestGuiPy_d")
        set_target_properties(SoundTestGuiPy PROPERTIES PDB_NAME_RELEASE "SoundTestGuiPy")
    endif(WIN32)

    if(WIN32)
        INSTALL(TARGETS SoundTestGuiPy
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    else(WIN32)
        INSTALL(TARGETS SoundTestGuiPy
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif(WIN32)
endif(BUILD_GUI)

set(CMAKE_AUTOMOC ON) 





