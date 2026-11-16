#ifndef VEC2
#define VEC2
#include "./approx.h"

typedef struct {
  double x;
  double y;
}vec2;

vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_negate(vec2 a);
double vec2_length(vec2 a);
double vec2_dot(vec2 a, vec2 b);
double vec2_cross(vec2 a, vec2 b);
int vec2_equal(vec2 a, vec2 b);
vec2 vec2_scale(vec2 a, double k);
vec2 vec2_devide(vec2 a, double k);
vec2 vec2_normalize(vec2 a);
vec2 vec2_destance(vec2 a, vec2 b);
double vec2_angle(vec2 a, vec2 b);
vec2 vec2_perpendicular(vec2 a);
//Why do we need perpendicular vectors in computer graphics?
// They are particularly useful in:
// 1. Collision detection: Determining surface normals and contact directions.
// 2. Lighting: Calculating how light interacts with a surface.
// 3. Geometry: Finding perpendicular directions to edges.
// 4. Physics: Calculating forces and reflections
//
vec2 vec2_lerp(vec2 a, vec2 b, double t);

// Why do we need Lerp in graphics?
// Imagine creating a game where a character moves from one position to another.
//
// Instead of instantly moving the character, you calculate intermediate positions.
//
// For example:
// - Frame 1: position A.
// - Frame 2: 25% toward B.
// - Frame 3: 50% toward B.
// - Frame 4: 75% toward B.
// - Frame 5: position B.


#endif

