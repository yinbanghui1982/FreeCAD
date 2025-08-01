/*
    振动噪声测试模块Python接口
*/

#include <FCConfig.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif  // HAVE_CONFIG_H

#ifdef _MSC_VER
#pragma warning(disable : 4005)
#endif

#include <QApplication>
#include <QIcon>
#include <QMainWindow>
#include <QVBoxLayout>

#if defined(Q_OS_WIN)
#include <windows.h>
#elif defined(Q_WS_X11)
#include <QX11EmbedWidget>
#endif
#include <thread>

// FreeCAD Base header
#include <App/Application.h>
#include <Base/Exception.h>
#include <Base/Factory.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/MainWindow.h>
#include <Gui/StartupProcess.h>
#include <Gui/SoFCDB.h>
#include <Gui/Quarter/Quarter.h>
#include <Gui/TextEdit.h>
#include <Gui/EditorView.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodekits/SoNodeKit.h>

#include "WidgetSoundTest.h"
#include "SoundTestView.h"

using namespace Gui;
using namespace SoundTest;

static bool _isSetupWithoutGui = false;

static PyObject* SoundTestGui_newWidgetSoundTest(PyObject* /*self*/, PyObject* args)
{
    PyObject* pyMainWindow {nullptr};
    if (!PyArg_ParseTuple(args, "|O",&pyMainWindow))
        return nullptr;

    MainWindow* mainWindow = getMainWindow();
    WidgetSoundTest* widgetSoundTest = new  WidgetSoundTest(mainWindow);
    SoundTestView* view2 = new SoundTestView(widgetSoundTest, mainWindow);
    mainWindow->addWindow(view2);
    
    Py::String out_str("sound and vibration test","utf-8");
    return Py::new_reference_to(out_str);
}

struct PyMethodDef SoundTestGui_methods[] = {    
     {"newWidgetSoundTest",
     SoundTestGui_newWidgetSoundTest,
     METH_VARARGS,
     "openWidgetSoundTest() -- return a new sound test window\n"},
    {nullptr, nullptr, 0, nullptr} /* sentinel */
};

PyMOD_INIT_FUNC(SoundTestGui)
{
    try {
        // clang-format off
        Base::Interpreter().loadModule("FreeCAD");
        App::Application::Config()["AppIcon"] = "freecad";
        App::Application::Config()["SplashScreen"] = "freecadsplash";
        App::Application::Config()["CopyrightInfo"] = "\xc2\xa9 Juergen Riegel, Werner Mayer, Yorik van Havre and others 2001-2024\n";
        App::Application::Config()["LicenseInfo"] = "FreeCAD is free and open-source software licensed under the terms of LGPL2+ license.\n";
        App::Application::Config()["CreditsInfo"] = "FreeCAD wouldn't be possible without FreeCAD community.\n";
        // clang-format on

        // it's possible that the GUI is already initialized when the Gui version of the executable
        // is started in command mode
        if (Base::Type::fromName("Gui::BaseView").isBad()) {
            Gui::Application::initApplication();
        }
        static struct PyModuleDef SoundTestGuiModuleDef = {PyModuleDef_HEAD_INIT,
                                                         "SoundTestGui",
                                                         "SoundTest GUI module\n",
                                                         -1,
                                                         SoundTestGui_methods,
                                                         nullptr,
                                                         nullptr,
                                                         nullptr,
                                                         nullptr};
        PyObject* module = PyModule_Create(&SoundTestGuiModuleDef);
        return module;
    }
    catch (const Base::Exception& e) {
        PyErr_Format(PyExc_ImportError, "%s\n", e.what());
    }
    catch (...) {
        PyErr_SetString(PyExc_ImportError, "Unknown runtime error occurred");
    }
    return nullptr;
}

