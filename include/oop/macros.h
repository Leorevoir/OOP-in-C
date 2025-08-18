#ifndef C_PLUS_MACROS_H_
#define C_PLUS_MACROS_H_

#define __cplus__inline __attribute__((always_inline, hot)) inline
#define __cplus__aligned(n) __attribute__((aligned(n)))
#define __cplus__pure __attribute__((pure))
#define __cplus__const __attribute__((const))

#define __cplus__ctor __attribute__((constructor))
#define __cplus__dtor __attribute__((destructor))

#define __cplus__unused __attribute__((unused))
#define __cplus__used __attribute__((used))
#define __cplus__defer(func) __attribute__((cleanup(func)))

#define __cplus__nodiscard [[nodiscard]]

#endif /* C_PLUS_MACROS_H_ */
