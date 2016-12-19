#ifndef _ASSERT_H
#define _ASSERT_H 1

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define str(x) #x

#define assert(expr)                                         \
   do {                                                      \
      if(!(expr)) {                                          \
         printf("Failed assertion: (%s) at line %d of %s\n", \
                  str(expr), __LINE__, __FILE__);              \
         abort();                                            \
      }                                                      \
   } while(0)


#ifdef __cplusplus
}
#endif

#endif
