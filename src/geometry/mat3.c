#include "../../include/pacgfx/geometry/mat3.h"
#include <math.h>

// Matrix operations
mat3 mat3_identity(void) {
    return (mat3){
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
}

mat3 mat3_multiply(mat3 a, mat3 b) {
    mat3 result;

    vec3 row0 = {a.cl0.x, a.cl1.x, a.cl2.x};
    vec3 row1 = {a.cl0.y, a.cl1.y, a.cl2.y};
    vec3 row2 = {a.cl0.z, a.cl1.z, a.cl2.z};

    result.cl0 = (vec3){
        vec3_dot(row0, b.cl0),
        vec3_dot(row1, b.cl0),
        vec3_dot(row2, b.cl0)
    };

    result.cl1 = (vec3){
        vec3_dot(row0, b.cl1),
        vec3_dot(row1, b.cl1),
        vec3_dot(row2, b.cl1)
    };

    result.cl2 = (vec3){
        vec3_dot(row0, b.cl2),
        vec3_dot(row1, b.cl2),
        vec3_dot(row2, b.cl2)
    };

    return result;
}

mat3 mat3_transpose(mat3 m) {
    return (mat3){
        {m.cl0.x, m.cl1.x, m.cl2.x},
        {m.cl0.y, m.cl1.y, m.cl2.y},
        {m.cl0.z, m.cl1.z, m.cl2.z}
    };
}

// Transformation matrices
mat3 mat3_translation(double tx, double ty) {
    return (mat3){
        {1, 0, 0},
        {0, 1, 0},
        {tx, ty, 1}
    };
}

mat3 mat3_rotation(double radians) {
    double c = cos(radians);
    double s = sin(radians);

    return (mat3){
        {c, s, 0},
        {-s, c, 0},
        {0, 0, 1}
    };
}

mat3 mat3_scaling(double sx, double sy) {
    return (mat3){
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };
}

// Apply transformation
vec3 mat3_transform_point(mat3 m, vec3 p) {
    return (vec3){
        m.cl0.x * p.x + m.cl1.x * p.y + m.cl2.x * p.z,
        m.cl0.y * p.x + m.cl1.y * p.y + m.cl2.y * p.z,
        m.cl0.z * p.x + m.cl1.z * p.y + m.cl2.z * p.z
    };
}

vec3 mat3_transform_vector(mat3 m, vec3 v) {
    // Ignore translation by using homogeneous coordinate w = 0.
    v.z = 0.0;

    return (vec3){
        m.cl0.x * v.x + m.cl1.x * v.y,
        m.cl0.y * v.x + m.cl1.y * v.y,
        m.cl0.z * v.x + m.cl1.z * v.y
    };
}
