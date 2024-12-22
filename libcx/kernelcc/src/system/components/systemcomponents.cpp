#include <system/components/systemcomponent.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

SystemComponent::SystemComponent(char* name, char* description)
{
    this->Name = name;
    this->Description = description;
}

char* SystemComponent::GetComponentName()
{
    return this->Name;
}
char* SystemComponent::GetComponentDescription()
{
    return this->Description;
}