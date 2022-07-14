#pragma once
#include "../../component/src/component.hpp"

class Valve : public Component
{
private:
    float m_flow_level;    // 0-1 range 
public:
    Valve();
    Valve(float);
   // ~Valve();
    float getFlowLevel();
    void setFlowLevel(float);
};