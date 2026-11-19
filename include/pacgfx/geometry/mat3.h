#ifndef PACGFX_GEOMETRY_MAT3_H
#define PACGFX_GEOMETRY_MAT3_H

#include <pacgfx/geometry/vec2.h>

/*
 * 3x3 homogeneous matrix, row-major, column-vector convention: p' = M * p.
 * Entry (row r, column c) is m[r * 3 + c].
 * Affine matrices only: the bottom row is assumed to be (0, 0, 1).
 */
typedef struct {
    double m[3][3];
} mat3;

/* Matrix operations */
mat3 mat3_identity(void);
/* a * b: b is applied first, then a. */
mat3 mat3_multiply(mat3 a, mat3 b);
mat3 mat3_transpose(mat3 a);

/* Transformation matrices */
mat3 mat3_translation(double tx, double ty);
mat3 mat3_rotation(double radians);   /* counter-clockwise */
mat3 mat3_scaling(double sx, double sy);

/* Apply transformation */
vec2 mat3_transform_point(mat3 m, vec2 p);   /* treats p as (x, y, 1) */
vec2 mat3_transform_vector(mat3 m, vec2 v);  /* treats v as (x, y, 0): no translation */

/* Comparison: element-wise approx_equal. */
int mat3_equal(mat3 a, mat3 b);

/* Inverse of an affine matrix (bottom row assumed to be 0, 0, 1).
 * Returns 1 and writes *out on success; returns 0 and leaves *out untouched
 * if the linear part is singular (determinant approximately zero). */
int mat3_inverse(mat3 m, mat3 *out);

#endif
