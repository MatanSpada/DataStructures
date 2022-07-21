
#ifndef __UTILS_H__
#define __UTILS_H__

#ifndef SUCCESS

 #define SUCCESS (0)

#endif

#ifndef FAILURE

 #define FAILURE (1)

#endif

#ifndef TRUE

 #define TRUE (1)

#endif

#ifndef FALSE

 #define FALSE (0)

#endif

#ifndef MAX

 #define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif

#ifndef MIN

 #define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif

#ifndef ABS

 #define ABS(n) ((n) >= 0 ? (n) : -(n))

#endif

#ifndef GEN_SWAP

#define GEN_SWAP(type, a, b)\
{\
    type temp = (a);\
    (a) = (b);\
    (b) = temp;\
}

#endif


#ifndef ARR_SIZE

 #define ARR_SIZE(arr) (sizeof(arr) / sizeof(*arr))

#endif
#endif /*__UTILS_H__*/
