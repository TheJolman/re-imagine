#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdio.h>

#ifdef DEBUG
#define debug_log(fmt, ...) debug_log_impl(fmt, ##__VA_ARGS__)
#else
#define debug_log(fmt, ...) ((void)0)
#endif

void debug_log_impl(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[DEBUG]: ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

#endif // !DEBUG_H
