#include "dynamic_array.h"

#include "../common.h"
#include <stdio.h>
#include <string.h>

#define DA_MIN_CAPACITY 32

static void DynamicArray__Resize(DynamicArray* self, size_t toFit) {
    size_t newSize = toFit < DA_MIN_CAPACITY ? DA_MIN_CAPACITY : self->capacity;
    while (newSize < toFit) {
        newSize <<= 1;
    }

    if (self->capacity == newSize) {
        return;
    }

    *self = (DynamicArray) {
        .elements = LA_REALLOC(self->elements, newSize * sizeof(float)),
        .count = self->count,
        .capacity = newSize
    };
}

DynamicArray DynamicArray_New(size_t capacity) {
    return (DynamicArray) {
        .elements = LA_ALLOC(capacity * sizeof(float)),
        .count = 0,
        .capacity = capacity
    };
}

void DynamicArray_Free(DynamicArray* self) {
    LA_FREE(self->elements);
    *self = (DynamicArray) {
        .elements = NULL,
        .count = 0,
        .capacity = 0
    };
}

float DynamicArray_Get(DynamicArray* self, size_t index) {
    panic_if(self->elements == NULL, "Attempted to get on freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to get outside of bounds of array.");

    return self->elements[index];
}

void DynamicArray_Set(DynamicArray* self, size_t index, float value) {
    panic_if(self->elements == NULL, "Attempted to set on freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to set outside of bounds of array.");
    
    self->elements[index] = value;
}

void DynamicArray_Append(DynamicArray* self, float value) {
    panic_if(self->elements == NULL, "Attempted to append to freed dynamic array.");
    
    if (self->count + 1 > self->capacity) {
        DynamicArray__Resize(self, self->count + 1);
    }

    self->elements[self->count++] = value;
}

void DynamicArray_Insert(DynamicArray* self, size_t index, float value) {
    panic_if(self->elements == NULL, "Attempted to insert in freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to insert outside of bounds of array.");
    
    if (self->count + 1 > self->capacity) {
        DynamicArray__Resize(self, self->capacity << 1);
    }

    memmove(&self->elements[index + 1], &self->elements[index], (self->count - index) * sizeof(float));
    self->elements[index] = value;
    self->count++;
}

void DynamicArray_RemoveAt(DynamicArray* self, size_t index) {
    panic_if(self->elements == NULL, "Attempted to remove from freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to remove outside of bounds of array.");

    memmove(&self->elements[index], &self->elements[index + 1], (self->count - index - 1) * sizeof(float));
    self->count--;
}

void DynamicArray_Remove(DynamicArray* self, float value) {
    panic_if(self->elements == NULL, "Attempted to remove from freed dynamic array.");
    
    for (size_t i = 0; i < self->count; i++) {
        if (DynamicArray_Get(self, i) != value) {
            continue;
        }

        DynamicArray_RemoveAt(self, i);
        return;
    }
}

void DynamicArray_Print(DynamicArray* self, const char* specifier) {
    printf("[ ");
    for (size_t i = 0; i < self->count; i++) {
        printf(specifier, DynamicArray_Get(self, i));
        if (i != self->count - 1) {
            printf(", ");
        }
    }
    printf(" ] (%zu/%zu)\n", self->count, self->capacity);
}