#pragma once
class TimeMock
{
public:
    long now(){return 0;}
    char * timeStr(){return (char*)"";}
    int year(){return 0;}
    int month(){return 0;}
    int day(){return 0;}
    int hour(){return 0;}
    int minute(){return 0;}
    int second(){return 0;}
};

extern TimeMock Time;