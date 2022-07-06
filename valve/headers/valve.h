#include "../../iot_node/headers/iot_note.h"

class Valve : public IotNode
{
private:
    float flow_level_;
public:
    Valve();
    Valve(float);
   // ~Valve();
    float &getFlowLevel();
    void setFlowLevel(float);
};
