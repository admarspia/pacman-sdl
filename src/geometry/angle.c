#include "../../include/pacgfx/geometry/angle.h"
#include <math.h>

#define PI 3.14159265358979323846
#define TWO_PI (2.0 * PI)

// Conversion
float angle_to_radians(float degrees) {
    return degrees * (PI / 180.0);
}

float angle_to_degrees(float radians) {
    return radians * (180.0 / PI);
}

// Normalization
float angle_normalize(float radians) {
    radians = fmodf(radians, TWO_PI);

    if (radians < 0.0f)
        radians += TWO_PI;

    return radians;
}

float angle_normalize_signed(float radians) {
    radians = angle_normalize(radians);

    if (radians >= PI)
        radians -= TWO_PI;

    return radians;
}

// Arithmetic
float angle_add(float a, float b) {
    return angle_normalize(a + b);
}

float angle_sub(float a, float b) {
    return angle_normalize(a - b);
}

float angle_lerp(float a, float b, float t) {
    float diff = angle_normalize_signed(b - a);

    return angle_normalize(a + diff * t);
}

// Comparison
int angle_equal(float a, float b) {
    return approx_equal(angle_normalize_signed(a - b), 0.0f);
}

int angle_between(float angle, float start, float end) {
    angle = angle_normalize(angle);
    start = angle_normalize(start);
    end = angle_normalize(end);

    if (start <= end)
        return angle >= start && angle <= end;

    return angle >= start || angle <= end;
}
