#include <gui/property.h>
#include <gui/widgets/control.h>

using namespace Novanix;

void Novanix::UpdateGUIPropertyTargetGUI(Control* target)
{
    if(target) target->ForcePaint();
}