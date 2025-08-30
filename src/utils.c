#include "utils.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

float clamp_float(float value, float min, float max)
{
    const float res = value < min ? min : value;
    return res > max ? max : res;
}

// static inline void debug_log_impl(const char *format, ...)
// {
//     va_list args;
//     va_start(args, format);
//     printf("[DEBUG]: ");
//     vprintf(format, args);
//     printf("\n");
//     va_end(args);
// }

void error_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR]: ");
    vprintf(format, args);
    putchar('\n');
    va_end(args);
}

void error_exit(int code, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR]: ");
    vprintf(format, args);
    putchar('\n');
    va_end(args);
    exit(code);
}
