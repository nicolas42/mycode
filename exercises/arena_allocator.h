#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* memory;
    size_t used;
    size_t size;
} Arena;

// Function declarations
void arena_init(Arena* arena, size_t size);
void* arena_alloc(Arena* arena, size_t size);
void arena_free(Arena* arena);

#ifdef ARENA_ALLOCATOR_IMPLEMENTATION

void arena_init(Arena* arena, size_t size) {
    arena->memory = malloc(size);
    if (arena->memory == NULL) {
        fprintf(stderr, "Failed to allocate memory for arena of size %zu\n", size);
        exit(1);
    }
    arena->used = 0;
    arena->size = size;
}

void* arena_alloc(Arena* arena, size_t size) {
    void* result;
    if (arena->used + size > arena->size) {
        fprintf(stderr, "Arena is full, cannot allocate more memory\n");
        return NULL;
    }

    result = arena->memory + arena->used;
    arena->used += size;
    return result;
}

void arena_free(Arena* arena) {
    free(arena->memory);
    arena->memory = NULL;
    arena->used = 0;
    arena->size = 0;
}

#endif // ARENA_ALLOCATOR_IMPLEMENTATION

#endif // ARENA_ALLOCATOR_H

