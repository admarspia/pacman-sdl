#include "tinytest.h"
#include <pacgfx/geometry/vec2.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

static void test_vec2_arithmetic(void) {
    vec2 a = {1.0, 2.0};
    vec2 b = {3.0, -4.0};
    ASSERT_VEC2(vec2_add(a, b), ((vec2){4.0, -2.0}));
    ASSERT_VEC2(vec2_sub(a, b), ((vec2){-2.0, 6.0}));
    ASSERT_VEC2(vec2_negate(a), ((vec2){-1.0, -2.0}));
    ASSERT_VEC2(vec2_scale(a, 3.0), ((vec2){3.0, 6.0}));
    ASSERT_VEC2(vec2_divide(b, 2.0), ((vec2){1.5, -2.0}));
    ASSERT_VEC2(vec2_add(a, vec2_negate(a)), ((vec2){0.0, 0.0}));
}

static void test_vec2_length_and_distance(void) {
    vec2 v = {3.0, 4.0};
    ASSERT_APPROX(vec2_length(v), 5.0);
    ASSERT_APPROX(vec2_length_squared(v), 25.0);
    ASSERT_APPROX(vec2_distance((vec2){1.0, 1.0}, (vec2){4.0, 5.0}), 5.0);
    ASSERT_APPROX(vec2_distance(v, v), 0.0);
}

static void test_vec2_dot_and_cross(void) {
    vec2 x = {1.0, 0.0};
    vec2 y = {0.0, 1.0};
    ASSERT_APPROX(vec2_dot(x, y), 0.0);
    ASSERT_APPROX(vec2_dot(x, x), 1.0);
    ASSERT_APPROX(vec2_cross(x, y), 1.0);     /* y is counter-clockwise from x: positive */
    ASSERT_APPROX(vec2_cross(y, x), -1.0);    /* anti-commutative */
    ASSERT_APPROX(vec2_cross(x, x), 0.0);
    /* |a x b| = |a||b| sin(theta) and a.b = |a||b| cos(theta) */
    vec2 a = {2.0, 1.0};
    vec2 b = {-1.0, 3.0};
    double lhs = vec2_dot(a, b) * vec2_dot(a, b) + vec2_cross(a, b) * vec2_cross(a, b);
    double rhs = vec2_length_squared(a) * vec2_length_squared(b);
    ASSERT_APPROX(lhs, rhs);
}

static void test_vec2_normalize(void) {
    ASSERT_VEC2(vec2_normalize((vec2){3.0, 4.0}), ((vec2){0.6, 0.8}));
    ASSERT_APPROX(vec2_length(vec2_normalize((vec2){-7.0, 2.5})), 1.0);
    ASSERT_VEC2(vec2_normalize((vec2){0.0, 0.0}), ((vec2){0.0, 0.0}));
    ASSERT_VEC2(vec2_normalize((vec2){1e-12, 0.0}), ((vec2){0.0, 0.0}));  /* degenerate policy */
}

static void test_vec2_perpendicular(void) {
    ASSERT_VEC2(vec2_perpendicular((vec2){1.0, 0.0}), ((vec2){0.0, 1.0}));   /* 90 degrees CCW */
    ASSERT_VEC2(vec2_perpendicular((vec2){0.0, 1.0}), ((vec2){-1.0, 0.0}));
    vec2 v = {2.5, -1.5};
    ASSERT_APPROX(vec2_dot(v, vec2_perpendicular(v)), 0.0);
    ASSERT_APPROX(vec2_length(vec2_perpendicular(v)), vec2_length(v));
}

static void test_vec2_angle(void) {
    ASSERT_APPROX(vec2_angle((vec2){1.0, 0.0}, (vec2){0.0, 1.0}), PG_PI / 2.0);
    ASSERT_APPROX(vec2_angle((vec2){1.0, 0.0}, (vec2){1.0, 1.0}), PG_PI / 4.0);
    ASSERT_APPROX(vec2_angle((vec2){1.0, 0.0}, (vec2){0.0, 0.0}), 0.0);      /* degenerate policy */

    /* Rounding can push cos slightly past 1; the clamp must prevent NaN.
     * Tolerance is loose on purpose: acos is ill-conditioned near 0 and pi. */
    vec2 v = {0.1, 0.3};
    double same = vec2_angle(v, v);
    ASSERT(same == same);                      /* not NaN */
    ASSERT(same < 1e-6);
    double opposite = vec2_angle(v, vec2_negate(v));
    ASSERT(opposite == opposite);
    ASSERT(fabs(opposite - PG_PI) < 1e-6);
}

static void test_vec2_lerp_and_equal(void) {
    vec2 a = {0.0, 0.0};
    vec2 b = {10.0, -4.0};
    ASSERT_VEC2(vec2_lerp(a, b, 0.0), a);
    ASSERT_VEC2(vec2_lerp(a, b, 1.0), b);
    ASSERT_VEC2(vec2_lerp(a, b, 0.5), ((vec2){5.0, -2.0}));
    ASSERT(vec2_equal((vec2){1.0, 2.0}, (vec2){1.0 + 5e-10, 2.0}));
    ASSERT(!vec2_equal((vec2){1.0, 2.0}, (vec2){1.0 + 5e-9, 2.0}));
    ASSERT(!vec2_equal((vec2){1.0, 2.0}, (vec2){1.0, 2.1}));
}

int main(void) {
    TT_RUN(test_vec2_arithmetic);
    TT_RUN(test_vec2_length_and_distance);
    TT_RUN(test_vec2_dot_and_cross);
    TT_RUN(test_vec2_normalize);
    TT_RUN(test_vec2_perpendicular);
    TT_RUN(test_vec2_angle);
    TT_RUN(test_vec2_lerp_and_equal);
    return tt_report();
}
