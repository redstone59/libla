#include "gc.h"

#include <stdio.h>
#include <stdbool.h>

#include "../common.h"
#include "allocation.h"
#include "allocation_array.h"

static AllocationArray allocs;
static bool initialised = false;

void GC_Init(size_t capacity) {
    allocs = AllocationArray_New(capacity);
    initialised = true;
    Libla_Log(LA_LOGLEVEL_DEBUG, "Initialised garbage collector!");
}

void GC_Destroy() {
    Libla_Log(LA_LOGLEVEL_DEBUG, "Destroying garbage collector...");
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);
        LA_FREE(alloc.ptr);
        alloc.ptr = NULL;
    }

    Libla_Log(LA_LOGLEVEL_DEBUG, "Garbage collector destroyed! Freed %zu objects.", allocs.count);
    AllocationArray_Free(&allocs);
    initialised = false;
}

void *GC_Alloc(size_t size) {
    GCAllocation new = {
        .ptr = LA_ALLOC(size),
        .flags = 0,
    };

    AllocationArray_Append(&allocs, new);

    return new.ptr;
}

void GC_Free(void *ptr) {
    GCAllocation* alloc = AllocationArray_GetFromPointer(&allocs, ptr);
    if (alloc == NULL) {
        return;
    }

    LA_FREE(ptr);
    AllocationArray_Remove(&allocs, *alloc);
}

void *GC_Realloc(void *ptr, size_t size) {
    GCAllocation* alloc = AllocationArray_GetFromPointer(&allocs, ptr);
    if (alloc == NULL) {
        return NULL;
    }

    return LA_REALLOC(alloc->ptr, size);
}

void GC_Mark(void *ptr) {
    GCAllocation* alloc = AllocationArray_GetFromPointer(&allocs, ptr);
    if (alloc == NULL) {
        return;
    }

    alloc->flags |= GC_MARK;
}

void GC_MakePermanent(void *ptr) {
    GCAllocation* alloc = AllocationArray_GetFromPointer(&allocs, ptr);
    if (alloc == NULL) {
        return;
    }

    alloc->flags |= GC_UNDESTROYABLE;
}

void GC_Sweep() {
    Libla_Log(LA_LOGLEVEL_DEBUG, "Beginning garbage collector sweep...");
    size_t freedObjects = 0;
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);

        if ((alloc.flags & GC_UNDESTROYABLE) != 0) {
            continue;
        }

        if ((alloc.flags & GC_MARK) != 0) {
            continue;
        }

        AllocationArray_Remove(&allocs, alloc);
        freedObjects++;
        LA_FREE(alloc.ptr);
    }
    Libla_Log(LA_LOGLEVEL_DEBUG, "Freed %zu objects on sweep", freedObjects);
}