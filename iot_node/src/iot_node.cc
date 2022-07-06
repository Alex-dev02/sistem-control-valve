#include "../headers/iot_note.h"

IotNode::IotNode()
{
    name_="<Name not set>";
    desc_="<Description not set>";
}

IotNode::IotNode(string name, string desc)
{
    name_=name;
    desc_=desc;
}

void IotNode::whoami()
{
    std::cout<<name_<<"\n"<<desc_<<"\n";
}