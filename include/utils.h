#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct
{
    void *elements;
    size_t size;
    size_t element_size;
} Array;

/**
 * Clamps a float between a min and max range
 * @return float Original value if within range, or min/max otherwise
 */
float ClampFloat(float value, float min, float max);

#endif
