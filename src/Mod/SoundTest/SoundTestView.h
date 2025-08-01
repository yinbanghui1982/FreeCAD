

#ifndef GUI_SOUNDTESTVIEW_H
#define GUI_SOUNDTESTVIEW_H

#include <Gui/MDIView.h>
#include <Gui/Window.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPlainTextEdit;
class QPrinter;
class QHBoxLayout;
class QToolButton;
class QCheckBox;
class QSpacerItem;
QT_END_NAMESPACE

using namespace Gui;

namespace SoundTest {

class EditorViewP;
class TextEdit;
class PythonTracingWatcher;

/**
 * A special view class which sends the messages from the application to
 * the editor and embeds it in a window.
 * @author Werner Mayer
 */
class __declspec(dllexport) SoundTestView : public MDIView, public WindowParameter
{
    Q_OBJECT

    TYPESYSTEM_HEADER_WITH_OVERRIDE();

public:

    SoundTestView(QWidget* widget, QWidget* parent);
    ~SoundTestView() override;    
};


} // namespace SoundTest

#endif // GUI_SOUNDTESTVIEW_H
