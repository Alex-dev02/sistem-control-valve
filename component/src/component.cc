#include "component.h"

Component::Component()
{
    name_="<Name not set>";
    desc_="<Description not set>";
}

Component::Component(string name, string desc)
{
    name_=name;
    desc_=desc;
}

void Component::whoami()
{
    std::cout<<name_<<"\n"<<desc_<<"\n";
}