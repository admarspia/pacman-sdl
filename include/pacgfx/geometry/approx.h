#ifndef APPROX
#define APPROX

#include <math.h>

#define EPSILON 1e-9

static inline int approx_equal(float a, float b){
  return fabsf(a - b) < EPSILON;
}


#endif // !APPROX



