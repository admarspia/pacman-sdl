#include "../../include/pacgfx/geometry/approx.h"

int approx_equal(float a, float b){
  return fabsf(a - b) < EPSILON;
}


