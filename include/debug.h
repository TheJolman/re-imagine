#pragma once

#include <stdarg.h>
#include <stdio.h>

#ifdef DEBUG

/*
 * Print a formatted debug message to standard output.
 *
 * The implementation uses a variadic argument list to forward
 * the arguments to vprintf. A prefix and trailing newline are
 * added for clarity.
 */
static inline void debug_log_impl(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("[DEBUG]: ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

/* Invoke the implementation when DEBUG is defined. */
#define debug_log(fmt, ...) debug_log_impl(fmt, ##__VA_ARGS__)

#else

/* No-op when DEBUG is not defined. */
#define debug_log(fmt, ...) ((void)0)

#endif
