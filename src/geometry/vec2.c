#include <pacgfx/geometry/vec2.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

vec2 vec2_add(vec2 a, vec2 b) {
    return (vec2){a.x + b.x, a.y + b.y};
}

vec2 vec2_sub(vec2 a, vec2 b) {
    return (vec2){a.x - b.x, a.y - b.y};
}

vec2 vec2_negate(vec2 a) {
    return (vec2){-a.x, -a.y};
}

vec2 vec2_scale(vec2 a, double scalar) {
    return (vec2){a.x * scalar, a.y * scalar};
}

vec2 vec2_divide(vec2 a, double scalar) {
    return (vec2){a.x / scalar, a.y / scalar};
}

double vec2_length_squared(vec2 a) {
    return a.x * a.x + a.y * a.y;
}

double vec2_length(vec2 a) {
    return sqrt(vec2_length_squared(a));
}

double vec2_distance(vec2 a, vec2 b) {
    return vec2_length(vec2_sub(a, b));
}

double vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

double vec2_cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

vec2 vec2_normalize(vec2 a) {
    double len = vec2_length(a);
    if (approx_equal(len, 0.0))
        return (vec2){0.0, 0.0};
    return vec2_divide(a, len);
}

vec2 vec2_perpendicular(vec2 a) {
    return (vec2){-a.y, a.x};
}

double vec2_angle(vec2 a, vec2 b) {
    double denominator = vec2_length(a) * vec2_length(b);
    if (approx_equal(denominator, 0.0))
        return 0.0;

    double cosine = vec2_dot(a, b) / denominator;

    /* Rounding can push the ratio slightly outside [-1, 1]. */
    if (cosine > 1.0)  cosine = 1.0;
    if (cosine < -1.0) cosine = -1.0;

    return acos(cosine);
}

vec2 vec2_lerp(vec2 a, vec2 b, double t) {
    return (vec2){
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t
    };
}

int vec2_equal(vec2 a, vec2 b) {
    return approx_equal(a.x, b.x) && approx_equal(a.y, b.y);
}
