/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
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
#if defined(__MINGW32__)
#define WNT  // avoid conflict with GUID
#endif
#ifndef _PreComp_
#include <iostream>

#include <QString>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextra-semi"
#endif

#include <OSD_Exception.hxx>
#include <Standard_Version.hxx>
#include <TColStd_IndexedDataMapOfStringString.hxx>
#include <TDataXtd_Shape.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFApp_Application.hxx>

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

#include <chrono>
#include "ExportOCAFGui.h"
#include "ImportOCAFGui.h"
#include "OCAFBrowser.h"

#include "dxf/ImpExpDxfGui.h"
#include <App/Document.h>
#include <App/DocumentObjectPy.h>
#include <Base/Console.h>
#include <Base/PyWrapParseTupleAndKeywords.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Document.h>
#include <Gui/MainWindow.h>
#include <Gui/ViewProviderLink.h>
#include <Mod/Import/App/ReaderGltf.h>
#include <Mod/Import/App/ReaderIges.h>
#include <Mod/Import/App/ReaderStep.h>
#include <Mod/Import/App/WriterGltf.h>
#include <Mod/Import/App/WriterIges.h>
#include <Mod/Import/App/WriterStep.h>
#include <Mod/Part/App/ImportIges.h>
#include <Mod/Part/App/ImportStep.h>
#include <Mod/Part/App/Interface.h>
#include <Mod/Part/App/OCAF/ImportExportSettings.h>
#include <Mod/Part/App/encodeFilename.h>
#include <Mod/Part/Gui/DlgExportStep.h>
#include <Mod/Part/Gui/DlgImportStep.h>
#include <Mod/Part/Gui/ViewProvider.h>


FC_LOG_LEVEL_INIT("Import", true, true)

namespace ImportGui
{

class Module: public Py::ExtensionModule<Module>
{
public:
    Module()
        : Py::ExtensionModule<Module>("ImportGui")
    {
        add_keyword_method("open",
                           &Module::insert,
                           "open(string) -- Open the file and create a new document.");
        add_keyword_method("insert",
                           &Module::insert,
                           "insert(string,string) -- Insert the file into the given document.");
        add_varargs_method("preScanDxf", &Module::preScanDxf, "preScanDxf(filepath) -> dict");
        add_varargs_method("readDXF",
                           &Module::readDXF,
                           "readDXF(filename,[document,ignore_errors,option_source]): Imports a "
                           "DXF file into the given document. ignore_errors is True by default.");
        add_varargs_method("importOptions",
                           &Module::importOptions,
                           "importOptions(string) -- Return the import options of a file type.");
        add_varargs_method("exportOptions",
                           &Module::exportOptions,
                           "exportOptions(string) -- Return the export options of a file type.");
        add_keyword_method("export",
                           &Module::exporter,
                           "export(list,string) -- Export a list of objects into a single file.");
        add_varargs_method("ocaf", &Module::ocaf, "ocaf(string) -- Browse the ocaf structure.");
        initialize("This module is the ImportGui module.");  // register with Python
    }

private:
    Py::Object preScanDxf(const Py::Tuple& args)
    {
        char* filepath_char = nullptr;
        if (!PyArg_ParseTuple(args.ptr(), "et", "utf-8", &filepath_char)) {
            throw Py::Exception();
        }
        std::string filepath(filepath_char);
        PyMem_Free(filepath_char);

#include <Mod/Import/App/dxf/ImpExpDxf.h>

        std::map<std::string, int> counts = Import::ImpExpDxfRead::PreScan(filepath);

        Py::Dict result;
        for (const auto& pair : counts) {
            result.setItem(Py::String(pair.first), Py::Long(pair.second));
        }
        return result;
    }

    Py::Object importOptions(const Py::Tuple& args)
    {
        char* Name {};
        if (!PyArg_ParseTuple(args.ptr(), "et", "utf-8", &Name)) {
            throw Py::Exception();
        }

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);
        std::string name8bit = Part::encodeFilename(Utf8Name);

        Py::Dict options;
        Base::FileInfo file(name8bit.c_str());
        if (file.hasExtension({"stp", "step"})) {
            PartGui::TaskImportStep dlg(Gui::getMainWindow());
            if (dlg.showDialog()) {
                if (!dlg.exec()) {
                    throw Py::Exception(Base::PyExc_FC_AbortIOException, "User cancelled import");
                }
            }
            auto stepSettings = dlg.getSettings();
            options.setItem("merge", Py::Boolean(stepSettings.merge));
            options.setItem("useLinkGroup", Py::Boolean(stepSettings.useLinkGroup));
            options.setItem("useBaseName", Py::Boolean(stepSettings.useBaseName));
            options.setItem("importHidden", Py::Boolean(stepSettings.importHidden));
            options.setItem("reduceObjects", Py::Boolean(stepSettings.reduceObjects));
            options.setItem("showProgress", Py::Boolean(stepSettings.showProgress));
            options.setItem("expandCompound", Py::Boolean(stepSettings.expandCompound));
            options.setItem("mode", Py::Long(stepSettings.mode));
            options.setItem("codePage", Py::Long(stepSettings.codePage));
        }
        return options;
    }

    Py::Object insert(const Py::Tuple& args, const Py::Dict& kwds)
    {
        char* Name;
        char* DocName = nullptr;
        PyObject* pyoptions = nullptr;
        PyObject* importHidden = Py_None;
        PyObject* merge = Py_None;
        PyObject* useLinkGroup = Py_None;
        int mode = -1;
        static const std::array<const char*, 8> kwd_list {"name",
                                                          "docName",
                                                          "options",
                                                          "importHidden",
                                                          "merge",
                                                          "useLinkGroup",
                                                          "mode",
                                                          nullptr};
        if (!Base::Wrapped_ParseTupleAndKeywords(args.ptr(),
                                                 kwds.ptr(),
                                                 "et|sO!O!O!O!i",
                                                 kwd_list,
                                                 "utf-8",
                                                 &Name,
                                                 &DocName,
                                                 &PyDict_Type,
                                                 &pyoptions,
                                                 &PyBool_Type,
                                                 &importHidden,
                                                 &PyBool_Type,
                                                 &merge,
                                                 &PyBool_Type,
                                                 &useLinkGroup,
                                                 &mode)) {
            throw Py::Exception();
        }

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);

        try {
            Base::FileInfo file(Utf8Name.c_str());

            App::Document* pcDoc = nullptr;
            if (DocName) {
                pcDoc = App::GetApplication().getDocument(DocName);
            }
            if (!pcDoc) {
                pcDoc = App::GetApplication().newDocument();
            }

            Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
            Handle(TDocStd_Document) hDoc;
            hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);
            ImportOCAFGui ocaf(hDoc, pcDoc, file.fileNamePure());
            ocaf.setImportOptions(ImportOCAFGui::customImportOptions());
            FC_TIME_INIT(t);
            FC_DURATION_DECL_INIT2(d1, d2);

            if (file.hasExtension({"stp", "step"})) {

                if (mode < 0) {
                    mode = ocaf.getMode();
                }
#if OCC_VERSION_HEX >= 0x070800
                Resource_FormatType cp = Resource_FormatType_UTF8;
#endif

                // new way
                if (pyoptions) {
                    Py::Dict options(pyoptions);
                    if (options.hasKey("merge")) {
                        ocaf.setMerge(static_cast<bool>(Py::Boolean(options.getItem("merge"))));
                    }
                    if (options.hasKey("useLinkGroup")) {
                        ocaf.setUseLinkGroup(
                            static_cast<bool>(Py::Boolean(options.getItem("useLinkGroup"))));
                    }
                    if (options.hasKey("useBaseName")) {
                        ocaf.setBaseName(
                            static_cast<bool>(Py::Boolean(options.getItem("useBaseName"))));
                    }
                    if (options.hasKey("importHidden")) {
                        ocaf.setImportHiddenObject(
                            static_cast<bool>(Py::Boolean(options.getItem("importHidden"))));
                    }
                    if (options.hasKey("reduceObjects")) {
                        ocaf.setReduceObjects(
                            static_cast<bool>(Py::Boolean(options.getItem("reduceObjects"))));
                    }
                    if (options.hasKey("showProgress")) {
                        ocaf.setShowProgress(
                            static_cast<bool>(Py::Boolean(options.getItem("showProgress"))));
                    }
                    if (options.hasKey("expandCompound")) {
                        ocaf.setExpandCompound(
                            static_cast<bool>(Py::Boolean(options.getItem("expandCompound"))));
                    }
                    if (options.hasKey("mode")) {
                        ocaf.setMode(static_cast<int>(Py::Long(options.getItem("mode"))));
                    }
#if OCC_VERSION_HEX >= 0x070800
                    if (options.hasKey("codePage")) {
                        int codePage = static_cast<int>(Py::Long(options.getItem("codePage")));
                        if (codePage >= 0) {
                            cp = static_cast<Resource_FormatType>(codePage);
                        }
                    }
#endif
                }

                if (mode && !pcDoc->isSaved()) {
                    auto gdoc = Gui::Application::Instance->getDocument(pcDoc);
                    if (!gdoc->save()) {
                        return Py::Object();
                    }
                }

                try {
                    Import::ReaderStep reader(file);
#if OCC_VERSION_HEX >= 0x070800
                    reader.setCodePage(cp);
#endif
                    reader.read(hDoc);
                }
                catch (OSD_Exception& e) {
                    Base::Console().error("%s\n", e.GetMessageString());
                    Base::Console().message("Try to load STEP file without colors...\n");

                    Part::ImportStepParts(pcDoc, Utf8Name.c_str());
                    pcDoc->recompute();
                }
            }
            else if (file.hasExtension({"igs", "iges"})) {
                try {
                    Import::ReaderIges reader(file);
                    reader.read(hDoc);
                }
                catch (OSD_Exception& e) {
                    Base::Console().error("%s\n", e.GetMessageString());
                    Base::Console().message("Try to load IGES file without colors...\n");

                    Part::ImportIgesParts(pcDoc, Utf8Name.c_str());
                    pcDoc->recompute();
                }
            }
            else if (file.hasExtension({"glb", "gltf"})) {
                Import::ReaderGltf reader(file);
                reader.read(hDoc);
            }
            else {
                throw Py::Exception(PyExc_IOError, "no supported file format");
            }

            FC_DURATION_PLUS(d1, t);
            if (merge != Py_None) {
                ocaf.setMerge(Base::asBoolean(merge));
            }
            if (importHidden != Py_None) {
                ocaf.setImportHiddenObject(Base::asBoolean(importHidden));
            }
            if (useLinkGroup != Py_None) {
                ocaf.setUseLinkGroup(Base::asBoolean(useLinkGroup));
            }
            if (mode >= 0) {
                ocaf.setMode(mode);
            }
            auto ret = ocaf.loadShapes();
            hApp->Close(hDoc);
            FC_DURATION_PLUS(d2, t);
            FC_DURATION_LOG(d1, "file read");
            FC_DURATION_LOG(d2, "import");
            FC_DURATION_LOG((d1 + d2), "total");

            if (ret) {
                App::GetApplication().setActiveDocument(pcDoc);
                auto gdoc = Gui::Application::Instance->getDocument(pcDoc);
                if (gdoc) {
                    gdoc->setActiveView();
                    Gui::Application::Instance->commandManager().runCommandByName("Std_ViewFitAll");
                }
                return Py::asObject(ret->getPyObject());
            }
        }
        catch (Standard_Failure& e) {
            throw Py::Exception(Base::PyExc_FC_GeneralError, e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            e.setPyException();
            throw Py::Exception();
        }

        return Py::None();
    }

    static std::map<std::string, Base::Color> getShapeColors(App::DocumentObject* obj,
                                                             const char* subname)
    {
        auto vp = Gui::Application::Instance->getViewProvider(obj);
        if (vp) {
            return vp->getElementColors(subname);
        }
        return {};
    }

    // This readDXF method is an almost exact duplicate of the one in Import::Module.
    // The only difference is the CDxfRead class derivation that is created.
    // It would seem desirable to have most of this code in just one place, passing it
    // e.g. a pointer to a function that does the 4 lines during the lifetime of the
    // CDxfRead object, but right now Import::Module and ImportGui::Module cannot see
    // each other's functions so this shared code would need some place to live where
    // both places could include a declaration.
    Py::Object readDXF(const Py::Tuple& args)
    {
        char* Name = nullptr;
        const char* DocName = nullptr;
        const char* optionSource = nullptr;
        std::string defaultOptions = "User parameter:BaseApp/Preferences/Mod/Draft";
        bool IgnoreErrors = true;
        if (!PyArg_ParseTuple(args.ptr(),
                              "et|sbs",
                              "utf-8",
                              &Name,
                              &DocName,
                              &IgnoreErrors,
                              &optionSource)) {
            throw Py::Exception();
        }

        std::string EncodedName = std::string(Name);
        PyMem_Free(Name);

        Base::FileInfo file(EncodedName.c_str());
        if (!file.exists()) {
            throw Py::RuntimeError("File doesn't exist");
        }

        if (optionSource) {
            defaultOptions = optionSource;
        }

        App::Document* pcDoc = nullptr;
        if (DocName) {
            pcDoc = App::GetApplication().getDocument(DocName);
        }
        else {
            pcDoc = App::GetApplication().getActiveDocument();
        }
        if (!pcDoc) {
            pcDoc = App::GetApplication().newDocument(DocName);
        }

        try {
            // read the DXF file
            ImpExpDxfReadGui dxf_file(EncodedName, pcDoc);
            dxf_file.setOptionSource(defaultOptions);
            dxf_file.setOptions();

            auto startTime = std::chrono::high_resolution_clock::now();
            dxf_file.DoRead(IgnoreErrors);
            auto endTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = endTime - startTime;
            dxf_file.setImportTime(elapsed.count());

            pcDoc->recompute();
            return dxf_file.getStatsAsPyObject();
        }
        catch (const Standard_Failure& e) {
            throw Py::RuntimeError(e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }
    }

    Py::Object exportOptions(const Py::Tuple& args)
    {
        char* Name;
        if (!PyArg_ParseTuple(args.ptr(), "et", "utf-8", &Name)) {
            throw Py::Exception();
        }

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);
        std::string name8bit = Part::encodeFilename(Utf8Name);

        Py::Dict options;
        Base::FileInfo file(name8bit.c_str());

        if (file.hasExtension({"stp", "step"})) {
            PartGui::TaskExportStep dlg(Gui::getMainWindow());
            if (!dlg.showDialog() || dlg.exec()) {
                auto stepSettings = dlg.getSettings();
                options.setItem("exportHidden", Py::Boolean(stepSettings.exportHidden));
                options.setItem("keepPlacement", Py::Boolean(stepSettings.keepPlacement));
                options.setItem("legacy", Py::Boolean(stepSettings.exportLegacy));
            }
        }

        return options;
    }

    Py::Object exporter(const Py::Tuple& args, const Py::Dict& kwds)
    {
        PyObject* object;
        char* Name;
        PyObject* pyoptions = nullptr;
        PyObject* pyexportHidden = Py_None;
        PyObject* pylegacy = Py_None;
        PyObject* pykeepPlacement = Py_None;
        static const std::array<const char*, 7>
            kwd_list {"obj", "name", "options", "exportHidden", "legacy", "keepPlacement", nullptr};
        if (!Base::Wrapped_ParseTupleAndKeywords(args.ptr(),
                                                 kwds.ptr(),
                                                 "Oet|O!O!O!O!",
                                                 kwd_list,
                                                 &object,
                                                 "utf-8",
                                                 &Name,
                                                 &PyDict_Type,
                                                 &pyoptions,
                                                 &PyBool_Type,
                                                 &pyexportHidden,
                                                 &PyBool_Type,
                                                 &pylegacy,
                                                 &PyBool_Type,
                                                 &pykeepPlacement)) {
            throw Py::Exception();
        }

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);

        // clang-format off
        // determine export options
        Part::OCAF::ImportExportSettings settings;

        // still support old way
        bool legacyExport = (pylegacy         == Py_None ? settings.getExportLegacy()
                                                         : Base::asBoolean(pylegacy));
        bool exportHidden = (pyexportHidden   == Py_None ? settings.getExportHiddenObject()
                                                         : Base::asBoolean(pyexportHidden));
        bool keepPlacement = (pykeepPlacement == Py_None ? settings.getExportKeepPlacement()
                                                         : Base::asBoolean(pykeepPlacement));
        // clang-format on

        // new way
        if (pyoptions) {
            Py::Dict options(pyoptions);
            if (options.hasKey("legacy")) {
                legacyExport = static_cast<bool>(Py::Boolean(options.getItem("legacy")));
            }
            if (options.hasKey("exportHidden")) {
                exportHidden = static_cast<bool>(Py::Boolean(options.getItem("exportHidden")));
            }
            if (options.hasKey("keepPlacement")) {
                keepPlacement = static_cast<bool>(Py::Boolean(options.getItem("keepPlacement")));
            }
        }

        try {
            Py::Sequence list(object);
            std::vector<App::DocumentObject*> objs;
            for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
                PyObject* item = (*it).ptr();
                if (PyObject_TypeCheck(item, &(App::DocumentObjectPy::Type))) {
                    auto pydoc = static_cast<App::DocumentObjectPy*>(item);
                    objs.push_back(pydoc->getDocumentObjectPtr());
                }
            }

            Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
            Handle(TDocStd_Document) hDoc;
            hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);

            Import::ExportOCAF2 ocaf(hDoc, &getShapeColors);
            if (!legacyExport || !ocaf.canFallback(objs)) {
                ocaf.setExportOptions(Import::ExportOCAF2::customExportOptions());
                ocaf.setExportHiddenObject(exportHidden);
                ocaf.setKeepPlacement(keepPlacement);

                ocaf.exportObjects(objs);
            }
            else {
                bool keepExplicitPlacement = true;
                ExportOCAFGui ocaf(hDoc, keepExplicitPlacement);
                ocaf.exportObjects(objs);
            }

            Base::FileInfo file(Utf8Name.c_str());
            if (file.hasExtension({"stp", "step"})) {
                ParameterGrp::handle hGrp = App::GetApplication().GetParameterGroupByPath(
                    "User parameter:BaseApp/Preferences/Mod/Part/STEP");
                std::string scheme = hGrp->GetASCII("Scheme", Part::Interface::writeStepScheme());
                std::list<std::string> supported = Part::supportedSTEPSchemes();
                if (std::ranges::find(supported, scheme) != supported.end()) {
                    Part::Interface::writeStepScheme(scheme.c_str());
                }

                Import::WriterStep writer(file);
                writer.write(hDoc);
            }
            else if (file.hasExtension({"igs", "iges"})) {
                Import::WriterIges writer(file);
                writer.write(hDoc);
            }
            else if (file.hasExtension({"glb", "gltf"})) {
                Import::WriterGltf writer(file);
                writer.write(hDoc);
            }

            hApp->Close(hDoc);
        }
        catch (Standard_Failure& e) {
            throw Py::Exception(Base::PyExc_FC_GeneralError, e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            e.setPyException();
            throw Py::Exception();
        }

        return Py::None();
    }
    Py::Object ocaf(const Py::Tuple& args)
    {
        const char* Name;
        if (!PyArg_ParseTuple(args.ptr(), "s", &Name)) {
            throw Py::Exception();
        }

        try {
            Base::FileInfo file(Name);

            Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
            Handle(TDocStd_Document) hDoc;
            hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);

            if (file.hasExtension({"stp", "step"})) {
                Import::ReaderStep reader(file);
                reader.read(hDoc);
            }
            else if (file.hasExtension({"igs", "iges"})) {
                Import::ReaderIges reader(file);
                reader.read(hDoc);
            }
            else if (file.hasExtension({"glb", "gltf"})) {
                Import::ReaderGltf reader(file);
                reader.read(hDoc);
            }
            else {
                throw Py::Exception(PyExc_IOError, "no supported file format");
            }

            OCAFBrowser::showDialog(QString::fromStdString(file.fileName()), hDoc);
            hApp->Close(hDoc);
        }
        catch (Standard_Failure& e) {
            throw Py::Exception(Base::PyExc_FC_GeneralError, e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            e.setPyException();
            throw Py::Exception();
        }

        return Py::None();
    }
};

PyObject* initModule()
{
    return Base::Interpreter().addModule(new Module);
}

}  // namespace ImportGui
