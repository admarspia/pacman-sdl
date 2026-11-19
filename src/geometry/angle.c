#include <pacgfx/geometry/angle.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

double angle_to_radians(double degrees) {
    return degrees * (PG_PI / 180.0);
}

double angle_to_degrees(double radians) {
    return radians * (180.0 / PG_PI);
}

double angle_normalize(double radians) {
    double r = fmod(radians, PG_TWO_PI);   /* in (-2*pi, 2*pi) */

    if (r < 0.0)
        r += PG_TWO_PI;

    /* A tiny negative input (e.g. -1e-20) rounds to exactly 2*pi above,
     * which is outside [0, 2*pi). It is the same angle as 0. */
    if (r >= PG_TWO_PI)
        r = 0.0;

    return r;
}

double angle_normalize_signed(double radians) {
    double r = angle_normalize(radians);

    if (r >= PG_PI)
        r -= PG_TWO_PI;

    return r;
}

double angle_lerp(double a, double b, double t) {
    double diff = angle_normalize_signed(b - a);
    return a + diff * t;
}

int angle_equal(double a, double b) {
    return approx_equal(angle_normalize_signed(a - b), 0.0);
}

int angle_between(double angle, double start, double end) {
    angle = angle_normalize(angle);
    start = angle_normalize(start);
    end   = angle_normalize(end);

    if (start <= end)
        return angle >= start && angle <= end;

    return angle >= start || angle <= end;
}
