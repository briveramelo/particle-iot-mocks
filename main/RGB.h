#pragma once

class RGBClass
{
public:
    static void control(bool control);
    static void brightness(uint8_t, bool update=true);
};
extern RGBClass RGB;