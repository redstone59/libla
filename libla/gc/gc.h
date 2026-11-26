#ifndef LA_GC_H_
#define LA_GC_H_

#include <stddef.h>

void GC_Init(size_t capacity);
void GC_Destroy();

void *GC_Alloc(size_t size);
void GC_Free(void *ptr);
void *GC_Realloc(void *ptr, size_t size);

void GC_Mark(void *ptr);
void GC_MakePermanent(void *ptr);
void GC_Sweep();

#endif // LA_GC_H_