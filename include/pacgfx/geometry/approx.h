#ifndef PACGFX_GEOMETRY_APPROX_H
#define PACGFX_GEOMETRY_APPROX_H

/* Defined once, here. Used only through the approx helpers and in tests. */
#define PG_EPSILON 1e-9
#define PG_PI      3.14159265358979323846
#define PG_TWO_PI  (2.0 * PG_PI)

/* |a - b| <= PG_EPSILON. NaN never compares equal. */
int approx_equal(double a, double b);

#endif
