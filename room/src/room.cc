#include "room.h"

Room::Room()
{
    room_name_="<Room name not defined>";
    room_target_temp_=-1;
    room_current_temp_=-1;
}

void Room::whereami()
{
    std::cout<<room_name_<<"\n";
}