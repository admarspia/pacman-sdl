#ifndef MAT3_H
#define MAT3_H
#include "vec3.h"

typedef struct {
  vec3 cl0;
  vec3 cl1;
  vec3 cl2;

}mat3;

// Matrix operations
mat3 mat3_identity(void);
mat3 mat3_multiply(mat3 a, mat3 b);
mat3 mat3_transpose(mat3 a);

// Transformation matrices
mat3 mat3_translation(double tx, double ty);
mat3 mat3_rotation(double radians);
mat3 mat3_scaling(double sx, double sy);

// Apply transformation
vec3 mat3_transform_point(mat3 m, vec3 p);
vec3 mat3_transform_vector(mat3 m, vec3 v);

#endif
