/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"

#ifndef _PreComp_
#include <boost/interprocess/sync/file_lock.hpp>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoError.h>
#include <QCheckBox>
#include <QCloseEvent>
#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QMessageBox>
#include <QMessageLogContext>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QScreen>
#include <QStatusBar>
#include <QStyle>
#include <QTextStream>
#include <QTimer>
#include <QWindow>
#endif

#include <QLoggingCategory>
#include <fmt/format.h>

#include <App/Document.h>
#include <App/DocumentObjectPy.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/Exception.h>
#include <Base/FileInfo.h>
#include <Base/Parameter.h>
#include <Base/Stream.h>
#include <Base/Tools.h>

#include <Base/UnitsApi.h>

#include <Language/Translator.h>
#include <Quarter/Quarter.h>

#include "Application.h"
#include "ApplicationPy.h"
#include "AxisOriginPy.h"
#include "BitmapFactory.h"
#include "Command.h"
#include "CommandActionPy.h"
#include "CommandPy.h"
#include "Control.h"
#include "PreferencePages/DlgSettingsCacheDirectory.h"
#include "DocumentPy.h"
#include "DocumentRecovery.h"
#include "EditorView.h"
#include "ExpressionBindingPy.h"
#include "FileDialog.h"
#include "GuiApplication.h"
#include "GuiInitScript.h"
#include "InputHintPy.h"
#include "LinkViewPy.h"
#include "MainWindow.h"
#include "Macro.h"
#include "PreferencePackManager.h"
#include "PythonConsolePy.h"
#include "PythonDebugger.h"
#include "MainWindowPy.h"
#include "MDIViewPy.h"
#include "Placement.h"
#include "SoFCDB.h"
#include "Selection.h"
#include "SelectionFilterPy.h"
#include "SoQtOffscreenRendererPy.h"
#include "SplitView3DInventor.h"
#include "StartupProcess.h"
#include "TaskView/TaskView.h"
#include "TaskView/TaskDialogPython.h"
#include "TransactionObject.h"
#include "TextDocumentEditorView.h"
#include "UiLoader.h"
#include "View3DPy.h"
#include "View3DViewerPy.h"
#include "View3DInventor.h"
#include "ViewProviderAnnotation.h"
#include "ViewProviderDocumentObject.h"
#include "ViewProviderDocumentObjectGroup.h"
#include "ViewProviderDragger.h"
#include "ViewProviderExtension.h"
#include "ViewProviderExtern.h"
#include "ViewProviderFeature.h"
#include "ViewProviderGeoFeatureGroup.h"
#include "ViewProviderGeometryObject.h"
#include "ViewProviderGeometryObjectPy.h"
#include "ViewProviderGroupExtension.h"
#include "ViewProviderSuppressibleExtension.h"
#include "ViewProviderImagePlane.h"
#include "ViewProviderInventorObject.h"
#include "ViewProviderLine.h"
#include "ViewProviderLink.h"
#include "ViewProviderLinkPy.h"
#include "ViewProviderMaterialObject.h"
#include "ViewProviderCoordinateSystem.h"
#include "ViewProviderDatum.h"
#include "ViewProviderOriginGroup.h"
#include "ViewProviderPlacement.h"
#include "ViewProviderPlane.h"
#include "ViewProviderPoint.h"
#include "ViewProviderPart.h"
#include "ViewProviderFeaturePython.h"
#include "ViewProviderTextDocument.h"
#include "ViewProviderTextureExtension.h"
#include "ViewProviderVRMLObject.h"
#include "ViewProviderVarSet.h"
#include "WaitCursor.h"
#include "Workbench.h"
#include "WorkbenchManager.h"
#include "WorkbenchManipulator.h"
#include "WidgetFactory.h"
#include "3Dconnexion/navlib/NavlibInterface.h"
#include "Inventor/SoFCPlacementIndicatorKit.h"
#include "QtWidgets.h"

#include <OverlayManager.h>
#include <Base/ServiceProvider.h>

#ifdef BUILD_TRACY_FRAME_PROFILER
#include <tracy/Tracy.hpp>
#endif

using namespace Gui;
using namespace Gui::DockWnd;
using namespace std;
namespace sp = std::placeholders;


Application* Application::Instance = nullptr;

namespace Gui
{

class ViewProviderMap
{
    std::unordered_map<const App::DocumentObject*, ViewProvider*> map;

public:
    void newObject(const ViewProvider& vp)
    {
        auto vpd =
            freecad_cast<ViewProviderDocumentObject*>(const_cast<ViewProvider*>(&vp));
        if (vpd && vpd->getObject()) {
            map[vpd->getObject()] = vpd;
        }
    }
    void deleteObject(const ViewProvider& vp)
    {
        auto vpd =
            freecad_cast<ViewProviderDocumentObject*>(const_cast<ViewProvider*>(&vp));
        if (vpd && vpd->getObject()) {
            map.erase(vpd->getObject());
        }
    }
    void deleteDocument(const App::Document& doc)
    {
        for (auto obj : doc.getObjects()) {
            map.erase(obj);
        }
    }
    Gui::ViewProvider* getViewProvider(const App::DocumentObject* obj) const
    {
        auto it = map.find(obj);
        if (it == map.end()) {
            return nullptr;
        }
        return it->second;
    }
};

// Pimpl class
struct ApplicationP
{
    explicit ApplicationP(bool GUIenabled)
    {
        // create the macro manager
        if (GUIenabled) {
            macroMngr = new MacroManager();
        }
        else {
            macroMngr = nullptr;
        }

        // Create the Theme Manager
        prefPackManager = new PreferencePackManager();
        // Create the Style Parameter Manager
        styleParameterManager = new StyleParameters::ParameterManager();
    }

    ~ApplicationP()
    {
        delete macroMngr;
        delete prefPackManager;
    }

    /// list of all handled documents
    std::map<const App::Document*, Gui::Document*> documents;
    /// Active document
    Gui::Document* activeDocument {nullptr};
    Gui::Document* editDocument {nullptr};

    MacroManager* macroMngr;
    PreferencePackManager* prefPackManager;
    StyleParameters::ParameterManager* styleParameterManager;

    /// List of all registered views
    std::list<Gui::BaseView*> passive;
    bool isClosing {false};
    bool startingUp {true};
    /// Handles all commands
    CommandManager commandManager;
    ViewProviderMap viewproviderMap;
    std::bitset<32> StatusBits;
};

static PyObject* FreeCADGui_subgraphFromObject(PyObject* /*self*/, PyObject* args)
{
    PyObject* o;
    if (!PyArg_ParseTuple(args, "O!", &(App::DocumentObjectPy::Type), &o)) {
        return nullptr;
    }
    App::DocumentObject* obj = static_cast<App::DocumentObjectPy*>(o)->getDocumentObjectPtr();
    std::string vp = obj->getViewProviderName();
    SoNode* node = nullptr;
    try {
        auto base =
            static_cast<Base::BaseClass*>(Base::Type::createInstanceByName(vp.c_str(), true));
        if (base && base->isDerivedFrom<Gui::ViewProviderDocumentObject>()) {
            std::unique_ptr<Gui::ViewProviderDocumentObject> vp(
                static_cast<Gui::ViewProviderDocumentObject*>(base));
            std::map<std::string, App::Property*> Map;
            obj->getPropertyMap(Map);
            vp->attach(obj);

            // this is needed to initialize Python-based view providers
            App::Property* pyproxy = vp->getPropertyByName("Proxy");
            if (pyproxy && pyproxy->is<App::PropertyPythonObject>()) {
                static_cast<App::PropertyPythonObject*>(pyproxy)->setValue(Py::Long(1));
            }

            for (const auto& it : Map) {
                vp->updateData(it.second);
            }

            std::vector<std::string> modes = vp->getDisplayModes();
            if (!modes.empty()) {
                vp->setDisplayMode(modes.front().c_str());
            }
            node = vp->getRoot()->copy();
            node->ref();
            std::string prefix = "So";
            std::string type = node->getTypeId().getName().getString();
            // doesn't start with the prefix 'So'
            if (type.rfind("So", 0) != 0) {
                type = prefix + type;
            }
            else if (type == "SoFCSelectionRoot") {
                type = "SoSeparator";
            }

            type += " *";
            PyObject* proxy = nullptr;
            proxy = Base::Interpreter().createSWIGPointerObj("pivy.coin",
                                                             type.c_str(),
                                                             static_cast<void*>(node),
                                                             1);
            return Py::new_reference_to(Py::Object(proxy, true));
        }
    }
    catch (const Base::Exception& e) {
        if (node) {
            node->unref();
        }
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* FreeCADGui_exportSubgraph(PyObject* /*self*/, PyObject* args)
{
    const char* format = "VRML";
    PyObject* proxy;
    PyObject* output;
    if (!PyArg_ParseTuple(args, "OO|s", &proxy, &output, &format)) {
        return nullptr;
    }

    void* ptr = nullptr;
    try {
        Base::Interpreter().convertSWIGPointerObj("pivy.coin", "SoNode *", proxy, &ptr, 0);
        auto node = static_cast<SoNode*>(ptr);
        if (node) {
            std::string formatStr(format);
            std::string buffer;

            if (formatStr == "VRML") {
                SoFCDB::writeToVRML(node, buffer);
            }
            else if (formatStr == "IV") {
                buffer = SoFCDB::writeNodesToString(node);
            }
            else {
                throw Base::ValueError("Unsupported format");
            }

            Base::PyStreambuf buf(output);
            std::ostream str(nullptr);
            str.rdbuf(&buf);
            str << buffer;
        }

        Py_INCREF(Py_None);
        return Py_None;
    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return nullptr;
    }
}

static PyObject* FreeCADGui_getSoDBVersion(PyObject* /*self*/, PyObject* args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return nullptr;
    }
    return PyUnicode_FromString(SoDB::getVersion());
}

struct PyMethodDef FreeCADGui_methods[] = {
    {"subgraphFromObject",
     FreeCADGui_subgraphFromObject,
     METH_VARARGS,
     "subgraphFromObject(object) -> Node\n\n"
     "Return the Inventor subgraph to an object"},
    {"exportSubgraph",
     FreeCADGui_exportSubgraph,
     METH_VARARGS,
     "exportSubgraph(Node, File or Buffer, [Format='VRML']) -> None\n\n"
     "Exports the sub-graph in the requested format"
     "The format string can be VRML or IV"},
    {"getSoDBVersion",
     FreeCADGui_getSoDBVersion,
     METH_VARARGS,
     "getSoDBVersion() -> String\n\n"
     "Return a text string containing the name\n"
     "of the Coin library and version information"},
    {nullptr, nullptr, 0, nullptr} /* sentinel */
};

}  // namespace Gui

void Application::initStyleParameterManager()
{
    Base::registerServiceImplementation<StyleParameters::ParameterSource>(
        new StyleParameters::BuiltInParameterSource({.name = QT_TR_NOOP("Built-in Parameters")}));

    Base::registerServiceImplementation<StyleParameters::ParameterSource>(
        new StyleParameters::UserParameterSource(
            App::GetApplication().GetParameterGroupByPath(
                "User parameter:BaseApp/Preferences/Themes/Tokens"),
            {.name = QT_TR_NOOP("Theme Parameters"),
             .options = StyleParameters::ParameterSourceOption::UserEditable}));

    Base::registerServiceImplementation<StyleParameters::ParameterSource>(
        new StyleParameters::UserParameterSource(
            App::GetApplication().GetParameterGroupByPath(
                "User parameter:BaseApp/Preferences/Themes/UserTokens"),
            {.name = QT_TR_NOOP("User Parameters"),
             .options = StyleParameters::ParameterSource::UserEditable}));

    for (auto* source : Base::provideServiceImplementations<StyleParameters::ParameterSource>()) {
        d->styleParameterManager->addSource(source);
    }

    Base::registerServiceImplementation(d->styleParameterManager);
}
// clang-format off
Application::Application(bool GUIenabled)
{
    // App::GetApplication().Attach(this);
    if (GUIenabled) {
        // NOLINTBEGIN
        App::GetApplication().signalNewDocument.connect(
            std::bind(&Gui::Application::slotNewDocument, this, sp::_1, sp::_2));
        App::GetApplication().signalDeleteDocument.connect(
            std::bind(&Gui::Application::slotDeleteDocument, this, sp::_1));
        App::GetApplication().signalRenameDocument.connect(
            std::bind(&Gui::Application::slotRenameDocument, this, sp::_1));
        App::GetApplication().signalActiveDocument.connect(
            std::bind(&Gui::Application::slotActiveDocument, this, sp::_1));
        App::GetApplication().signalRelabelDocument.connect(
            std::bind(&Gui::Application::slotRelabelDocument, this, sp::_1));
        App::GetApplication().signalShowHidden.connect(
            std::bind(&Gui::Application::slotShowHidden, this, sp::_1));
        // NOLINTEND
        // install the last active language
        ParameterGrp::handle hPGrp = App::GetApplication().GetUserParameter().GetGroup("BaseApp");
        hPGrp = hPGrp->GetGroup("Preferences")->GetGroup("General");
        QString lang = QLocale::languageToString(QLocale().language());
        Translator::instance()->activateLanguage(
            hPGrp->GetASCII("Language", (const char*)lang.toLatin1()).c_str());
        GetWidgetFactorySupplier();

        // Coin3d disabled VBO support for all Intel drivers but in the meantime they have improved
        // so we can try to override the workaround by setting COIN_VBO
        ParameterGrp::handle hViewGrp = App::GetApplication().GetParameterGroupByPath(
            "User parameter:BaseApp/Preferences/View");
        if (hViewGrp->GetBool("UseVBO", false)) {
            (void)coin_setenv("COIN_VBO", "0", true);
        }

        // Check for the symbols for group separator and decimal point. They must be different
        // otherwise Qt doesn't work properly.
#if defined(Q_OS_WIN32)
        if (QLocale().groupSeparator() == QLocale().decimalPoint()) {
            QMessageBox::critical(
                0,
                QLatin1String("Invalid system settings"),
                QLatin1String(
                    "Your system uses the same symbol for decimal point and group separator.\n\n"
                    "This causes serious problems and makes the application fail to work "
                    "properly.\n"
                    "Go to the system configuration panel of the OS and fix this issue, please."));
            throw Base::RuntimeError("Invalid system settings");
        }
#endif

        // setting up Python binding
        Base::PyGILStateLocker lock;

        PyDoc_STRVAR(
            FreeCADGui_doc,
            "The functions in the FreeCADGui module allow working with GUI documents,\n"
            "view providers, views, workbenches and much more.\n\n"
            "The FreeCADGui instance provides a list of references of GUI documents which\n"
            "can be addressed by a string. These documents contain the view providers for\n"
            "objects in the associated App document. An App and GUI document can be\n"
            "accessed with the same name.\n\n"
            "The FreeCADGui module also provides a set of functions to work with so called\n"
            "workbenches.");

        // if this returns a valid pointer then the 'FreeCADGui' Python module was loaded,
        // otherwise the executable was launched
        PyObject* modules = PyImport_GetModuleDict();
        PyObject* module = PyDict_GetItemString(modules, "FreeCADGui");
        if (!module) {
            static struct PyModuleDef FreeCADGuiModuleDef = {PyModuleDef_HEAD_INIT,
                                                             "FreeCADGui",
                                                             FreeCADGui_doc,
                                                             -1,
                                                             ApplicationPy::Methods,
                                                             nullptr,
                                                             nullptr,
                                                             nullptr,
                                                             nullptr};
            module = PyModule_Create(&FreeCADGuiModuleDef);

            PyDict_SetItemString(modules, "FreeCADGui", module);
        }
        else {
            // extend the method list
            PyModule_AddFunctions(module, ApplicationPy::Methods);
        }
        Py::Module(module).setAttr(std::string("ActiveDocument"), Py::None());
        Py::Module(module).setAttr(std::string("HasQtBug_129596"),
#ifdef HAS_QTBUG_129596
            Py::True()
#else
            Py::False()
#endif
        );

        UiLoaderPy::init_type();
        Base::Interpreter().addType(UiLoaderPy::type_object(), module, "UiLoader");
        PyResource::init_type();

        Gui::Dialog::TaskPlacementPy::init_type();
        Base::Interpreter().addType(Gui::Dialog::TaskPlacementPy::type_object(),
            module, "TaskPlacement");

        // PySide additions
        PyModule_AddObject(module, "PySideUic", Base::Interpreter().addModule(new PySideUicModule));

        ExpressionBindingPy::init_type();
        Base::Interpreter().addType(ExpressionBindingPy::type_object(),
                                    module,
                                    "ExpressionBinding");

        // insert Selection module
        static struct PyModuleDef SelectionModuleDef = {PyModuleDef_HEAD_INIT,
                                                        "Selection",
                                                        "Selection module",
                                                        -1,
                                                        SelectionSingleton::Methods,
                                                        nullptr,
                                                        nullptr,
                                                        nullptr,
                                                        nullptr};
        PyObject* pSelectionModule = PyModule_Create(&SelectionModuleDef);
        Py_INCREF(pSelectionModule);
        PyModule_AddObject(module, "Selection", pSelectionModule);

        SelectionFilterPy::init_type();
        Base::Interpreter().addType(SelectionFilterPy::type_object(), pSelectionModule, "Filter");

        Gui::TaskView::ControlPy::init_type();
        Py::Module(module).setAttr(std::string("Control"),
                                   Py::Object(Gui::TaskView::ControlPy::getInstance(), true));
        Gui::TaskView::TaskDialogPy::init_type();

        registerUserInputEnumInPython(module);
        Base::PyRegisterEnum<SoFCPlacementIndicatorKit::Part>(module, "PlacementIndicatorParts", {
            {"Axes", SoFCPlacementIndicatorKit::Axes},
            {"ArrowHeads", SoFCPlacementIndicatorKit::ArrowHeads},
            {"Labels", SoFCPlacementIndicatorKit::Labels},
            {"PlaneIndicator", SoFCPlacementIndicatorKit::PlaneIndicator},
            {"OriginIndicator", SoFCPlacementIndicatorKit::OriginIndicator},

            // common configurations
            {"AllParts", SoFCPlacementIndicatorKit::AllParts},
            {"AxisCross", SoFCPlacementIndicatorKit::AxisCross},
        });

        Base::PyRegisterEnum<Gui::BitmapFactoryInst::Position>(module, "IconPosition", {
            {"TopLeft",     Gui::BitmapFactoryInst::TopLeft},
            {"TopRight",    Gui::BitmapFactoryInst::TopRight},
            {"BottomLeft",  Gui::BitmapFactoryInst::BottomLeft},
            {"BottomRight", Gui::BitmapFactoryInst::BottomRight}
        });

        CommandActionPy::init_type();
        Base::Interpreter().addType(CommandActionPy::type_object(), module, "CommandAction");

        Base::Interpreter().addType(&LinkViewPy::Type, module, "LinkView");
        Base::Interpreter().addType(&AxisOriginPy::Type, module, "AxisOrigin");
        Base::Interpreter().addType(&CommandPy::Type, module, "Command");
        Base::Interpreter().addType(&DocumentPy::Type, module, "Document");
        Base::Interpreter().addType(&ViewProviderPy::Type, module, "ViewProvider");
        Base::Interpreter().addType(&ViewProviderDocumentObjectPy::Type,
                                    module,
                                    "ViewProviderDocumentObject");
        Base::Interpreter().addType(&ViewProviderGeometryObjectPy::Type,
                                    module,
                                    "ViewProviderGeometryObject");
        Base::Interpreter().addType(&ViewProviderLinkPy::Type, module, "ViewProviderLink");
    }

    Base::PyGILStateLocker lock;
    PyObject* module = PyImport_AddModule("FreeCADGui");
    PyMethodDef* meth = FreeCADGui_methods;
    PyObject* dict = PyModule_GetDict(module);
    for (; meth->ml_name != nullptr; meth++) {
        PyObject* descr;
        descr = PyCFunction_NewEx(meth, nullptr, nullptr);
        if (!descr) {
            break;
        }
        if (PyDict_SetItemString(dict, meth->ml_name, descr) != 0) {
            break;
        }
        Py_DECREF(descr);
    }

    SoQtOffscreenRendererPy::init_type();
    Base::Interpreter().addType(SoQtOffscreenRendererPy::type_object(),
                                module,
                                "SoQtOffscreenRenderer");

    App::Application::Config()["COIN_VERSION"] = COIN_VERSION;

    // clang-format off
    // Python console binding
    PythonDebugModule           ::init_module();
    PythonStdout                ::init_type();
    PythonStderr                ::init_type();
    OutputStdout                ::init_type();
    OutputStderr                ::init_type();
    PythonStdin                 ::init_type();
    MainWindowPy                ::init_type();
    MDIViewPy                   ::init_type();
    View3DInventorPy            ::init_type();
    View3DInventorViewerPy      ::init_type();
    AbstractSplitViewPy         ::init_type();
    // clang-format on

    d = new ApplicationP(GUIenabled);

    initStyleParameterManager();

    // global access
    Instance = this;

    // instantiate the workbench dictionary
    _pcWorkbenchDictionary = PyDict_New();

#ifdef USE_3DCONNEXION_NAVLIB
    ParameterGrp::handle hViewGrp = App::GetApplication().GetParameterGroupByPath(
        "User parameter:BaseApp/Preferences/View");
    if (!hViewGrp->GetBool("LegacySpaceMouseDevices", false)) {
        // Instantiate the 3Dconnexion controller
        pNavlibInterface = new NavlibInterface();
    }
    else {
        pNavlibInterface = nullptr;
    }
#endif

    if (GUIenabled) {
        createStandardOperations();
        MacroCommand::load();
    }
}
// clang-format on

Application::~Application()
{
    Base::Console().log("Destruct Gui::Application\n");
#ifdef USE_3DCONNEXION_NAVLIB
    delete pNavlibInterface;
#endif
    WorkbenchManager::destruct();
    WorkbenchManipulator::removeAll();
    SelectionSingleton::destruct();
    Translator::destruct();
    WidgetFactorySupplier::destruct();
    BitmapFactoryInst::destruct();

    Base::PyGILStateLocker lock;
    Py_DECREF(_pcWorkbenchDictionary);

    // save macros
    try {
        MacroCommand::save();
    }
    catch (const Base::Exception& e) {
        std::cerr << "Saving macros failed: " << e.what() << std::endl;
    }

    delete d;
    Instance = nullptr;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// creating std commands
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void Application::open(const char* FileName, const char* Module)
{
    WaitCursor wc;
    wc.setIgnoreEvents(WaitCursor::NoEvents);
    Base::FileInfo File(FileName);
    string te = File.extension();
    string unicodepath = Base::Tools::escapedUnicodeFromUtf8(File.filePath().c_str());
    unicodepath = Base::Tools::escapeEncodeFilename(unicodepath);

    // if the active document is empty and not modified, close it
    // in case of an automatically created empty document at startup
    App::Document* act = App::GetApplication().getActiveDocument();
    Gui::Document* gui = this->getDocument(act);
    if (act && act->countObjects() == 0 && gui && !gui->isModified() && act->isAutoCreated()) {
        Command::doCommand(Command::App, "App.closeDocument('%s')", act->getName());
        qApp->processEvents();  // an update is needed otherwise the new view isn't shown
    }

    if (Module) {
        try {
            if (File.hasExtension("FCStd")) {
                bool handled = false;
                std::string filepath = File.filePath();
                for (auto& v : d->documents) {
                    auto doc = v.second->getDocument();
                    std::string fi = Base::FileInfo(doc->FileName.getValue()).filePath();
                    if (filepath == fi) {
                        handled = true;
                        Command::doCommand(Command::App, "FreeCADGui.reload('%s')", doc->getName());
                        break;
                    }
                }

                if (!handled) {
                    Command::doCommand(Command::App,
                                       "FreeCAD.openDocument('%s')",
                                       unicodepath.c_str());
                    Gui::Application::checkForRecomputes();
                }
            }
            else {
                std::string code = fmt::format("from freecad import module_io\n"
                                               "module_io.OpenInsertObject(\"{}\", \"{}\", \"{}\")\n",
                                               Module, unicodepath, "open");
                Gui::Command::runCommand(Gui::Command::App, code.c_str());

                // ViewFit
                if (sendHasMsgToActiveView("ViewFit")) {
                    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath(
                        "User parameter:BaseApp/Preferences/View");
                    if (hGrp->GetBool("AutoFitToView", true)) {
                        Command::doCommand(Command::Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
                    }
                }
            }

            // the original file name is required
            QString filename = QString::fromUtf8(File.filePath().c_str());
            getMainWindow()->appendRecentFile(filename);
            FileDialog::setWorkingDirectory(filename);
        }
        catch (const Base::PyException& e) {
            // Usually thrown if the file is invalid somehow
            e.reportException();
        }
    }
    else {
        wc.restoreCursor();
        QMessageBox::warning(
            getMainWindow(),
            QObject::tr("Unknown filetype"),
            QObject::tr("Cannot open unknown filetype: %1").arg(QLatin1String(te.c_str())));
        wc.setWaitCursor();
        return;
    }
}

void Application::importFrom(const char* FileName, const char* DocName, const char* Module)
{
    WaitCursor wc;
    wc.setIgnoreEvents(WaitCursor::NoEvents);
    Base::FileInfo File(FileName);
    std::string te = File.extension();
    string unicodepath = File.filePath().c_str();
    unicodepath = Base::Tools::escapeEncodeFilename(unicodepath);

    if (Module) {
        try {
            // issue module loading
            Command::doCommand(Command::App, "import %s", Module);

            // load the file with the module
            if (File.hasExtension("FCStd")) {
                Command::doCommand(Command::App, "%s.open(u\"%s\")", Module, unicodepath.c_str());
                setStatus(UserInitiatedOpenDocument, false);
                App::Document* doc = App::GetApplication().getActiveDocument();
                checkPartialRestore(doc);
                checkRestoreError(doc);
                checkForRecomputes();
                if (activeDocument()) {
                    activeDocument()->setModified(false);
                }
            }
            else {
                // Open transaction when importing a file
                Gui::Document* doc = DocName ? getDocument(DocName) : activeDocument();
                bool pendingCommand = false;
                if (doc) {
                    pendingCommand = doc->hasPendingCommand();
                    if (!pendingCommand) {
                        doc->openCommand(QT_TRANSLATE_NOOP("Command", "Import"));
                    }
                }

                std::string code = fmt::format("from freecad import module_io\n"
                                               "module_io.OpenInsertObject(\"{}\", \"{}\", \"{}\", \"{}\")\n",
                                               Module, unicodepath, "insert", DocName);
                Gui::Command::runCommand(Gui::Command::App, code.c_str());

                // Commit the transaction
                if (doc && !pendingCommand) {
                    doc->commitCommand();
                }

                // It's possible that before importing a file the document with the
                // given name doesn't exist or there is no active document.
                // The import function then may create a new document.
                if (!doc) {
                    doc = activeDocument();
                }

                if (doc) {
                    doc->setModified(true);

                    ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath(
                        "User parameter:BaseApp/Preferences/View");
                    if (hGrp->GetBool("AutoFitToView", true)) {
                        MDIView* view = doc->getActiveView();
                        if (view) {
                            const char* ret = nullptr;
                            if (view->onMsg("ViewFit", &ret)) {
                                updateActions(true);
                            }
                        }
                    }
                }
            }

            // the original file name is required
            QString filename = QString::fromUtf8(File.filePath().c_str());
            auto parameterGroup = App::GetApplication().GetParameterGroupByPath(
                "User parameter:BaseApp/Preferences/General");
            bool addToRecent = parameterGroup->GetBool("RecentIncludesImported", true);
            parameterGroup->SetBool("RecentIncludesImported",
                                    addToRecent);  // Make sure it gets added to the parameter list
            if (addToRecent) {
                getMainWindow()->appendRecentFile(filename);
            }
            FileDialog::setWorkingDirectory(filename);
        }
        catch (const Base::PyException& e) {
            // Usually thrown if the file is invalid somehow
            e.reportException();
        }
    }
    else {
        wc.restoreCursor();
        QMessageBox::warning(
            getMainWindow(),
            QObject::tr("Unknown filetype"),
            QObject::tr("Cannot open unknown filetype: %1").arg(QLatin1String(te.c_str())));
        wc.setWaitCursor();
    }
}

void Application::exportTo(const char* FileName, const char* DocName, const char* Module)
{
    WaitCursor wc;
    wc.setIgnoreEvents(WaitCursor::NoEvents);
    Base::FileInfo File(FileName);
    std::string te = File.extension();
    string unicodepath = Base::Tools::escapedUnicodeFromUtf8(File.filePath().c_str());
    unicodepath = Base::Tools::escapeEncodeFilename(unicodepath);

    if (Module) {
        try {
            std::vector<App::DocumentObject*> sel =
                Gui::Selection().getObjectsOfType(App::DocumentObject::getClassTypeId(), DocName);
            if (sel.empty()) {
                App::Document* doc = App::GetApplication().getDocument(DocName);
                sel = doc->getObjectsOfType(App::DocumentObject::getClassTypeId());
            }

            std::stringstream str;
            std::set<App::DocumentObject*> unique_objs;
            str << "__objs__ = []\n";
            for (auto it : sel) {
                if (unique_objs.insert(it).second) {
                    str << "__objs__.append(FreeCAD.getDocument(\"" << DocName << "\").getObject(\""
                        << it->getNameInDocument() << "\"))\n";
                }
            }

            // check for additional export options
            str << "import " << Module << '\n';
            str << "if hasattr(" << Module << ", \"exportOptions\"):\n"
                << "    options = " << Module << ".exportOptions(u\"" << unicodepath << "\")\n"
                << "    " << Module << ".export(__objs__, u\"" << unicodepath << "\", options)\n"
                << "else:\n"
                << "    " << Module << ".export(__objs__, u\"" << unicodepath << "\")\n";

            std::string code = str.str();
            // the original file name is required
            Gui::Command::runCommand(Gui::Command::App, code.c_str());

            auto parameterGroup = App::GetApplication().GetParameterGroupByPath(
                "User parameter:BaseApp/Preferences/General");
            bool addToRecent = parameterGroup->GetBool("RecentIncludesExported", false);
            parameterGroup->SetBool("RecentIncludesExported",
                                    addToRecent);  // Make sure it gets added to the parameter list
            if (addToRecent) {
                // search for a module that is able to open the exported file because otherwise
                // it doesn't need to be added to the recent files list (#0002047)
                std::map<std::string, std::string> importMap =
                    App::GetApplication().getImportFilters(te.c_str());
                if (!importMap.empty()) {
                    getMainWindow()->appendRecentFile(QString::fromUtf8(File.filePath().c_str()));
                }
            }
            // allow exporters to pass _objs__ to submodules before deleting it
            Gui::Command::runCommand(Gui::Command::App, "del __objs__");
        }
        catch (const Base::PyException& e) {
            // Usually thrown if the file is invalid somehow
            e.reportException();
            wc.restoreCursor();
            QMessageBox::critical(getMainWindow(),
                                  QObject::tr("Export failed"),
                                  QString::fromUtf8(e.what()));
            wc.setWaitCursor();
        }
    }
    else {
        wc.restoreCursor();
        QMessageBox::warning(
            getMainWindow(),
            QObject::tr("Unknown filetype"),
            QObject::tr("Cannot save to unknown filetype: %1").arg(QLatin1String(te.c_str())));
        wc.setWaitCursor();
    }
}

void Application::createStandardOperations()
{
    // register the application Standard commands from CommandStd.cpp
    Gui::CreateStdCommands();
    Gui::CreateDocCommands();
    Gui::CreateFeatCommands();
    Gui::CreateMacroCommands();
    Gui::CreateViewStdCommands();
    Gui::CreateWindowStdCommands();
    Gui::CreateStructureCommands();
    Gui::CreateTestCommands();
    Gui::CreateLinkCommands();
}

void Application::slotNewDocument(const App::Document& Doc, bool isMainDoc)
{
#ifdef FC_DEBUG
    assert(d->documents.find(&Doc) == d->documents.end());
#endif
    auto pDoc = new Gui::Document(const_cast<App::Document*>(&Doc), this);
    d->documents[&Doc] = pDoc;

    // NOLINTBEGIN
    //  connect the signals to the application for the new document
    pDoc->signalNewObject.connect(std::bind(&Gui::Application::slotNewObject, this, sp::_1));
    pDoc->signalDeletedObject.connect(
        std::bind(&Gui::Application::slotDeletedObject, this, sp::_1));
    pDoc->signalChangedObject.connect(
        std::bind(&Gui::Application::slotChangedObject, this, sp::_1, sp::_2));
    pDoc->signalRelabelObject.connect(
        std::bind(&Gui::Application::slotRelabelObject, this, sp::_1));
    pDoc->signalActivatedObject.connect(
        std::bind(&Gui::Application::slotActivatedObject, this, sp::_1));
    pDoc->signalInEdit.connect(std::bind(&Gui::Application::slotInEdit, this, sp::_1));
    pDoc->signalResetEdit.connect(std::bind(&Gui::Application::slotResetEdit, this, sp::_1));
    // NOLINTEND

    signalNewDocument(*pDoc, isMainDoc);
    if (isMainDoc) {
        pDoc->createView(View3DInventor::getClassTypeId());
    }
}

void Application::slotDeleteDocument(const App::Document& Doc)
{
    std::map<const App::Document*, Gui::Document*>::iterator doc = d->documents.find(&Doc);
    if (doc == d->documents.end()) {
        Base::Console().log("GUI document '%s' already deleted\n", Doc.getName());
        return;
    }

    // Inside beforeDelete() a view provider may finish editing mode
    // and therefore can alter the selection.
    doc->second->beforeDelete();

    // We must clear the selection here to notify all observers.
    // And because of possible cross document link, better clear all selection
    // to be safe
    Gui::Selection().clearCompleteSelection();
    doc->second->signalDeleteDocument(*doc->second);
    signalDeleteDocument(*doc->second);

    // If the active document gets destructed we must set it to 0. If there are further existing
    // documents then the view that becomes active sets the active document again. So, we needn't
    // worry about this.
    if (d->activeDocument == doc->second) {
        setActiveDocument(nullptr);
    }

    d->viewproviderMap.deleteDocument(Doc);

    // For exception-safety use a smart pointer
    unique_ptr<Document> delDoc(doc->second);
    d->documents.erase(doc);
}

void Application::slotRelabelDocument(const App::Document& Doc)
{
    std::map<const App::Document*, Gui::Document*>::iterator doc = d->documents.find(&Doc);
#ifdef FC_DEBUG
    assert(doc != d->documents.end());
#endif

    signalRelabelDocument(*doc->second);
    doc->second->onRelabel();
}

void Application::slotRenameDocument(const App::Document& Doc)
{
    std::map<const App::Document*, Gui::Document*>::iterator doc = d->documents.find(&Doc);
#ifdef FC_DEBUG
    assert(doc != d->documents.end());
#endif

    signalRenameDocument(*doc->second);
}

void Application::slotShowHidden(const App::Document& Doc)
{
    std::map<const App::Document*, Gui::Document*>::iterator doc = d->documents.find(&Doc);
#ifdef FC_DEBUG
    assert(doc != d->documents.end());
#endif

    signalShowHidden(*doc->second);
}

void Application::checkForRecomputes() {
    std::vector<App::Document *> docs;
    for (auto doc: App::GetApplication().getDocuments()) {
        if (doc->testStatus(App::Document::RecomputeOnRestore)) {
            docs.push_back(doc);
            doc->setStatus(App::Document::RecomputeOnRestore, false);
        }
    }
    // Certain tests want to use very old .FCStd files.  We should not prompt during those tests, so this
    // allows them to 'FreeCAD.ConfigSet("SuppressRecomputeRequiredDialog", "True")`
    const std::map<std::string, std::string>& Map = App::Application::Config();
    auto value = Map.find("SuppressRecomputeRequiredDialog");
    bool skip = value != Map.end() && ! value->second.empty();   // Any non empty string is true.
    if (docs.empty() || skip )
        return;
    WaitCursor wc;
    wc.restoreCursor();
    auto res = QMessageBox::warning(getMainWindow(), QObject::tr("Recomputation required"),
                                    QObject::tr("Some document(s) require recomputation for migration purposes. "
                                                "It is highly recommended to perform a recomputation before "
                                                "any modification to avoid compatibility problems.\n\n"
                                                "Do you want to recompute now?"),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (res != QMessageBox::Yes)
        return;
    bool hasError = false;
    for (auto doc: App::Document::getDependentDocuments(docs, true)) {
        try {
            doc->recompute({}, false, &hasError);
        } catch (Base::Exception &e) {
            e.reportException();
            hasError = true;
        }
    }
    if (hasError)
        QMessageBox::critical(getMainWindow(), QObject::tr("Recompute error"),
                              QObject::tr("Failed to recompute some document(s).\n"
                                          "Please check report view for more details."));
}

void Application::checkPartialRestore(App::Document* doc)
{
    if (doc && doc->testStatus(App::Document::PartialRestore)) {
        QMessageBox::critical(
            getMainWindow(),
            QObject::tr("Error"),
            QObject::tr("There were errors while loading the file. Some data might have been "
                        "modified or not recovered at all. Look in the report view for more "
                        "specific information about the objects involved."));
    }
}

void Application::checkRestoreError(App::Document* doc)
{
    if (doc && doc->testStatus(App::Document::RestoreError)) {
        QMessageBox::critical(
            getMainWindow(),
            QObject::tr("Error"),
            QObject::tr("There were serious errors while loading the file. Some data might have "
                        "been modified or not recovered at all. Saving the project will most "
                        "likely result in loss of data."));
    }
}

void Application::slotActiveDocument(const App::Document& Doc)
{
    std::map<const App::Document*, Gui::Document*>::iterator doc = d->documents.find(&Doc);
    // this can happen when closing a document with two views opened
    if (doc != d->documents.end()) {
        // this can happen when calling App.setActiveDocument directly from Python
        // because no MDI view will be activated
        if (d->activeDocument != doc->second) {
            d->activeDocument = doc->second;
            if (d->activeDocument) {
                Base::PyGILStateLocker lock;
                Py::Object active(d->activeDocument->getPyObject(), true);
                Py::Module("FreeCADGui").setAttr(std::string("ActiveDocument"), active);

                auto view = getMainWindow()->activeWindow();
                if (!view || view->getAppDocument() != &Doc) {
                    Gui::MDIView* view = d->activeDocument->getActiveView();
                    getMainWindow()->setActiveWindow(view);
                }
            }
            else {
                Base::PyGILStateLocker lock;
                Py::Module("FreeCADGui").setAttr(std::string("ActiveDocument"), Py::None());
            }
        }

        // Update the application to show the unit change
        ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath(
            "User parameter:BaseApp/Preferences/Units");
        if (!hGrp->GetBool("IgnoreProjectSchema")) {
            int userSchema = Doc.UnitSystem.getValue();
            Base::UnitsApi::setSchema(userSchema);
            getMainWindow()->setUserSchema(userSchema);
            Application::Instance->onUpdate();
        }
        else {  // set up Unit system default
            Base::UnitsApi::setSchema(hGrp->GetInt("UserSchema", 0));
            Base::UnitsApi::setDecimals(hGrp->GetInt("Decimals", Base::UnitsApi::getDecimals()));
        }
        signalActiveDocument(*doc->second);
        updateActions();
    }
}

void Application::slotNewObject(const ViewProvider& vp)
{
    d->viewproviderMap.newObject(vp);
    this->signalNewObject(vp);
}

void Application::slotDeletedObject(const ViewProvider& vp)
{
    this->signalDeletedObject(vp);
    d->viewproviderMap.deleteObject(vp);
}

void Application::slotChangedObject(const ViewProvider& vp, const App::Property& prop)
{
    this->signalChangedObject(vp, prop);
    updateActions(true);
}

void Application::slotRelabelObject(const ViewProvider& vp)
{
    this->signalRelabelObject(vp);
}

void Application::slotActivatedObject(const ViewProvider& vp)
{
    this->signalActivatedObject(vp);
    updateActions();
}

void Application::slotInEdit(const Gui::ViewProviderDocumentObject& vp)
{
    this->signalInEdit(vp);
}

void Application::slotResetEdit(const Gui::ViewProviderDocumentObject& vp)
{
    this->signalResetEdit(vp);
}

void Application::onLastWindowClosed(Gui::Document* pcDoc)
{
    try {
        if (!d->isClosing && pcDoc) {
            // Call the closing mechanism from Python. This also checks whether pcDoc is the last
            // open document.
            Command::doCommand(Command::Doc,
                               "App.closeDocument(\"%s\")",
                               pcDoc->getDocument()->getName());
            if (!d->activeDocument && !d->documents.empty()) {
                Document* gdoc = nullptr;
                for (auto& v : d->documents) {
                    if (v.second->getDocument()->testStatus(App::Document::TempDoc)) {
                        continue;
                    }
                    else if (!gdoc) {
                        gdoc = v.second;
                    }

                    Gui::MDIView* view = v.second->getActiveView();
                    if (view) {
                        setActiveDocument(v.second);
                        getMainWindow()->setActiveWindow(view);
                        return;
                    }
                }

                if (gdoc) {
                    setActiveDocument(gdoc);
                    activateView(View3DInventor::getClassTypeId(), true);
                }
            }
        }
    }
    catch (const Base::Exception& e) {
        e.reportException();
    }
    catch (const Py::Exception&) {
        Base::PyException e;
        e.reportException();
    }
    catch (const std::exception& e) {
        Base::Console().error(
            "Unhandled std::exception caught in Application::onLastWindowClosed.\n"
            "The error message is: %s\n",
            e.what());
    }
    catch (...) {
        Base::Console().error(
            "Unhandled unknown exception caught in Application::onLastWindowClosed.\n");
    }
}

/// send Messages to the active view
bool Application::sendMsgToActiveView(const char* pMsg, const char** ppReturn)
{
    MDIView* pView = getMainWindow()->activeWindow();
    bool res = pView ? pView->onMsg(pMsg, ppReturn) : false;
    updateActions(true);
    return res;
}

bool Application::sendHasMsgToActiveView(const char* pMsg)
{
    MDIView* pView = getMainWindow()->activeWindow();
    return pView ? pView->onHasMsg(pMsg) : false;
}

/// send Messages to the active view
bool Application::sendMsgToFocusView(const char* pMsg, const char** ppReturn)
{
    MDIView* pView = getMainWindow()->activeWindow();
    if (!pView) {
        return false;
    }
    for (auto focus = qApp->focusWidget(); focus; focus = focus->parentWidget()) {
        if (focus == pView) {
            bool res = pView->onMsg(pMsg, ppReturn);
            updateActions(true);
            return res;
        }
    }
    return false;
}

bool Application::sendHasMsgToFocusView(const char* pMsg)
{
    MDIView* pView = getMainWindow()->activeWindow();
    if (!pView) {
        return false;
    }
    for (auto focus = qApp->focusWidget(); focus; focus = focus->parentWidget()) {
        if (focus == pView) {
            return pView->onHasMsg(pMsg);
        }
    }
    return false;
}

Gui::MDIView* Application::activeView() const
{
    if (activeDocument()) {
        return activeDocument()->getActiveView();
    }
    else {
        return nullptr;
    }
}

/**
 * @brief Application::activateView
 * Activates a view of the given type of the active document.
 * If a view of this type doesn't exist and \a create is true
 * a new view of this type will be created.
 * @param type
 * @param create
 */
void Application::activateView(const Base::Type& type, bool create)
{
    Document* doc = activeDocument();
    if (doc) {
        MDIView* mdiView = doc->getActiveView();
        if (mdiView && mdiView->isDerivedFrom(type)) {
            return;
        }
        std::list<MDIView*> mdiViews = doc->getMDIViewsOfType(type);
        if (!mdiViews.empty()) {
            doc->setActiveWindow(mdiViews.back());
        }
        else if (create) {
            doc->createView(type);
        }
    }
}

/// Getter for the active view
Gui::Document* Application::activeDocument() const
{
    return d->activeDocument;
}

Gui::Document* Application::editDocument() const
{
    return d->editDocument;
}

Gui::MDIView* Application::editViewOfNode(SoNode* node) const
{
    return d->editDocument ? d->editDocument->getViewOfNode(node) : nullptr;
}

void Application::setEditDocument(Gui::Document* doc)
{
    if (doc == d->editDocument) {
        return;
    }
    if (!doc) {
        d->editDocument = nullptr;
    }
    for (auto& v : d->documents) {
        v.second->_resetEdit();
    }
    d->editDocument = doc;
    updateActions();
}

void Application::setActiveDocument(Gui::Document* pcDocument)
{
    if (d->activeDocument == pcDocument) {
        return;  // nothing needs to be done
    }

    updateActions();

    if (pcDocument) {
        // This happens if a document with more than one view is about being
        // closed and a second view is activated. The document is still not
        // removed from the map.
        App::Document* doc = pcDocument->getDocument();
        if (d->documents.find(doc) == d->documents.end()) {
            return;
        }
    }
    d->activeDocument = pcDocument;
    std::string nameApp, nameGui;

    // This adds just a line to the macro file but does not set the active document
    // Macro recording of this is problematic, thus it's written out as comment.
    if (pcDocument) {
        nameApp += "App.setActiveDocument(\"";
        nameApp += pcDocument->getDocument()->getName();
        nameApp += "\")\n";
        nameApp += "App.ActiveDocument=App.getDocument(\"";
        nameApp += pcDocument->getDocument()->getName();
        nameApp += "\")";
        macroManager()->addLine(MacroManager::Cmt, nameApp.c_str());
        nameGui += "Gui.ActiveDocument=Gui.getDocument(\"";
        nameGui += pcDocument->getDocument()->getName();
        nameGui += "\")";
        macroManager()->addLine(MacroManager::Cmt, nameGui.c_str());
    }
    else {
        nameApp += "App.setActiveDocument(\"\")\n";
        nameApp += "App.ActiveDocument=None";
        macroManager()->addLine(MacroManager::Cmt, nameApp.c_str());
        nameGui += "Gui.ActiveDocument=None";
        macroManager()->addLine(MacroManager::Cmt, nameGui.c_str());
    }

    // Sets the currently active document
    try {
        Base::Interpreter().runString(nameApp.c_str());
        Base::Interpreter().runString(nameGui.c_str());
    }
    catch (const Base::Exception& e) {
        Base::Console().warning(e.what());
        return;
    }

#ifdef FC_DEBUG
    // May be useful for error detection
    if (d->activeDocument) {
        App::Document* doc = d->activeDocument->getDocument();
        Base::Console().log("Active document is %s (at %p)\n",
                            doc->getName(),
                            static_cast<void*>(doc));
    }
    else {
        Base::Console().log("No active document\n");
    }
#endif

    // notify all views attached to the application (not views belong to a special document)
    for (list<Gui::BaseView*>::iterator It = d->passive.begin(); It != d->passive.end(); ++It) {
        (*It)->setDocument(pcDocument);
    }
}

Gui::Document* Application::getDocument(const char* name) const
{
    App::Document* pDoc = App::GetApplication().getDocument(name);
    std::map<const App::Document*, Gui::Document*>::const_iterator it = d->documents.find(pDoc);
    if (it != d->documents.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

Gui::Document* Application::getDocument(const App::Document* pDoc) const
{
    std::map<const App::Document*, Gui::Document*>::const_iterator it = d->documents.find(pDoc);
    if (it != d->documents.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

void Application::showViewProvider(const App::DocumentObject* obj)
{
    ViewProvider* vp = getViewProvider(obj);
    if (vp) {
        vp->show();
    }
}

void Application::hideViewProvider(const App::DocumentObject* obj)
{
    ViewProvider* vp = getViewProvider(obj);
    if (vp) {
        vp->hide();
    }
}

Gui::ViewProvider* Application::getViewProvider(const App::DocumentObject* obj) const
{
    return d->viewproviderMap.getViewProvider(obj);
}

void Application::attachView(Gui::BaseView* pcView)
{
    d->passive.push_back(pcView);
}

void Application::detachView(Gui::BaseView* pcView)
{
    d->passive.remove(pcView);
}

void Application::onUpdate()
{
    // update all documents
    std::map<const App::Document*, Gui::Document*>::iterator It;
    for (It = d->documents.begin(); It != d->documents.end(); ++It) {
        It->second->onUpdate();
    }
    // update all the independent views
    for (std::list<Gui::BaseView*>::iterator It2 = d->passive.begin(); It2 != d->passive.end();
         ++It2) {
        (*It2)->onUpdate();
    }
}

/// Gets called if a view gets activated, this manages the whole activation scheme
void Application::viewActivated(MDIView* pcView)
{
#ifdef FC_DEBUG
    // May be useful for error detection
    Base::Console().log("Active view is %s (at %p)\n",
                        (const char*)pcView->windowTitle().toUtf8(),
                        static_cast<void*>(pcView));
#endif

    signalActivateView(pcView);
    getMainWindow()->setWindowTitle(pcView->buildWindowTitle());
    if (auto document = pcView->getGuiDocument()) {
        getMainWindow()->setWindowModified(document->isModified());
    }

    // Set the new active document which is taken of the activated view. If, however,
    // this view is passive we let the currently active document unchanged as we would
    // have no document active which is causing a lot of trouble.
    if (!pcView->isPassive()) {
        setActiveDocument(pcView->getGuiDocument());
    }
}

/// Gets called if a view gets closed
void Application::viewClosed(MDIView* pcView)
{
    signalCloseView(pcView);
}

void Application::updateActive()
{
    activeDocument()->onUpdate();
}

void Application::updateActions(bool delay)
{
    getMainWindow()->updateActions(delay);
}

void Application::tryClose(QCloseEvent* e)
{
    e->setAccepted(getMainWindow()->closeAllDocuments(false));
    if (!e->isAccepted()) {
        return;
    }

    // ask all passive views if closable
    for (std::list<Gui::BaseView*>::iterator It = d->passive.begin(); It != d->passive.end();
         ++It) {
        e->setAccepted((*It)->canClose());
        if (!e->isAccepted()) {
            return;
        }
    }

    if (e->isAccepted()) {
        d->isClosing = true;

        std::map<const App::Document*, Gui::Document*>::iterator It;

        // detach the passive views
        // SetActiveDocument(0);
        std::list<Gui::BaseView*>::iterator itp = d->passive.begin();
        while (itp != d->passive.end()) {
            (*itp)->onClose();
            itp = d->passive.begin();
        }

        App::GetApplication().closeAllDocuments();
    }
}

int Application::getUserEditMode(const std::string& mode) const
{
    if (mode.empty()) {
        return userEditMode;
    }
    for (auto const& uem : userEditModes) {
        if (uem.second.first == mode) {
            return uem.first;
        }
    }
    return -1;
}

std::pair<std::string, std::string> Application::getUserEditModeUIStrings(int mode) const
{
    if (mode == -1) {
        return userEditModes.at(userEditMode);
    }
    if (userEditModes.find(mode) != userEditModes.end()) {
        return userEditModes.at(mode);
    }
    return std::make_pair(std::string(), std::string());
}

bool Application::setUserEditMode(int mode)
{
    if (userEditModes.find(mode) != userEditModes.end() && userEditMode != mode) {
        userEditMode = mode;
        this->signalUserEditModeChanged(userEditMode);
        return true;
    }
    return false;
}

bool Application::setUserEditMode(const std::string& mode)
{
    for (auto const& uem : userEditModes) {
        if (uem.second.first == mode) {
            return setUserEditMode(uem.first);
        }
    }
    return false;
}

/**
 * Activate the matching workbench to the registered workbench handler with name \a name.
 * The handler must be an instance of a class written in Python.
 * Normally, if a handler gets activated a workbench with the same name gets created unless it
 * already exists.
 *
 * The old workbench gets deactivated before. If the workbench to the handler is already
 * active or if the switch fails false is returned.
 */
bool Application::activateWorkbench(const char* name)
{
    bool ok = false;
    WaitCursor wc;
    Workbench* oldWb = WorkbenchManager::instance()->active();
    if (oldWb && oldWb->name() == name) {
        return false;  // already active
    }

    Base::PyGILStateLocker lock;
    // we check for the currently active workbench and call its 'Deactivated'
    // method, if available
    PyObject* pcOldWorkbench = nullptr;
    if (oldWb) {
        pcOldWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, oldWb->name().c_str());
    }

    // get the python workbench object from the dictionary
    PyObject* pcWorkbench = nullptr;
    pcWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, name);
    // test if the workbench exists
    if (!pcWorkbench) {
        return false;
    }

    try {
        std::string type;
        Py::Object handler(pcWorkbench);
        if (!handler.hasAttr(std::string("__Workbench__"))) {
            // call its GetClassName method if possible
            Py::Callable method(handler.getAttr(std::string("GetClassName")));
            Py::Tuple args;
            Py::String result(method.apply(args));
            type = result.as_std_string("ascii");
            if (Base::Type::fromName(type.c_str())
                    .isDerivedFrom(Gui::PythonBaseWorkbench::getClassTypeId())) {
                Workbench* wb = WorkbenchManager::instance()->createWorkbench(name, type);
                if (!wb) {
                    throw Py::RuntimeError("Failed to instantiate workbench of type " + type);
                }
                handler.setAttr(std::string("__Workbench__"), Py::Object(wb->getPyObject(), true));
            }

            // import the matching module first
            Py::Callable activate(handler.getAttr(std::string("Initialize")));
            activate.apply(args);

            // Dependent on the implementation of a workbench handler the type
            // can be defined after the call of Initialize()
            if (type.empty()) {
                Py::String result(method.apply(args));
                type = result.as_std_string("ascii");
            }
        }

        // does the Python workbench handler have changed the workbench?
        Workbench* curWb = WorkbenchManager::instance()->active();
        if (curWb && curWb->name() == name) {
            ok = true;  // already active
        }
        // now try to create and activate the matching workbench object
        else if (WorkbenchManager::instance()->activate(name, type)) {
            getMainWindow()->activateWorkbench(QString::fromLatin1(name));
            this->signalActivateWorkbench(name);
            ok = true;
        }

        // if we still not have this member then it must be built-in C++ workbench
        // which could be created after loading the appropriate module
        if (!handler.hasAttr(std::string("__Workbench__"))) {
            Workbench* wb = WorkbenchManager::instance()->getWorkbench(name);
            if (wb) {
                handler.setAttr(std::string("__Workbench__"), Py::Object(wb->getPyObject(), true));
            }
        }

        // If the method Deactivate is available we call it
        if (pcOldWorkbench) {
            Py::Object handler(pcOldWorkbench);
            if (handler.hasAttr(std::string("Deactivated"))) {
                Py::Object method(handler.getAttr(std::string("Deactivated")));
                if (method.isCallable()) {
                    Py::Tuple args;
                    Py::Callable activate(method);
                    activate.apply(args);
                }
            }
        }

        if (oldWb) {
            oldWb->deactivated();
        }

        // If the method Activate is available we call it
        if (handler.hasAttr(std::string("Activated"))) {
            Py::Object method(handler.getAttr(std::string("Activated")));
            if (method.isCallable()) {
                Py::Tuple args;
                Py::Callable activate(method);
                activate.apply(args);
            }
        }

        // now get the newly activated workbench
        Workbench* newWb = WorkbenchManager::instance()->active();
        if (newWb) {
            if (!Instance->d->startingUp) {
                std::string nameWb = newWb->name();
                App::GetApplication()
                    .GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")
                    ->SetASCII("LastModule", nameWb.c_str());
            }
            newWb->activated();
        }
    }
    catch (Py::Exception&) {
        Base::PyException e;  // extract the Python error text
        QString msg = QString::fromUtf8(e.what());
        QRegularExpression rx;
        // ignore '<type 'exceptions.ImportError'>' prefixes
        rx.setPattern(QLatin1String("^\\s*<type 'exceptions.ImportError'>:\\s*"));
        auto match = rx.match(msg);
        while (match.hasMatch()) {
            msg = msg.mid(match.capturedLength());
            match = rx.match(msg);
        }

        Base::Console().error("%s\n", (const char*)msg.toUtf8());
        if (!d->startingUp) {
            Base::Console().error("%s\n", e.getStackTrace().c_str());
        }
        else {
            Base::Console().log("%s\n", e.getStackTrace().c_str());
        }

        if (!d->startingUp) {
            wc.restoreCursor();
            QMessageBox::critical(getMainWindow(),
                                  QObject::tr("Workbench failure"),
                                  QObject::tr("%1").arg(msg));
            wc.setWaitCursor();
        }
    }

    return ok;
}

QPixmap Application::workbenchIcon(const QString& wb) const
{
    Base::PyGILStateLocker lock;
    // get the python workbench object from the dictionary
    PyObject* pcWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, wb.toLatin1());
    // test if the workbench exists
    if (pcWorkbench) {
        // make a unique icon name
        std::stringstream str;
        str << static_cast<const void*>(pcWorkbench) << std::ends;
        std::string iconName = str.str();
        QPixmap icon;
        if (BitmapFactory().findPixmapInCache(iconName.c_str(), icon)) {
            return icon;
        }

        // get its Icon member if possible
        try {
            Py::Object handler(pcWorkbench);
            if (handler.hasAttr(std::string("Icon"))) {
                Py::Object member = handler.getAttr(std::string("Icon"));
                Py::String data(member);
                std::string content = data.as_std_string("utf-8");

                // test if in XPM format
                QByteArray ary;
                int strlen = (int)content.size();
                ary.resize(strlen);
                for (int j = 0; j < strlen; j++) {
                    ary[j] = content[j];
                }
                if (ary.indexOf("/* XPM */") > 0) {
                    // Make sure to remove crap around the XPM data
                    QList<QByteArray> lines = ary.split('\n');
                    QByteArray buffer;
                    buffer.reserve(ary.size() + lines.size());
                    for (QList<QByteArray>::iterator it = lines.begin(); it != lines.end(); ++it) {
                        QByteArray trim = it->trimmed();
                        if (!trim.isEmpty()) {
                            buffer.append(trim);
                            buffer.append('\n');
                        }
                    }
                    icon.loadFromData(buffer, "XPM");
                }
                else {
                    // is it a file name...
                    QString file = QString::fromUtf8(content.c_str());
                    icon.load(file);
                    if (icon.isNull()) {
                        // ... or the name of another icon?
                        icon = BitmapFactory().pixmap(file.toUtf8());
                    }
                }

                if (!icon.isNull()) {
                    BitmapFactory().addPixmapToCache(iconName.c_str(), icon);
                }

                return icon;
            }
        }
        catch (Py::Exception& e) {
            e.clear();
        }
    }

    QIcon icon = QApplication::windowIcon();
    if (!icon.isNull()) {
        QList<QSize> s = icon.availableSizes();
        if (!s.isEmpty()) {
            return icon.pixmap(s[0]);
        }
    }
    return {};
}

QString Application::workbenchToolTip(const QString& wb) const
{
    // get the python workbench object from the dictionary
    Base::PyGILStateLocker lock;
    PyObject* pcWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, wb.toLatin1());
    // test if the workbench exists
    if (pcWorkbench) {
        // get its ToolTip member if possible
        try {
            Py::Object handler(pcWorkbench);
            Py::Object member = handler.getAttr(std::string("ToolTip"));
            if (member.isString()) {
                Py::String tip(member);
                return QString::fromUtf8(tip.as_std_string("utf-8").c_str());
            }
        }
        catch (Py::Exception& e) {
            e.clear();
        }
    }

    return {};
}

QString Application::workbenchMenuText(const QString& wb) const
{
    // get the python workbench object from the dictionary
    Base::PyGILStateLocker lock;
    PyObject* pcWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, wb.toLatin1());
    // test if the workbench exists
    if (pcWorkbench) {
        // get its ToolTip member if possible
        Base::PyGILStateLocker locker;
        try {
            Py::Object handler(pcWorkbench);
            Py::Object member = handler.getAttr(std::string("MenuText"));
            if (member.isString()) {
                Py::String tip(member);
                return QString::fromUtf8(tip.as_std_string("utf-8").c_str());
            }
        }
        catch (Py::Exception& e) {
            e.clear();
        }
    }

    return {};
}

QStringList Application::workbenches() const
{
    // If neither 'HiddenWorkbench' nor 'ExtraWorkbench' is set then all workbenches are returned.
    const std::map<std::string, std::string>& config = App::Application::Config();
    auto ht = config.find("HiddenWorkbench");
    auto et = config.find("ExtraWorkbench");
    auto st = config.find("StartWorkbench");
    const char* start = (st != config.end() ? st->second.c_str() : "<none>");
    QStringList hidden, extra;
    if (ht != config.end()) {
        QString items = QString::fromLatin1(ht->second.c_str());
        hidden = items.split(QLatin1Char(';'), Qt::SkipEmptyParts);

        if (hidden.isEmpty()) {
            hidden.push_back(QLatin1String(""));
        }
    }
    if (et != config.end()) {
        QString items = QString::fromLatin1(et->second.c_str());

        extra = items.split(QLatin1Char(';'), Qt::SkipEmptyParts);
        if (extra.isEmpty()) {
            extra.push_back(QLatin1String(""));
        }
    }

    PyObject *key, *value;
    Py_ssize_t pos = 0;
    QStringList wb;
    // insert all items
    while (PyDict_Next(_pcWorkbenchDictionary, &pos, &key, &value)) {
        /* do something interesting with the values... */
        const char* wbName = PyUnicode_AsUTF8(key);
        // add only allowed workbenches
        bool ok = true;
        if (!extra.isEmpty() && ok) {
            ok = (extra.indexOf(QString::fromLatin1(wbName)) != -1);
        }
        if (!hidden.isEmpty() && ok) {
            ok = (hidden.indexOf(QString::fromLatin1(wbName)) == -1);
        }

        // okay the item is visible
        if (ok) {
            wb.push_back(QString::fromLatin1(wbName));
        }
        // also allow start workbench in case it is hidden
        else if (strcmp(wbName, start) == 0) {
            wb.push_back(QString::fromLatin1(wbName));
        }
    }

    return wb;
}

void Application::setupContextMenu(const char* recipient, MenuItem* items) const
{
    Workbench* actWb = WorkbenchManager::instance()->active();
    if (actWb) {
        // when populating the context-menu of a Python workbench invoke the method
        // 'ContextMenu' of the handler object
        if (actWb->isDerivedFrom<PythonWorkbench>()) {
            static_cast<PythonWorkbench*>(actWb)->clearContextMenu();
            Base::PyGILStateLocker lock;
            PyObject* pWorkbench = nullptr;
            pWorkbench = PyDict_GetItemString(_pcWorkbenchDictionary, actWb->name().c_str());

            try {
                // call its GetClassName method if possible
                Py::Object handler(pWorkbench);
                Py::Callable method(handler.getAttr(std::string("ContextMenu")));
                Py::Tuple args(1);
                args.setItem(0, Py::String(recipient));
                method.apply(args);
            }
            catch (Py::Exception& e) {
                Py::Object o = Py::type(e);
                e.clear();
                if (o.isString()) {
                    Py::String s(o);
                    std::clog << "Application::setupContextMenu: " << s.as_std_string("utf-8")
                              << std::endl;
                }
            }
        }
        actWb->createContextMenu(recipient, items);
    }
}

bool Application::isClosing()
{
    return d->isClosing;
}

MacroManager* Application::macroManager()
{
    return d->macroMngr;
}

CommandManager& Application::commandManager()
{
    return d->commandManager;
}

Gui::PreferencePackManager* Application::prefPackManager()
{
    return d->prefPackManager;
}

Gui::StyleParameters::ParameterManager* Application::styleParameterManager()
{
    return d->styleParameterManager;
}


//**************************************************************************
// Init, Destruct and singleton

namespace
{
void setCategoryFilterRules()
{
    QString filter;
    QTextStream stream(&filter);
    stream << "qt.qpa.xcb.warning=false\n";
    stream << "qt.qpa.mime.warning=false\n";
    stream << "qt.qpa.wayland.warning=false\n";
    stream << "qt.qpa.wayland.*.warning=false\n";
    stream << "qt.svg.warning=false\n";
    stream << "qt.xkb.compose.warning=false\n";
    stream << "kf.*.warning=false\n";
    stream.flush();
    QLoggingCategory::setFilterRules(filter);
}
}  // namespace

using _qt_msg_handler_old = void (*)(QtMsgType, const QMessageLogContext&, const QString&);
_qt_msg_handler_old old_qtmsg_handler = nullptr;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QByteArray output;
    if (context.category && strcmp(context.category, "default") != 0) {
        output.append('(');
        output.append(context.category);
        output.append(')');
        output.append(' ');
    }

    output.append(msg.toUtf8());

    switch (type) {
        case QtInfoMsg:
        case QtDebugMsg:
#ifdef FC_DEBUG
            Base::Console().message("%s\n", output.constData());
#else
            // do not stress user with Qt internals but write to log file if enabled
            Base::Console().log("%s\n", output.constData());
#endif
            break;
        case QtWarningMsg:
            Base::Console().warning("%s\n", output.constData());
            break;
        case QtCriticalMsg:
            Base::Console().error("%s\n", output.constData());
            break;
        case QtFatalMsg:
            Base::Console().error("%s\n", output.constData());
            abort();  // deliberately core dump
    }
#ifdef FC_OS_WIN32
    if (old_qtmsg_handler) {
        (*old_qtmsg_handler)(type, context, msg);
    }
#endif
}

#ifdef FC_DEBUG  // redirect Coin messages to FreeCAD
void messageHandlerCoin(const SoError* error, void* /*userdata*/)
{
    if (error && error->getTypeId() == SoDebugError::getClassTypeId()) {
        const SoDebugError* dbg = static_cast<const SoDebugError*>(error);
        const char* msg = error->getDebugString().getString();
        switch (dbg->getSeverity()) {
            case SoDebugError::INFO:
                Base::Console().message("%s\n", msg);
                break;
            case SoDebugError::WARNING:
                Base::Console().warning("%s\n", msg);
                break;
            default:  // error
                Base::Console().error("%s\n", msg);
                break;
        }
#ifdef FC_OS_WIN32
        if (old_qtmsg_handler) {
            (*old_qtmsg_handler)(QtDebugMsg, QMessageLogContext(), QString::fromLatin1(msg));
        }
#endif
    }
    else if (error) {
        const char* msg = error->getDebugString().getString();
        Base::Console().log(msg);
    }
}

#endif

// To fix bug #0000345 move Q_INIT_RESOURCE() outside initApplication()
static void init_resources()
{
    // init resources
    Q_INIT_RESOURCE(resource);
    Q_INIT_RESOURCE(translation);
    Q_INIT_RESOURCE(FreeCAD_translation);
}

void Application::initApplication()
{
    static bool init = false;
    if (init) {
        Base::Console().error("Tried to run Gui::Application::initApplication() twice!\n");
        return;
    }

    try {
        initTypes();
        new Base::ScriptProducer("FreeCADGuiInit", FreeCADGuiInit);
        init_resources();
        setCategoryFilterRules();
        old_qtmsg_handler = qInstallMessageHandler(messageHandler);
        init = true;
    }
    catch (...) {
        // force to flush the log
        App::Application::destructObserver();
        throw;
    }
}

void Application::initTypes()
{
    // clang-format off
    // views
    Gui::BaseView                               ::init();
    Gui::MDIView                                ::init();
    Gui::View3DInventor                         ::init();
    Gui::AbstractSplitView                      ::init();
    Gui::SplitView3DInventor                    ::init();
    Gui::TextDocumentEditorView                 ::init();
    Gui::EditorView                             ::init();
    Gui::PythonEditorView                       ::init();
    // View Provider
    Gui::ViewProvider                           ::init();
    Gui::ViewProviderExtension                  ::init();
    Gui::ViewProviderExtensionPython            ::init();
    Gui::ViewProviderGroupExtension             ::init();
    Gui::ViewProviderGroupExtensionPython       ::init();
    Gui::ViewProviderGeoFeatureGroupExtension   ::init();
    Gui::ViewProviderGeoFeatureGroupExtensionPython::init();
    Gui::ViewProviderOriginGroupExtension       ::init();
    Gui::ViewProviderOriginGroupExtensionPython ::init();
    Gui::ViewProviderSuppressibleExtension      ::init();
    Gui::ViewProviderSuppressibleExtensionPython::init();
    Gui::ViewProviderExtern                     ::init();
    Gui::ViewProviderDocumentObject             ::init();
    Gui::ViewProviderFeature                    ::init();
    Gui::ViewProviderDocumentObjectGroup        ::init();
    Gui::ViewProviderDocumentObjectGroupPython  ::init();
    Gui::ViewProviderDragger                    ::init();
    Gui::ViewProviderGeometryObject             ::init();
    Gui::ViewProviderImagePlane                 ::init();
    Gui::ViewProviderInventorObject             ::init();
    Gui::ViewProviderVRMLObject                 ::init();
    Gui::ViewProviderAnnotation                 ::init();
    Gui::ViewProviderAnnotationLabel            ::init();
    Gui::ViewProviderFeaturePython              ::init();
    Gui::ViewProviderGeometryPython             ::init();
    Gui::ViewProviderPlacement                  ::init();
    Gui::ViewProviderPlacementPython            ::init();
    Gui::ViewProviderDatum                      ::init();
    Gui::ViewProviderPlane                      ::init();
    Gui::ViewProviderPoint                      ::init();
    Gui::ViewProviderLine                       ::init();
    Gui::ViewProviderGeoFeatureGroup            ::init();
    Gui::ViewProviderGeoFeatureGroupPython      ::init();
    Gui::ViewProviderOriginGroup                ::init();
    Gui::ViewProviderPart                       ::init();
    Gui::ViewProviderCoordinateSystem           ::init();
    Gui::ViewProviderMaterialObject             ::init();
    Gui::ViewProviderMaterialObjectPython       ::init();
    Gui::ViewProviderTextDocument               ::init();
    Gui::ViewProviderTextureExtension           ::init();
    Gui::ViewProviderFaceTexture                ::init();
    Gui::ViewProviderLinkObserver               ::init();
    Gui::LinkView                               ::init();
    Gui::ViewProviderLink                       ::init();
    Gui::ViewProviderLinkPython                 ::init();
    Gui::ViewProviderVarSet                     ::init();
    Gui::AxisOrigin                             ::init();

    // Workbench
    Gui::Workbench                              ::init();
    Gui::StdWorkbench                           ::init();
    Gui::BlankWorkbench                         ::init();
    Gui::NoneWorkbench                          ::init();
    Gui::TestWorkbench                          ::init();
    Gui::PythonBaseWorkbench                    ::init();
    Gui::PythonBlankWorkbench                   ::init();
    Gui::PythonWorkbench                        ::init();

    // register transaction type
    new App::TransactionProducer<TransactionViewProvider>
            (ViewProviderDocumentObject::getClassTypeId());
    // clang-format on
}

void Application::initOpenInventor()
{
    // init the Inventor subsystem
    SoDB::init();
    SIM::Coin3D::Quarter::Quarter::init();
    SoFCDB::init();
}

void Application::runInitGuiScript()
{
    Base::Interpreter().runString(Base::ScriptFactory().ProduceScript("FreeCADGuiInit"));
}

namespace
{
bool onlySingleInstance(GUISingleApplication& mainApp)
{
    const std::map<std::string, std::string>& cfg = App::Application::Config();
    auto it = cfg.find("SingleInstance");
    if (it != cfg.end() && mainApp.isRunning()) {
        // send the file names to be opened to the server application so that this
        // opens them
        QDir cwd = QDir::current();
        std::list<std::string> files = App::Application::getCmdLineFiles();
        for (const auto& file : files) {
            QString fn = QString::fromUtf8(file.c_str(), static_cast<int>(file.size()));
            QFileInfo fi(fn);
            // if path name is relative make it absolute because the running instance
            // cannot determine the full path when trying to load the file
            if (fi.isRelative()) {
                fn = cwd.absoluteFilePath(fn);
                fn = QDir::cleanPath(fn);
            }

            fn.prepend(QLatin1String("OpenFile:"));
            if (!mainApp.sendMessage(fn)) {
                qWarning("Failed to send OpenFile message to server");
                break;
            }
        }

        return true;
    }

    return false;
}

void setAppNameAndIcon()
{
    const std::map<std::string, std::string>& cfg = App::Application::Config();

    // set application icon and window title
    auto it = cfg.find("Application");
    if (it != cfg.end()) {
        QApplication::setApplicationName(QString::fromUtf8(it->second.c_str()));
    }
    else {
        QApplication::setApplicationName(
            QString::fromStdString(App::Application::getExecutableName()));
    }
#ifndef Q_OS_MACOS
    QApplication::setWindowIcon(
        Gui::BitmapFactory().pixmap(App::Application::Config()["AppIcon"].c_str()));
#endif
}

void tryRunEventLoop(GUISingleApplication& mainApp)
{
    std::stringstream out;
    out << App::Application::getUserCachePath()
        << App::Application::getExecutableName()
        << "_"
        << App::Application::applicationPid()
        << ".lock";

    // open a lock file with the PID
    Base::FileInfo fi(out.str());
    Base::ofstream lock(fi);

    // In case the file_lock cannot be created start FreeCAD without IPC support.
#if !defined(FC_OS_WIN32) || (BOOST_VERSION < 107600)
    std::string filename = out.str();
#else
    std::wstring filename = fi.toStdWString();
#endif
    try {
        boost::interprocess::file_lock flock(filename.c_str());
        if (flock.try_lock()) {
            Base::Console().log("Init: Executing event loop...\n");
            QApplication::exec();

            // Qt can't handle exceptions thrown from event handlers, so we need
            // to manually rethrow SystemExitExceptions.
            if (mainApp.caughtException) {
                throw Base::SystemExitException(*mainApp.caughtException.get());
            }

            // close the lock file, in case of a crash we can see the existing lock file
            // on the next restart and try to repair the documents, if needed.
            flock.unlock();
            lock.close();
            fi.deleteFile();
        }
        else {
            Base::Console().warning("Failed to create a file lock for the IPC.\n"
                                    "The application will be terminated\n");
        }
    }
    catch (const boost::interprocess::interprocess_exception& e) {
        QString msg = QString::fromLocal8Bit(e.what());
        Base::Console().warning("Failed to create a file lock for the IPC: %s\n",
                                msg.toUtf8().constData());
    }
}

void runEventLoop(GUISingleApplication& mainApp)
{
    try {
        tryRunEventLoop(mainApp);
    }
    catch (const Base::SystemExitException&) {
        Base::Console().message("System exit\n");
        throw;
    }
    catch (const std::exception& e) {
        // catching nasty stuff coming out of the event loop
        Base::Console().error("Event loop left through unhandled exception: %s\n", e.what());
        App::Application::destructObserver();
        throw;
    }
    catch (...) {
        // catching nasty stuff coming out of the event loop
        Base::Console().error("Event loop left through unknown unhandled exception\n");
        App::Application::destructObserver();
        throw;
    }
}
}  // namespace

void Application::runApplication()
{
    StartupProcess::setupApplication();

    // A new QApplication
    Base::Console().log("Init: Creating Gui::Application and QApplication\n");

    int argc = App::Application::GetARGC();
    GUISingleApplication mainApp(argc, App::Application::GetARGV());

#if defined(FC_OS_LINUX) || defined(FC_OS_BSD)
    // If QT is running with native Wayland then inform Coin to use EGL
    if (QGuiApplication::platformName() == QString::fromStdString("wayland")) {
        setenv("COIN_EGL", "1", 1);
    }
#endif

    // Make sure that we use '.' as decimal point. See also
    // http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=559846
    // and issue #0002891
    // http://doc.qt.io/qt-5/qcoreapplication.html#locale-settings
    setlocale(LC_NUMERIC, "C");

    // check if a single or multiple instances can run
    if (onlySingleInstance(mainApp)) {
        return;
    }

    setAppNameAndIcon();

    StartupProcess process;
    process.execute();

    Application app(true);
    MainWindow mw;
    mw.setProperty("QuitOnClosed", true);

    // https://forum.freecad.org/viewtopic.php?f=3&t=15540
    // Needs to be set after app is created to override platform defaults (qt commit a2aa1f81a81)
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus, false);

#ifdef FC_DEBUG  // redirect Coin messages to FreeCAD
    SoDebugError::setHandlerCallback(messageHandlerCoin, 0);
#endif

    StartupPostProcess postProcess(&mw, app, &mainApp);
    postProcess.execute();

    Instance->d->startingUp = false;

    // gets called once we start the event loop
    QTimer::singleShot(0, &mw, SLOT(delayedStartup()));

    // run the Application event loop
    Base::Console().log("Init: Entering event loop\n");

    // boot phase reference point
    // https://forum.freecad.org/viewtopic.php?f=10&t=21665
    Gui::getMainWindow()->setProperty("eventLoop", true);

#ifdef USE_3DCONNEXION_NAVLIB
    if (Instance->pNavlibInterface) {
        Instance->pNavlibInterface->enableNavigation();
    }
#endif

    runEventLoop(mainApp);

    Base::Console().log("Finish: Event loop left\n");
}

bool Application::hiddenMainWindow()
{
    const std::map<std::string,std::string>& cfg = App::Application::Config();
    auto it = cfg.find("StartHidden");

    return it != cfg.end();
}

bool Application::testStatus(Status pos) const
{
    return d->StatusBits.test((size_t)pos);
}

void Application::setStatus(Status pos, bool on)
{
    d->StatusBits.set((size_t)pos, on);
}

void Application::setStyleSheet(const QString& qssFile, bool tiledBackground)
{
    Gui::MainWindow* mw = getMainWindow();
    auto mdi = mw->findChild<QMdiArea*>();
    mdi->setProperty("showImage", tiledBackground);

    // Qt's style sheet doesn't support it to define the link color of a QLabel
    // or in the property editor when an expression is set because therefore the
    // link color of the application's palette is used.
    // A workaround is to set a user-defined property to e.g. a QLabel and then
    // define it in the .qss file.
    //
    // Example:
    // QLabel label;
    // label.setProperty("haslink", QByteArray("true"));
    // label.show();
    // QColor link = label.palette().color(QPalette::Text);
    //
    // The .qss file must define it with:
    // QLabel[haslink="true"] {
    //     color: #rrggbb;
    // }
    //
    // See
    // https://stackoverflow.com/questions/5497799/how-do-i-customise-the-appearance-of-links-in-qlabels-using-style-sheets
    // and https://forum.freecad.org/viewtopic.php?f=34&t=50744
    static bool init = true;
    if (init) {
        init = false;
        mw->setProperty("fc_originalLinkCoor", qApp->palette().color(QPalette::Link));
    }
    else {
        QPalette newPal(qApp->palette());
        newPal.setColor(QPalette::Link, mw->property("fc_originalLinkCoor").value<QColor>());
        qApp->setPalette(newPal);
    }

    mw->setProperty("fc_currentStyleSheet", qssFile);
    mw->setProperty("fc_tiledBackground", tiledBackground);

    if (!qssFile.isEmpty()) {
        // Search for stylesheet in user-defined search paths.
        // For qss they are set-up in runApplication() with the prefix "qss"
        QString prefix(QLatin1String("qss:"));

        QFile f;
        if (QFile::exists(qssFile)) {
            f.setFileName(qssFile);
        }
        else if (QFile::exists(prefix + qssFile)) {
            f.setFileName(prefix + qssFile);
        }

        if (!f.fileName().isEmpty() && f.open(QFile::ReadOnly | QFile::Text)) {
            mdi->setBackground(QBrush(Qt::NoBrush));
            QTextStream str(&f);

            QString styleSheetContent = replaceVariablesInQss(str.readAll());

            qApp->setStyleSheet(styleSheetContent);

            ActionStyleEvent e(ActionStyleEvent::Clear);
            qApp->sendEvent(mw, &e);

            // This is a way to retrieve the link color of a .qss file when it's defined there.
            // The color will then be set to the application's palette.
            // Limitation: it doesn't work if the .qss file on purpose sets the same color as
            // for normal text. In this case the default link color is used.
            {
                QLabel l1, l2;
                l2.setProperty("haslink", QByteArray("true"));

                l1.show();
                l2.show();
                QColor text = l1.palette().color(QPalette::Text);
                QColor link = l2.palette().color(QPalette::Text);

                if (text != link) {
                    QPalette newPal(qApp->palette());
                    newPal.setColor(QPalette::Link, link);
                    qApp->setPalette(newPal);
                }
            }
        }
    }
    else {
        if (tiledBackground) {
            qApp->setStyleSheet(QString());
            ActionStyleEvent e(ActionStyleEvent::Restore);
            qApp->sendEvent(getMainWindow(), &e);
            mdi->setBackground(QPixmap(QLatin1String("images:background.png")));
        }
        else {
            qApp->setStyleSheet(QString());
            ActionStyleEvent e(ActionStyleEvent::Restore);
            qApp->sendEvent(getMainWindow(), &e);
            mdi->setBackground(QBrush(QColor(160, 160, 160)));
        }
    }

    // At startup time unpolish() mustn't be executed because otherwise the QSint widget
    // appear incorrect due to an outdated cache.
    // See https://doc.qt.io/qt-5/qstyle.html#unpolish-1
    // See https://forum.freecad.org/viewtopic.php?f=17&t=50783
    if (!d->startingUp) {
        if (mdi->style()) {
            mdi->style()->unpolish(qApp);
        }
    }
}

void Application::reloadStyleSheet()
{
    const MainWindow* mw = getMainWindow();

    const QString qssFile = mw->property("fc_currentStyleSheet").toString();
    const bool tiledBackground = mw->property("fc_tiledBackground").toBool();

    d->styleParameterManager->reload();

    setStyleSheet(qssFile, tiledBackground);
    OverlayManager::instance()->refresh(nullptr, true);
}

QString Application::replaceVariablesInQss(const QString& qssText)
{
    return QString::fromStdString(d->styleParameterManager->replacePlaceholders(qssText.toStdString()));
}

void Application::checkForDeprecatedSettings()
{
    // From 0.21, `FCBak` will be the intended default backup format
    bool makeBackups = App::GetApplication()
                           .GetParameterGroupByPath("User parameter:BaseApp/Preferences/Document")
                           ->GetBool("CreateBackupFiles", true);
    if (makeBackups) {
        bool useFCBakExtension =
            App::GetApplication()
                .GetParameterGroupByPath("User parameter:BaseApp/Preferences/Document")
                ->GetBool("UseFCBakExtension", true);
        if (!useFCBakExtension) {
            // TODO: This should be translated
            Base::Console().warning("The `.FCStd#` backup format is deprecated and may "
                                    "be removed in future versions.\n"
                                    "To update, check the 'Preferences->General->Document->Use "
                                    "date and FCBak extension' option.\n");
        }
    }
}

void Application::checkForPreviousCrashes()
{
    try {
        Gui::Dialog::DocumentRecoveryFinder finder;
        if (!finder.checkForPreviousCrashes()) {

            // If the recovery dialog wasn't shown check the cache size periodically
            Gui::Dialog::ApplicationCache cache;
            cache.applyUserSettings();
            if (cache.periodicCheckOfSize()) {
                qint64 total = cache.size();
                cache.performAction(total);
            }
        }
    }
    catch (const boost::interprocess::interprocess_exception& e) {
        QString msg = QString::fromLocal8Bit(e.what());
        Base::Console().warning("Failed check for previous crashes because of IPC error: %s\n",
                                msg.toUtf8().constData());
    }
}

App::Document* Application::reopen(App::Document* doc)
{
    if (!doc) {
        return nullptr;
    }
    std::string name = doc->FileName.getValue();
    std::set<const Gui::Document*> untouchedDocs;
    for (auto& v : d->documents) {
        if (!v.second->isModified() && !v.second->getDocument()->isTouched()) {
            untouchedDocs.insert(v.second);
        }
    }

    WaitCursor wc;
    wc.setIgnoreEvents(WaitCursor::NoEvents);

    if (doc->testStatus(App::Document::PartialDoc)
        || doc->testStatus(App::Document::PartialRestore)) {
        App::GetApplication().openDocument(name.c_str());
    }
    else {
        std::vector<std::string> docs;
        for (auto d : doc->getDependentDocuments(true)) {
            if (d->testStatus(App::Document::PartialDoc)
                || d->testStatus(App::Document::PartialRestore)) {
                docs.emplace_back(d->FileName.getValue());
            }
        }

        if (docs.empty()) {
            Document* gdoc = getDocument(doc);
            if (gdoc) {
                setActiveDocument(gdoc);
                if (!gdoc->setActiveView()) {
                    gdoc->setActiveView(nullptr, View3DInventor::getClassTypeId());
                }
            }
            return doc;
        }

        for (auto& file : docs) {
            App::DocumentInitFlags initFlags {
                .createView = false
            };
            App::GetApplication().openDocument(file.c_str(), initFlags);
        }
    }

    doc = nullptr;
    for (auto& v : d->documents) {
        if (name == v.first->FileName.getValue()) {
            doc = const_cast<App::Document*>(v.first);
        }
        if (untouchedDocs.contains(v.second)) {
            if (!v.second->isModified()) {
                continue;
            }
            bool reset = true;
            for (auto obj : v.second->getDocument()->getObjects()) {
                if (!obj->isTouched()) {
                    continue;
                }
                std::vector<App::Property*> props;
                obj->getPropertyList(props);
                for (auto prop : props) {
                    auto link = dynamic_cast<App::PropertyLinkBase*>(prop);
                    if (link && link->checkRestore()) {
                        reset = false;
                        break;
                    }
                }
                if (!reset) {
                    break;
                }
            }
            if (reset) {
                v.second->getDocument()->purgeTouched();
                v.second->setModified(false);
            }
        }
    }
    return doc;
}

void Application::getVerboseDPIStyleInfo(QTextStream& str) {
    // Add Stylesheet/Theme/Qtstyle information
    std::string styleSheet =
        App::GetApplication()
            .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow")
            ->GetASCII("StyleSheet");
    std::string theme =
        App::GetApplication()
            .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow")
            ->GetASCII("Theme");
#if QT_VERSION >= QT_VERSION_CHECK(6, 1, 0)
    std::string style = qApp->style()->name().toStdString();
#else
    std::string style =
        App::GetApplication()
            .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MainWindow")
            ->GetASCII("QtStyle");
    if (style.empty()) {
        style = "Qt default";
    }
#endif
    if (styleSheet.empty()) {
        styleSheet = "unset";
    }
    if (theme.empty()) {
        theme = "unset";
    }

    str << "Stylesheet/Theme/QtStyle: " << QString::fromStdString(styleSheet) << "/"
        << QString::fromStdString(theme) << "/" << QString::fromStdString(style) << "\n";

    // Add DPI information
    str << "Logical DPI/Physical DPI/Pixel Ratio: "
        << QApplication::primaryScreen()->logicalDotsPerInch()
        << "/"
        << QApplication::primaryScreen()->physicalDotsPerInch()
        << "/"
        << QApplication::primaryScreen()->devicePixelRatio()
        << "\n";
}
