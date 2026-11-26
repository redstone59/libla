#include "allocation_array.h"

#include "../common.h"
#include <stdio.h>
#include <string.h>

#define DA_MIN_CAPACITY 32

static void AllocationArray__Resize(AllocationArray* self, size_t toFit) {
    size_t newSize = toFit < DA_MIN_CAPACITY ? DA_MIN_CAPACITY : self->capacity;
    while (newSize < toFit) {
        newSize <<= 1;
    }

    if (self->capacity == newSize) {
        return;
    }

    *self = (AllocationArray) {
        .elements = LA_REALLOC(self->elements, newSize * sizeof(GCAllocation)),
        .count = self->count,
        .capacity = newSize
    };
}

AllocationArray AllocationArray_New(size_t capacity) {
    return (AllocationArray) {
        .elements = LA_ALLOC(capacity * sizeof(GCAllocation)),
        .count = 0,
        .capacity = capacity
    };
}

void AllocationArray_Free(AllocationArray* self) {
    LA_FREE(self->elements);
    *self = (AllocationArray) {
        .elements = NULL,
        .count = 0,
        .capacity = 0
    };
}

GCAllocation AllocationArray_Get(AllocationArray* self, size_t index) {
    panic_if(self->elements == NULL, "Attempted to get on freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to get outside of bounds of array.");

    return self->elements[index];
}

GCAllocation *AllocationArray_GetReference(AllocationArray* self, size_t index) {
    panic_if(self->elements == NULL, "Attempted to get on freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to get outside of bounds of array.");

    return &self->elements[index];
}

GCAllocation *AllocationArray_GetFromPointer(AllocationArray* self, void *ptr) {
    for (size_t i = 0; i < self->count; i++) {
        GCAllocation *alloc = AllocationArray_GetReference(self, i);
        if (alloc->ptr != ptr) {
            continue;
        }
        return alloc;
    }

    return NULL;
}

void AllocationArray_Set(AllocationArray* self, size_t index, GCAllocation value) {
    panic_if(self->elements == NULL, "Attempted to set on freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to set outside of bounds of array.");
    
    self->elements[index] = value;
}

void AllocationArray_Append(AllocationArray* self, GCAllocation value) {
    panic_if(self->elements == NULL, "Attempted to append to freed dynamic array.");
    
    if (self->count + 1 > self->capacity) {
        AllocationArray__Resize(self, self->count + 1);
    }

    self->elements[self->count++] = value;
}

void AllocationArray_Insert(AllocationArray* self, size_t index, GCAllocation value) {
    panic_if(self->elements == NULL, "Attempted to insert in freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to insert outside of bounds of array.");
    
    if (self->count + 1 > self->capacity) {
        AllocationArray__Resize(self, self->capacity << 1);
    }

    memmove(&self->elements[index + 1], &self->elements[index], (self->count - index) * sizeof(GCAllocation));
    self->elements[index] = value;
    self->count++;
}

void AllocationArray_RemoveAt(AllocationArray* self, size_t index) {
    panic_if(self->elements == NULL, "Attempted to remove from freed dynamic array.");
    panic_if(index < 0 || index >= self->count, "Attempted to remove outside of bounds of array.");

    memmove(&self->elements[index], &self->elements[index + 1], (self->count - index - 1) * sizeof(GCAllocation));
    self->count--;
}

void AllocationArray_Remove(AllocationArray* self, GCAllocation value) {
    panic_if(self->elements == NULL, "Attempted to remove from freed dynamic array.");
    
    for (size_t i = 0; i < self->count; i++) {
        if (AllocationArray_Get(self, i).ptr != value.ptr) {
            continue;
        }

        AllocationArray_RemoveAt(self, i);
        return;
    }
}

#define DA_SEPARATOR ","

void AllocationArray_Print(AllocationArray* self, const char* specifier) {
    printf("[ ");
    for (size_t i = 0; i < self->count; i++) {
        printf(specifier, AllocationArray_Get(self, i));
        if (i != self->count - 1) {
            printf(DA_SEPARATOR " ");
        }
    }
    printf(" ] (%zu/%zu)\n", self->count, self->capacity);
}