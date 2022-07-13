#pragma once
#include "../../component/src/component.h"
#include <stdlib.h>
#include <time.h>
class Sensor : public Component
{
private:
    float temp_;

public:
    Sensor();
    //~Sensor();
    float &getTemp();
};
