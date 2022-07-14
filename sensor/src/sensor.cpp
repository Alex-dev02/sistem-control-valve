#include "sensor.hpp"

Sensor::Sensor()
{
    m_name="Sensor";
    m_desc="DescSensor...";
    srand(time(NULL));
    m_temp=rand()%35+1;      
}

float &Sensor::getTemp()
{
    return m_temp;
}
