#include <pacgfx/geometry/mat3.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

mat3 mat3_identity(void) {
    return (mat3){{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    }};
}

mat3 mat3_multiply(mat3 a, mat3 b) {
    mat3 result;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            double sum = 0.0;
            for (int k = 0; k < 3; k++)
                sum += a.m[r][k] * b.m[k][c];
            result.m[r][c] = sum;
        }
    }

    return result;
}

mat3 mat3_transpose(mat3 a) {
    mat3 result;

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            result.m[c][r] = a.m[r][c];

    return result;
}

mat3 mat3_translation(double tx, double ty) {
    return (mat3){{
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    }};
}

mat3 mat3_rotation(double radians) {
    double c = cos(radians);
    double s = sin(radians);

    return (mat3){{
        {c,   -s,  0.0},
        {s,    c,  0.0},
        {0.0, 0.0, 1.0}
    }};
}

mat3 mat3_scaling(double sx, double sy) {
    return (mat3){{
        {sx,  0.0, 0.0},
        {0.0, sy,  0.0},
        {0.0, 0.0, 1.0}
    }};
}

vec2 mat3_transform_point(mat3 m, vec2 p) {
    return (vec2){
        m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2],
        m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2]
    };
}

vec2 mat3_transform_vector(mat3 m, vec2 v) {
    return (vec2){
        m.m[0][0] * v.x + m.m[0][1] * v.y,
        m.m[1][0] * v.x + m.m[1][1] * v.y
    };
}

int mat3_equal(mat3 a, mat3 b) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (!approx_equal(a.m[r][c], b.m[r][c]))
                return 0;

    return 1;
}


int mat3_inverse(mat3 m, mat3 *out) {
    double a = m.m[0][0], b = m.m[0][1], tx = m.m[0][2];
    double c = m.m[1][0], d = m.m[1][1], ty = m.m[1][2];

    double det = a * d - b * c;
    if (approx_equal(det, 0.0))
        return 0;

    double inv_det = 1.0 / det;

    /* inverse of the 2x2 linear part */
    double ia =  d * inv_det;
    double ib = -b * inv_det;
    double ic = -c * inv_det;
    double id =  a * inv_det;

    /* inverse translation = -(A^-1 * t) */
    *out = (mat3){{
        {ia, ib, -(ia * tx + ib * ty)},
        {ic, id, -(ic * tx + id * ty)},
        {0.0, 0.0, 1.0}
    }};
    return 1;
}
