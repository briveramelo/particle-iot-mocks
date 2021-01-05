#pragma once
#include "application.h"
class Particle{
public:
    void process(){}
    bool connected(){return false;}
    void connect(){}
    void syncTime(){}
};
extern Particle Particle;