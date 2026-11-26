#ifndef LA_ALLOCATION_H_
#define LA_ALLOCATION_H_

#include <stdint.h>

typedef enum GCFlagPositions {
    GC_MARK = 1 << 0,
    GC_UNDESTROYABLE = 1 << 1 
} GCFlagPositions;

typedef uint8_t GCFlags;

typedef struct GCAllocation {
    void *ptr;
    GCFlags flags;
} GCAllocation;

#endif //LA_ALLOCATION_H_