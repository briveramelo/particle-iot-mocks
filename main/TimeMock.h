#pragma once
class TimeMock
{
public:
    long now(){return 0;}
    char * timeStr(){return "";}
};

extern TimeMock Time;