#pragma once
#include <iostream>

using std::string;

class Room
{
private:
    string room_name_;
    float room_target_temp_;
    float room_current_temp_;

public:
    Room();
    //~Room();
    void whereami();
};