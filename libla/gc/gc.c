#include "gc.h"

#include <stdio.h>
#include <stdbool.h>
#include "allocation_array.h"
#include "../common.h"

static AllocationArray allocs;
static bool initialised = false;

void GC_Init(size_t capacity) {
    allocs = AllocationArray_New(capacity);
    initialised = true;
}

void GC_Destroy() {
    printf("Destroying GC...\n");
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);
        printf("Freeing allocation %p\n", alloc.ptr);
        LA_FREE(alloc.ptr);
        alloc.ptr = NULL;
    }

    AllocationArray_Free(&allocs);
    initialised = false;
}

void *GC_Alloc(size_t size) {
    GCAllocation new = {
        .ptr = LA_ALLOC(size),
        .flags = 0,
    };

    AllocationArray_Append(&allocs, new);
    AllocationArray_Print(&allocs, "%p");

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
    for (size_t i = 0; i < allocs.count; i++) {
        GCAllocation alloc = AllocationArray_Get(&allocs, i);

        printf("Checking allocation %p... ", alloc.ptr);

        if ((alloc.flags & GC_UNDESTROYABLE) != 0) {
            printf("OK (indestructible)\n");
            continue;
        }

        if ((alloc.flags & GC_MARK) != 0) {
            printf("OK (marked)\n");
            continue;
        }

        printf("freed (not marked).\n");
        AllocationArray_Remove(&allocs, alloc);
        LA_FREE(alloc.ptr);
    }
}