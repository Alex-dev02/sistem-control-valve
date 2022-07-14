#include "room.hpp"

Room::Room()
{
    m_room_name = "<Room name not defined>";
}

Room::Room(string room_name, float temp)
{
    m_room_name = room_name;
    m_thermostat.setTargetTemp(temp);
}

void Room::whereami()
{
    std::cout << m_room_name << "\n"
              << "Setpoint to:" << m_thermostat.getTargetTemp()<<"\n";
              
}
