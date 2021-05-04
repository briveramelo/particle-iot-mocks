#pragma once
#include "application.h"
class Particle{
public:
    void process(){}
    bool connected(){return false;}
    void connect(){}
    void syncTime(){}
    void unsubscribe(){}
    void subscribe(const char * topic, void (*callback)(const char *topic, const char *data)){}
    void publish(const char *){}
    void publishVitals(){}
    void publishVitals(int interval){}
};
extern Particle Particle;