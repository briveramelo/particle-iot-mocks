#pragma once
#include <stddef.h>
#include "Print.h"

class Print;
class Printable
{
public:
    size_t printTo(Print& p){return 0;}
};