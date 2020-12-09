#pragma once
class TimeMock
{
public:
    long now(){return 0;}
};

extern TimeMock Time;