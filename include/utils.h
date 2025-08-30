#pragma once

#include <stddef.h>

typedef struct
{
    void *elements;
    size_t size;
    size_t element_size;
} Array;

typedef struct
{
    void *value;
    const char *err;
} Result;

/**
 * Clamps a float between a min and max range
 * @return float Original value if within range, or min/max otherwise
 */
float clamp_float(float value, float min, float max);

void error_log(const char *format, ...);
void error_exit(int code, const char *format, ...);
