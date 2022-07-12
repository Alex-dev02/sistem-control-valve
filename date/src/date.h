#pragma once 
#include <iostream>

class Date
{private:
    int day_;
    int month_;
    int year_;
    int hour_;
    int minute_;

public:
    Date();
    Date(int);
    Date(int,int);
    Date(int,int,int);
    Date(int,int,int,int);
    Date(int,int,int,int,int);
    //~Date();
    bool isValid();
};