#include "../../include/pacgfx/geometry/vec3.h"
#include <math.h>

// Arithmetic
vec3 vec3_add(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec3_sub(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 vec3_negate(vec3 a) {
    return (vec3){-a.x, -a.y, -a.z};
}

vec3 vec3_scale(vec3 a, double scalar) {
    return (vec3){a.x * scalar, a.y * scalar, a.z * scalar};
}

vec3 vec3_divide(vec3 a, double scalar) {
    if (approx_equal(scalar, 0.0f))
        return (vec3){0.0, 0.0, 0.0};

    return (vec3){a.x / scalar, a.y / scalar, a.z / scalar};
}

// Geometric properties
double vec3_length_squared(vec3 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

double vec3_length(vec3 a) {
    return sqrt(vec3_length_squared(a));
}

double vec3_distance(vec3 a, vec3 b) {
    return vec3_length(vec3_sub(a, b));
}

double vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_cross(vec3 a, vec3 b) {
    return (vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// Vector operations
vec3 vec3_normalize(vec3 a) {
    double len = vec3_length(a);

    if (approx_equal(len, 0.0f))
        return (vec3){0.0, 0.0, 0.0};

    return vec3_divide(a, len);
}

vec3 vec3_perpendicular(vec3 a) {
    // Choose an axis that is not parallel to a.
    vec3 axis = fabs(a.x) < fabs(a.y)
        ? (vec3){1.0, 0.0, 0.0}
        : (vec3){0.0, 1.0, 0.0};

    if (approx_equal(a.x, 0.0f) &&
        approx_equal(a.y, 0.0f) &&
        approx_equal(a.z, 0.0f))
        return (vec3){0.0, 0.0, 0.0};

    return vec3_normalize(vec3_cross(a, axis));
}

double vec3_angle(vec3 a, vec3 b) {
    double denominator = vec3_length(a) * vec3_length(b);

    if (approx_equal(denominator, 0.0f))
        return 0.0;

    double cosine = vec3_dot(a, b) / denominator;

    if (cosine > 1.0) cosine = 1.0;
    if (cosine < -1.0) cosine = -1.0;

    return acos(cosine);
}

// Interpolation and comparison
vec3 vec3_lerp(vec3 a, vec3 b, double t) {
    return (vec3){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}

int vec3_equal(vec3 a, vec3 b) {
    return approx_equal(a.x, b.x) &&
           approx_equal(a.y, b.y) &&
           approx_equal(a.z, b.z);
}
