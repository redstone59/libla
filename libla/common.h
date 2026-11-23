#ifndef LA_COMMON_H_
#define LA_COMMON_H_

#ifndef LA_NO_ASSERT
#   include <assert.h>
#   define panic_if(predicate, msg) assert(!(predicate) && msg)
#   define not_implemented assert(0 && "Function not implemented")
#else
#   define panic_if(predicate, msg)
#   define not_implemented exit(1)
#endif

#ifndef LA_ALLOC
#   include <stdlib.h>
#   define LA_ALLOC malloc
#endif

#ifndef LA_FREE
#   include <stdlib.h>
#   define LA_FREE free
#endif

#ifndef LA_REALLOC
#   include <stdlib.h>
#   define LA_REALLOC realloc
#endif

#define LA_ABS(x) ((x) < 0 ? -(x) : (x))

#endif // LA_COMMON_H_