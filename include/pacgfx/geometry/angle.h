#ifndef PACGFX_GEOMETRY_ANGLE_H
#define PACGFX_GEOMETRY_ANGLE_H

/* Radians, counter-clockwise, 0 = +x axis. Poses never auto-normalize;
 * these helpers are for comparison and interpolation only. */

/* Conversion */
double angle_to_radians(double degrees);
double angle_to_degrees(double radians);

/* Normalization */
double angle_normalize(double radians);         /* result in [0, 2*pi) */
double angle_normalize_signed(double radians);  /* result in [-pi, pi) */

/* Interpolation along the shortest arc. Result is NOT normalized. */
double angle_lerp(double a, double b, double t);

/* Comparison */
int angle_equal(double a, double b);                       /* equal modulo 2*pi, within PG_EPSILON */
int angle_between(double angle, double start, double end); /* on the counter-clockwise arc start -> end, inclusive */

#endif
