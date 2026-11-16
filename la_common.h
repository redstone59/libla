#ifndef LA_COMMON_H_
#define LA_COMMON_H_

#ifndef LA_NO_ASSERT
#   include <assert.h>
#   define panic_if(predicate, msg) assert(!(predicate) && msg)
#   define not_implemented assert(0 && "Function not implemented")
#endif

#endif // LA_COMMON_H_