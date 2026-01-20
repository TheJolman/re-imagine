#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "arena.h"

Arena arena_init(size_t capacity) {
    Arena a = {};
    a.buffer = (uint8_t *)malloc(capacity);
    a.capacity = capacity;
    a.offset = 0;
    return a;
}

void *arena_alloc(Arena *a, size_t size) {
    // 8-byte alignment
    size_t align = 8;
    size_t aligned_offset = (a->offset + align - 1) & ~(align - 1);

    if (aligned_offset + size <= a->capacity) {
        void *ptr = &a->buffer[aligned_offset];
        a->offset = aligned_offset + size;
        return ptr;
    }
    return nullptr;
}

// Free everyting at once
void arena_reset(Arena *a) { a->offset = 0; }

// Free backing memory
void arena_free(Arena *a) {
    free(a->buffer);
    a->buffer = nullptr;
    a->capacity = 0;
    a->offset = 0;
}
