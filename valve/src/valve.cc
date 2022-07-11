#include "valve.h"

Valve::Valve()
{
    name_ = "Valve";
    desc_ = "DescValve.....";
    flow_level_ = 0.0;
}

Valve::Valve(float flow)
{
    name_ = "Valve";
    desc_ = "DescValve.....";
    flow_level_ = flow;
}

float &Valve::getFlowLevel()
{
    return flow_level_;
}

void Valve::setFlowLevel(float lvl)
{
    flow_level_ = lvl;
}