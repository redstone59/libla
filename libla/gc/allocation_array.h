#ifndef LA_ALLOCATION_ARRAY_H_
#define LA_ALLOCATION_ARRAY_H_

#include <stddef.h>
#include <stdint.h>
#include "allocation.h"

typedef struct AllocationArray {
    GCAllocation *elements;
    size_t count;
    size_t capacity;
} AllocationArray;

AllocationArray AllocationArray_New(size_t capacity);
void AllocationArray_Free(AllocationArray* self);

GCAllocation AllocationArray_Get(AllocationArray* self, size_t index);
GCAllocation *AllocationArray_GetReference(AllocationArray* self, size_t index);
GCAllocation *AllocationArray_GetFromPointer(AllocationArray* self, void *ptr);
void AllocationArray_Set(AllocationArray* self, size_t index, GCAllocation value);

void AllocationArray_Append(AllocationArray* self, GCAllocation value);
void AllocationArray_Insert(AllocationArray* self, size_t index, GCAllocation value);

void AllocationArray_RemoveAt(AllocationArray* self, size_t index);
void AllocationArray_Remove(AllocationArray* self, GCAllocation value);

void AllocationArray_Print(AllocationArray* self, const char* specifier);

#endif // LA_DYNAMIC_ARRAY_H_