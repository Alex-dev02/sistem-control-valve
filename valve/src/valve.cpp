#include "valve.hpp"

Valve::Valve()
{
    m_name = "Valve";
    m_desc = "DescValve.....";
    m_flow_level = 0.0;
}

Valve::Valve(float flow)
{
    m_name = "Valve";
    m_desc = "DescValve.....";
    m_flow_level = flow;
}

float Valve::getFlowLevel()
{
    return m_flow_level;
}

void Valve::setFlowLevel(float lvl)
{
    m_flow_level = lvl;
}