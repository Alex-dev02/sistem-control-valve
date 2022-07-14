#include "component.hpp"

Component::Component()
{
    m_name="<Name not set>";
    m_desc="<Description not set>";
}

Component::Component(string name, string desc)
{
    m_name=name;
    m_desc=desc;
}

void Component::whoami()
{
    std::cout<<m_name<<"\n"<<m_desc<<"\n";
}