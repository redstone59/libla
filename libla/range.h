#ifndef LA_RANGE_H_
#define LA_RANGE_H_

#include <stddef.h>

#define RANGE_LEN(r) ((r).end - (r).start + 1)
#define RANGE(s, e) (Range) { (s), (e) }
#define RANGE_SINGULAR(s) RANGE(s, s)
#define RANGE_EXCLUSIVE(s, e) RANGE(s, e - 1)
#define EACH_IN_RANGE(type, lvalue, r) type (lvalue) = r.start; (lvalue) <= r.end; (lvalue)++

/**
 * An inclusive range from `start` to `end`.
 */
typedef struct Range {
    size_t start;
    size_t end;
    // int step
    // TODO: range step (0:2:10 => 0, 2, 4, 6, 8, 10) etc. etc.
} Range;

#endif // LA_RANGE_H_