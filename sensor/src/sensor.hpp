#pragma once
#include "../../component/src/component.hpp"
#include <stdlib.h>
#include <time.h>
class Sensor : public Component
{
private:
    float m_temp;

public:
    Sensor();
    //~Sensor();
    float &getTemp();
};
