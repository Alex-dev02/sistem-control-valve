#pragma once
#include <iostream>

using std::string;

class Component
{
protected:
    string name_;
    string desc_;

public:
    Component();
    Component(string, string);
    //~Component();
    void whoami();
};