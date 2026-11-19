#include <pacgfx/geometry/approx.h>
#include <math.h>

int approx_equal(double a, double b) {
    return fabs(a - b) <= PG_EPSILON;
}
