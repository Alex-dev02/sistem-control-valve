#include "../../iot_node/headers/iot_note.h"

class Thermostat : public IotNode
{
private:
    float target_temp_;
    float current_temp_;

public:
    Thermostat();
    Thermostat(float);
   // ~Thermostat();

    float &getCurrentTemp();
    void setCurrentTemp(float);

    float &getTargetTemp();
    void setTargetTemp(float);
};
