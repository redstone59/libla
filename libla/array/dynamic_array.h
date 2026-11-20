#ifndef LA_DYNAMIC_ARRAY_H_
#define LA_DYNAMIC_ARRAY_H_

#include <stddef.h>

typedef struct DynamicArray {
    float *elements;
    size_t count;
    size_t capacity;
} DynamicArray;

DynamicArray DynamicArray_New(size_t capacity);
void DynamicArray_Free(DynamicArray* self);

float DynamicArray_Get(DynamicArray* self, size_t index);
void DynamicArray_Set(DynamicArray* self, size_t index, float value);

void DynamicArray_Append(DynamicArray* self, float value);
void DynamicArray_Insert(DynamicArray* self, size_t index, float value);

void DynamicArray_RemoveAt(DynamicArray* self, size_t index);
void DynamicArray_Remove(DynamicArray* self, float value);

void DynamicArray_Print(DynamicArray* self, const char* specifier);

#endif // LA_DYNAMIC_ARRAY_H_