#ifndef LA_GC_H_
#define LA_GC_H_

#include "allocation.h"

void *GC_Alloc(size_t size);
void GC_Free(void *ptr);

void GC_Mark(GCAllocation *alloc);
void GC_MakePermanent(GCAllocation *alloc);
void GC_Sweep();

#endif // LA_GC_H_