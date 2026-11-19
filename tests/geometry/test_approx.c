#include "tinytest.h"
#include <pacgfx/geometry/approx.h>

static void test_approx_epsilon_boundaries(void) {
    ASSERT(approx_equal(1.0, 1.0));
    ASSERT(approx_equal(1.0, 1.0 + 5e-10));   /* inside epsilon  */
    ASSERT(!approx_equal(1.0, 1.0 + 5e-9));   /* outside epsilon: fails if you still use float */
    ASSERT(!approx_equal(0.0, 1e-8));
}

static void test_approx_symmetric_and_sign(void) {
    ASSERT(approx_equal(2.0, 2.0 + 5e-10) == approx_equal(2.0 + 5e-10, 2.0));
    ASSERT(approx_equal(0.0, -0.0));
    ASSERT(approx_equal(-1.0, -1.0 - 5e-10));
    ASSERT(!approx_equal(1.0, -1.0));
}

static void test_approx_nan_never_equal(void) {
    double nan = (double)NAN;
    ASSERT(!approx_equal(nan, nan));
    ASSERT(!approx_equal(nan, 0.0));
}

static void test_approx_constants(void) {
    ASSERT(PG_EPSILON == 1e-9);
    ASSERT(approx_equal(PG_TWO_PI, 2.0 * PG_PI));
    ASSERT(approx_equal(PG_PI, 3.141592653589793));
}

int main(void) {
    TT_RUN(test_approx_epsilon_boundaries);
    TT_RUN(test_approx_symmetric_and_sign);
    TT_RUN(test_approx_nan_never_equal);
    TT_RUN(test_approx_constants);
    return tt_report();
}
