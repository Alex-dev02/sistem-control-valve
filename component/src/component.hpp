#pragma once
#include <iostream>

using std::string;

class Component
{
protected:
    string m_name;
    string m_desc;

public:
    Component();
    Component(string, string);
    //~Component();
    virtual void whoami();
};