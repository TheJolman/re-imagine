#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t offset;
} Arena;

Arena arena_init(size_t capacity);

void *arena_alloc(Arena *a, size_t size);

/** Free everyting at once
 */
void arena_reset(Arena *a);

/** Free backing memory
 */
void arena_free(Arena *a);
