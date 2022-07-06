#include <iostream>

using std::string;

class IotNode
{
protected:
    string name_;
    string desc_;

public:
    IotNode();
    IotNode(string,string);
    //~IotNode();
    void whoami();
};
