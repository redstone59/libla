#include "gc.h"

#include "allocation_array.h"
#include "../common.h"

static AllocationArray allocs = {0};

void *GC_Alloc(size_t size) {
    GCAllocation new = {
        .ptr = LA_ALLOC(size),
        .flags = 0,
    };

    return new.ptr;
}

void GC_Free(void *ptr) {
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);
        if (alloc.ptr == ptr) {
            LA_FREE(ptr);
            return;
        }
    }
}

void GC_Mark(GCAllocation *alloc) {
    alloc->flags |= GC_MARK;
}

void GC_MakePermanent(GCAllocation *alloc) {
    alloc->flags |= GC_UNDESTROYABLE;
}

void GC_Sweep() {
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);

        if (alloc.flags & GC_UNDESTROYABLE != 0) {
            continue;
        }

        if (alloc.flags & GC_MARK != 0) {
            continue;
        }
        
        AllocationArray_Remove(&allocs, alloc);
        LA_FREE(alloc.ptr);
    }
}