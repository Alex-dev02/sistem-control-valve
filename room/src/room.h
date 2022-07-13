#pragma once
#include <iostream>
#include <vector>
#include "../../thermostat/src/thermostat.h"
#include "../../valve/src/valve.h"
using std::string;
using std::vector;

class Room
{
private:
    string room_name_;
    Thermostat thermostat_;
    vector<Valve> valves_;

public:
    Room();
    Room(string,float);
    //~Room();
    void whereami();
};