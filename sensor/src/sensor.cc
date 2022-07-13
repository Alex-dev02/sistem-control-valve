#include "sensor.h"

Sensor::Sensor()
{
    name_="Sensor";
    desc_="DescSensor...";
    srand(time(NULL));
    temp_=rand()%35+1;      
}

float &Sensor::getTemp()
{
    return temp_;
}
