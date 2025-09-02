/**
 * @file utils.h
 * @brief Utility functions and data structures
 */

#pragma once

#include "list.h"
#include <stddef.h>

/**
 * @brief Dynamic array structure
 */
typedef struct
{
    void *elements;      ///< Pointer to array elements
    size_t size;         ///< Number of elements in array
    size_t element_size; ///< Size of each element in bytes
} Array;

/**
 * @brief Result type for error handling
 */
typedef struct
{
    void *value;     ///< Pointer to result value (NULL on error)
    const char *err; ///< Error message (NULL on success)
} Result;

/**
 * @brief Clamps a float between a min and max range
 *
 * @param value The value to clamp
 * @param min Minimum allowed value
 * @param max Maximum allowed value
 * @return Original value if within range, or min/max otherwise
 */
float clamp_float(float value, float min, float max);

/**
 * @brief Logs an error message to stderr
 *
 * @param format Printf-style format string
 * @param ... Variable arguments for the format string
 */
void error_log(const char *format, ...);

/**
 * @brief Logs an error message and exits the program
 *
 * @param code Exit code to return
 * @param format Printf-style format string
 * @param ... Variable arguments for the format string
 */
void error_exit(int code, const char *format, ...);

extern List heap_list; ///< Global linked list for allocating and freeing memory

void *my_malloc(size_t size);
List heap_list_create();
void free_all(void);
