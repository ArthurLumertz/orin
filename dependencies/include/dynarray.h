#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void **data;
    size_t capacity;
    size_t size;
} DynArray;

static inline void DYNARR_create(DynArray *arr, size_t initial_capacity) {
    arr->capacity = initial_capacity;
    arr->size = 0;
    arr->data = (void**)malloc(initial_capacity * sizeof(void*));
    if (arr->data == NULL) {
        fprintf(stderr, "ERROR: DYNARR_create(): malloc failed\n");
        exit(EXIT_FAILURE);
    }
}

static inline void DYNARR_resize(DynArray *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_resize(): arr is NULL\n");
        return;
    }

    arr->capacity *= 2;
    void **new_data = (void**)realloc(arr->data, arr->capacity * sizeof(void*));
    if (new_data == NULL) {
        fprintf(stderr, "ERROR: DYNARR_resize(): realloc failed\n");
        free(arr->data);
        exit(EXIT_FAILURE);
    }
    arr->data = new_data;
}

static inline void DYNARR_push(DynArray *arr, void *value) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_push(): arr is NULL\n");
        return;
    }

    if (arr->size >= arr->capacity) {
        DYNARR_resize(arr);
    }
    arr->data[arr->size++] = value;
}

static inline void *DYNARR_fetch(DynArray *arr, size_t idx) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_fetch(): arr is NULL\n");
        return NULL;
    }

    if (idx >= arr->size) {
        fprintf(stderr, "ERROR: DYNARR_fetch(): index %zu out of bounds (size=%zu)\n",
               idx, arr->size);
        return NULL;
    }
    return arr->data[idx];
}

static inline void DYNARR_delete(DynArray *arr, size_t idx) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_delete(): arr is NULL\n");
        return;
    }

    if (idx >= arr->size) {
        fprintf(stderr, "ERROR: DYNARR_delete(): index %zu out of bounds (size=%zu)\n",
               idx, arr->size);
        return;
    }

    free(arr->data[idx]);
    
    memmove(&arr->data[idx], 
            &arr->data[idx + 1], 
            (arr->size - idx - 1) * sizeof(void*));
    
    arr->size--;
}

static inline void DYNARR_free(DynArray *arr) {
    if (arr == NULL) {
        fprintf(stderr, "ERROR: DYNARR_free(): arr is NULL\n");
        return;
    }

    for (size_t i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

#ifdef __cplusplus
}
#endif

#endif