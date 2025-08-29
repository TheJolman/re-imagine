#include "utils.h"

float clamp_float(float value, float min, float max)
{
    const float res = value < min ? min : value;
    return res > max ? max : res;
}
