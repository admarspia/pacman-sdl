#ifndef ANGLE_H
#define ANGLE_H

#include "approx.h"

// Conversion
float angle_to_radians(float degrees);
float angle_to_degrees(float radians);

// Normalization
float angle_normalize(float radians);
float angle_normalize_signed(float radians);

// Arithmetic
float angle_add(float a, float b);
float angle_sub(float a, float b);
float angle_lerp(float a, float b, float t);

// Comparison
int angle_equal(float a, float b);
int angle_between(float angle, float start, float end);

#endif
