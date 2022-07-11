#pragma once
#include "../../component/src/component.cc"

class Valve : public Component
{
private:
    float flow_level_;    // 0-1 range 
public:
    Valve();
    Valve(float);
   // ~Valve();
    float &getFlowLevel();
    void setFlowLevel(float);
};