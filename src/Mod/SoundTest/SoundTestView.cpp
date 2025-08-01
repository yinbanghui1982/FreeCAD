
#include <QApplication>
#include <QCheckBox>
#include <QClipboard>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPlainTextEdit>
#include <QPrintPreviewDialog>
#include <QSpacerItem>
#include <QStyle>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextStream>
#include <QTimer>
#include <QToolButton>


#include "SoundTestView.h"

#include <Gui/Application.h>
#include <Gui/FileDialog.h>
#include <Gui/Macro.h>
#include <Gui/MainWindow.h>
#include <Gui/PythonEditor.h>
#include <Gui/PythonTracing.h>
#include <Gui/WaitCursor.h>

#include <Base/Exception.h>
#include <Base/Interpreter.h>
#include <Base/Parameter.h>


using namespace SoundTest;

TYPESYSTEM_SOURCE_ABSTRACT(SoundTest::SoundTestView, Gui::MDIView)

/**
 *  Constructs a EditorView which is a child of 'parent', with the
 *  name 'name'.
 */
SoundTestView::SoundTestView(QWidget* widget, QWidget* parent)
    : MDIView(nullptr, parent, Qt::WindowFlags())
    , WindowParameter("SoundTest")
{
    // Create the layout containing the workspace and a tab bar
    auto hbox = new QFrame(this);
    hbox->setFrameShape(QFrame::StyledPanel);
    hbox->setFrameShadow(QFrame::Sunken);
    auto layout = new QVBoxLayout();
    layout->setContentsMargins(1, 1, 1, 1);
    layout->addWidget(widget);
    hbox->setLayout(layout);
    setCentralWidget(hbox);

    // setWindowIcon(d->textEdit->windowIcon());

}

/** Destroys the object and frees any allocated resources */
SoundTestView::~SoundTestView()
{

}


// #include "moc_EditorView.cpp"
