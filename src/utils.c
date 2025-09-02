#include "utils.h"
#include "list.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// This defines the global heap_list declared in utils.h
HeapList heap_list;

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
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
}

void error_exit(int code, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
    exit(code);
}

/**
 * @brief Frees the underlying memory block tracked by the list.
 * @param p A pointer to the list's node data, which itself holds the pointer
 * to the allocated memory block.
 */
static void free_user_pointer(void *p)
{
    // p is the node->data, which is a container holding the user's pointer.
    // We need to dereference it to get the user's pointer and free that.
    if (p)
    {
        free(*(void **)p);
    }
}

static void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr)
    {
        error_exit(1, "could not allocate memory");
    }

    list_push_front(&heap_list.list, &ptr);
    return ptr;
}

static void my_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    if (!list_delete(&heap_list.list, &ptr))
    {
        error_log("Attempted to free non-tracked pointer or double free: %p", ptr);
    }
}

/**
 * @brief Returns an object with .malloc and .free methods that uses a linked list to keep track
 *        of memory allocations
 */
HeapList heap_list_create()
{
    List list = list_init(sizeof(void *), free_user_pointer, nullptr);
    return (HeapList){.list = list, .malloc = my_malloc, .free = my_free};
}

void free_all(void) { clear_list(&heap_list.list); }
