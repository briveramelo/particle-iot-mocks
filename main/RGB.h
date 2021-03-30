#pragma once

class RGBClass
{
public:
    static void control(bool control);
    static void brightness(uint8_t, bool update = true);
    static void color(uint8_t r, uint8_t g, uint8_t b);
};
extern RGBClass RGB;