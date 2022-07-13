#include "room.h"

Room::Room()
{
    room_name_ = "<Room name not defined>";
}

Room::Room(string room_name, float temp)
{
    room_name_ = room_name;
    thermostat_.setTargetTemp(temp);
}

void Room::whereami()
{
    std::cout << room_name_ << "\n"
              << "Setpoint to:" << thermostat_.getTargetTemp()<<"\n";
              
}
