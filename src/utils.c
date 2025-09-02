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

static void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
        error_exit(1, "could not allocate memory");
    }

    list_push_front(&heap_list.list, ptr);
    return ptr;
}

static void my_free(void *ptr) { free(ptr); }

static void heap_list_destroy(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = nullptr;
    }
}

HeapList heap_list_create()
{
    List list = list_init(sizeof(void *), heap_list_destroy, nullptr);
    return (HeapList){.list = list, .malloc = my_malloc};
}

void free_all(void) { clear_list(&heap_list.list); }
