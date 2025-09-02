#include "utils.h"
#include "list.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

float clamp_float(float value, float min, float max)
{
    const float res = value < min ? min : value;
    return res > max ? max : res;
}

void error_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR] ");
    vprintf(format, args);
    putchar('\n');
    va_end(args);
}

void error_exit(int code, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR] ");
    vprintf(format, args);
    putchar('\n');
    va_end(args);
    exit(code);
}

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
    }
    return ptr;
}

static void heap_list_destroy(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = nullptr;
    }
}

List heap_list_create()
{
    List list = list_init(sizeof(void *), heap_list_destroy, nullptr);

    return list;
}

void free_all(void);
