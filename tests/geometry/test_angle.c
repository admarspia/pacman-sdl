#include "tinytest.h"
#include <pacgfx/geometry/angle.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

#define DEG(x) angle_to_radians(x)

static void test_angle_conversion(void) {
    ASSERT_APPROX(angle_to_radians(180.0), PG_PI);
    ASSERT_APPROX(angle_to_radians(90.0), PG_PI / 2.0);
    ASSERT_APPROX(angle_to_degrees(PG_PI), 180.0);
    ASSERT_APPROX(angle_to_degrees(angle_to_radians(37.0)), 37.0);
}

static void test_angle_normalize_range(void) {
    ASSERT_APPROX(angle_normalize(0.0), 0.0);
    ASSERT_APPROX(angle_normalize(PG_TWO_PI), 0.0);
    ASSERT_APPROX(angle_normalize(-PG_PI / 2.0), 3.0 * PG_PI / 2.0);
    ASSERT_APPROX(angle_normalize(5.0 * PG_PI), PG_PI);
    ASSERT_APPROX(angle_normalize(-5.0 * PG_PI), PG_PI);
}

static void test_angle_normalize_wraparound_edges(void) {
    double tiny_neg = angle_normalize(-1e-20);
    ASSERT(tiny_neg >= 0.0);
    ASSERT(tiny_neg < PG_TWO_PI);              /* must never return exactly 2*pi */

    double just_below = angle_normalize(PG_TWO_PI - 1e-12);
    ASSERT(just_below < PG_TWO_PI);
    ASSERT(just_below >= 0.0);
}

static void test_angle_normalize_signed_range(void) {
    ASSERT_APPROX(angle_normalize_signed(0.0), 0.0);
    ASSERT_APPROX(angle_normalize_signed(-PG_PI / 2.0), -PG_PI / 2.0);
    ASSERT_APPROX(angle_normalize_signed(3.0 * PG_PI / 2.0), -PG_PI / 2.0);
    ASSERT_APPROX(angle_normalize_signed(PG_PI), -PG_PI);   /* range is [-pi, pi) */
}

static void test_angle_equal_modulo_two_pi(void) {
    ASSERT(angle_equal(0.0, PG_TWO_PI));
    ASSERT(angle_equal(-PG_PI / 2.0, 3.0 * PG_PI / 2.0));
    ASSERT(angle_equal(PG_TWO_PI - 1e-12, 0.0));            /* the wrap-around trap */
    ASSERT(angle_equal(0.0, 100.0 * PG_TWO_PI));
    ASSERT(!angle_equal(0.0, 1e-3));
    ASSERT(!angle_equal(0.0, PG_PI));
    ASSERT(!angle_equal(1.0, 1.0 + 1e-3));
}

static void test_angle_lerp_shortest_arc(void) {
    ASSERT_APPROX(angle_lerp(0.0, PG_PI / 2.0, 0.5), PG_PI / 4.0);
    ASSERT(angle_equal(angle_lerp(DEG(350.0), DEG(10.0), 0.5), 0.0));   /* crosses 0, not 180 */
    ASSERT(angle_equal(angle_lerp(DEG(10.0), DEG(350.0), 0.5), 0.0));
    ASSERT(angle_equal(angle_lerp(DEG(30.0), DEG(100.0), 0.0), DEG(30.0)));
    ASSERT(angle_equal(angle_lerp(DEG(30.0), DEG(100.0), 1.0), DEG(100.0)));
}

static void test_angle_between(void) {
    ASSERT(angle_between(DEG(45.0), DEG(0.0), DEG(90.0)));
    ASSERT(!angle_between(DEG(180.0), DEG(0.0), DEG(90.0)));
    ASSERT(angle_between(DEG(0.0), DEG(0.0), DEG(90.0)));      /* inclusive */
    ASSERT(angle_between(DEG(90.0), DEG(0.0), DEG(90.0)));
    /* arc that wraps through 0 */
    ASSERT(angle_between(DEG(0.0), DEG(350.0), DEG(10.0)));
    ASSERT(angle_between(DEG(355.0), DEG(350.0), DEG(10.0)));
    ASSERT(angle_between(DEG(5.0), DEG(350.0), DEG(10.0)));
    ASSERT(!angle_between(DEG(180.0), DEG(350.0), DEG(10.0)));
}

int main(void) {
    TT_RUN(test_angle_conversion);
    TT_RUN(test_angle_normalize_range);
    TT_RUN(test_angle_normalize_wraparound_edges);
    TT_RUN(test_angle_normalize_signed_range);
    TT_RUN(test_angle_equal_modulo_two_pi);
    TT_RUN(test_angle_lerp_shortest_arc);
    TT_RUN(test_angle_between);
    return tt_report();
}
