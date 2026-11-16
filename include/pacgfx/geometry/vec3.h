#ifndef VEC3_H
#define VEC3_H
#include "./approx.h"

typedef struct {
  double x;
  double y;
  double z;
}vec3;


// Arithmetic
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_negate(vec3 a);
vec3 vec3_scale(vec3 a, double scalar);
vec3 vec3_divide(vec3 a, double scalar);

// Geometric properties
double vec3_length(vec3 a);
double vec3_length_squared(vec3 a);
double vec3_distance(vec3 a, vec3 b);
double vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);

// Vector operations
vec3 vec3_normalize(vec3 a);
vec3 vec3_perpendicular(vec3 a);
double vec3_angle(vec3 a, vec3 b);

// Interpolation and comparison
vec3 vec3_lerp(vec3 a, vec3 b, double t);
int vec3_equal(vec3 a, vec3 b);


#endif
