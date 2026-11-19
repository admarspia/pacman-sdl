#include "tinytest.h"
#include <pacgfx/geometry/mat3.h>
#include <pacgfx/geometry/vec2.h>
#include <pacgfx/geometry/approx.h>
#include <math.h>

/* Layout facts the rest of the project relies on. */
static void test_mat3_layout(void) {
    ASSERT(sizeof(mat3) == 9 * sizeof(double));
    mat3 r = mat3_rotation(0.3);
    ASSERT_APPROX(r.m[0][0], cos(0.3));
    ASSERT_APPROX(r.m[0][1], -sin(0.3));
    ASSERT_APPROX(r.m[1][0], sin(0.3));
    ASSERT_APPROX(r.m[1][1], cos(0.3));
    ASSERT_APPROX(r.m[2][2], 1.0);
    mat3 t = mat3_translation(5.0, 7.0);
    ASSERT_APPROX(t.m[0][2], 5.0);
    ASSERT_APPROX(t.m[1][2], 7.0);
    ASSERT_APPROX(t.m[2][0], 0.0);
    ASSERT_APPROX(t.m[2][1], 0.0);
    ASSERT_APPROX(t.m[2][2], 1.0);
}

/* 3.1 property 1 */
static void test_mat3_3_1_p1_identity_and_associativity(void) {
    mat3 i = mat3_identity();
    mat3 a = mat3_translation(1.0, 2.0);
    mat3 b = mat3_rotation(0.7);
    mat3 c = mat3_scaling(2.0, 3.0);
    ASSERT_MAT3(mat3_multiply(i, b), b);
    ASSERT_MAT3(mat3_multiply(b, i), b);
    ASSERT_MAT3(mat3_multiply(mat3_multiply(a, b), c),
                mat3_multiply(a, mat3_multiply(b, c)));
}

/* 3.1 property 2 */
static void test_mat3_3_1_p2_rotation_composition(void) {
    double th = 0.4;
    double ph = 1.1;
    ASSERT_MAT3(mat3_multiply(mat3_rotation(th), mat3_rotation(ph)), mat3_rotation(th + ph));
    ASSERT_MAT3(mat3_multiply(mat3_rotation(th), mat3_rotation(-th)), mat3_identity());
}

/* 3.1 property 3 */
static void test_mat3_3_1_p3_translations_add(void) {
    ASSERT_MAT3(mat3_multiply(mat3_translation(1.0, 2.0), mat3_translation(-4.0, 0.5)),
                mat3_translation(-3.0, 2.5));
}

/* 3.1 property 4: rotation and translation do not commute */
static void test_mat3_3_1_p4_rotation_translation_do_not_commute(void) {
    mat3 r = mat3_rotation(PG_PI / 2.0);
    mat3 t = mat3_translation(5.0, 0.0);
    ASSERT(!mat3_equal(mat3_multiply(r, t), mat3_multiply(t, r)));
}

/* "A * B applies B first" */
static void test_mat3_compose_order(void) {
    vec2 p = {1.0, 0.0};
    mat3 r = mat3_rotation(PG_PI / 2.0);
    mat3 t = mat3_translation(5.0, 0.0);
    /* rotate first -> (0,1), then translate -> (5,1) */
    ASSERT_VEC2(mat3_transform_point(mat3_multiply(t, r), p), ((vec2){5.0, 1.0}));
    /* translate first -> (6,0), then rotate -> (0,6) */
    ASSERT_VEC2(mat3_transform_point(mat3_multiply(r, t), p), ((vec2){0.0, 6.0}));
}

/* 3.1 property 5 */
static void test_mat3_3_1_p5_rotation_preserves_length(void) {
    vec2 v = {3.0, 4.0};
    for (int i = 0; i < 16; i++) {
        double th = -8.0 + 1.0 * (double)i;
        ASSERT_APPROX(vec2_length(mat3_transform_vector(mat3_rotation(th), v)), 5.0);
    }
}

/* 3.1 property 6: this is why EPSILON exists */
static void test_mat3_3_1_p6_rotate_90_needs_tolerance(void) {
    vec2 p = mat3_transform_point(mat3_rotation(PG_PI / 2.0), (vec2){1.0, 0.0});
    ASSERT_VEC2(p, ((vec2){0.0, 1.0}));
    ASSERT(p.x != 0.0);                        /* about 6e-17, not exactly zero */
    ASSERT(fabs(p.x) < 1e-15);
}

static void test_mat3_point_vs_vector(void) {
    mat3 t = mat3_translation(5.0, -2.0);
    ASSERT_VEC2(mat3_transform_point(t, (vec2){1.0, 1.0}), ((vec2){6.0, -1.0}));
    ASSERT_VEC2(mat3_transform_vector(t, (vec2){1.0, 1.0}), ((vec2){1.0, 1.0}));
    mat3 s = mat3_scaling(2.0, 3.0);
    ASSERT_VEC2(mat3_transform_point(s, (vec2){1.0, 1.0}), ((vec2){2.0, 3.0}));
    ASSERT_VEC2(mat3_transform_vector(s, (vec2){1.0, 1.0}), ((vec2){2.0, 3.0}));
}

static void test_mat3_transpose(void) {
    mat3 r = mat3_rotation(0.9);
    ASSERT_MAT3(mat3_transpose(r), mat3_rotation(-0.9));                        /* inverse of a rotation */
    ASSERT_MAT3(mat3_multiply(mat3_transpose(r), r), mat3_identity());
    ASSERT_MAT3(mat3_transpose(mat3_transpose(r)), r);
    mat3 t = mat3_transpose(mat3_translation(5.0, 7.0));
    ASSERT_APPROX(t.m[2][0], 5.0);
    ASSERT_APPROX(t.m[2][1], 7.0);
    ASSERT_APPROX(t.m[0][2], 0.0);
}

static void test_mat3_equal(void) {
    ASSERT(mat3_equal(mat3_identity(), mat3_identity()));
    ASSERT(!mat3_equal(mat3_identity(), mat3_translation(1e-6, 0.0)));
    mat3 almost = mat3_identity();
    almost.m[1][2] = 5e-10;                    /* within epsilon */
    ASSERT(mat3_equal(mat3_identity(), almost));
    almost.m[1][2] = 5e-9;                     /* outside epsilon */
    ASSERT(!mat3_equal(mat3_identity(), almost));
}

/* Model matrix T(pos) * R(angle) reproduces the spec fixture: (1,1) at (5,3), 90 degrees -> (4,4) */
static void test_mat3_model_matrix_fixture(void) {
    mat3 model = mat3_multiply(mat3_translation(5.0, 3.0), mat3_rotation(PG_PI / 2.0));
    ASSERT_VEC2(mat3_transform_point(model, (vec2){ 1.0,  1.0}), ((vec2){4.0, 4.0}));
    ASSERT_VEC2(mat3_transform_point(model, (vec2){-1.0,  1.0}), ((vec2){4.0, 2.0}));
    ASSERT_VEC2(mat3_transform_point(model, (vec2){-1.0, -1.0}), ((vec2){6.0, 2.0}));
    ASSERT_VEC2(mat3_transform_point(model, (vec2){ 1.0, -1.0}), ((vec2){6.0, 4.0}));
}

int main(void) {
    TT_RUN(test_mat3_layout);
    TT_RUN(test_mat3_3_1_p1_identity_and_associativity);
    TT_RUN(test_mat3_3_1_p2_rotation_composition);
    TT_RUN(test_mat3_3_1_p3_translations_add);
    TT_RUN(test_mat3_3_1_p4_rotation_translation_do_not_commute);
    TT_RUN(test_mat3_compose_order);
    TT_RUN(test_mat3_3_1_p5_rotation_preserves_length);
    TT_RUN(test_mat3_3_1_p6_rotate_90_needs_tolerance);
    TT_RUN(test_mat3_point_vs_vector);
    TT_RUN(test_mat3_transpose);
    TT_RUN(test_mat3_equal);
    TT_RUN(test_mat3_model_matrix_fixture);
    return tt_report();
}


static void test_mat3_inverse_basic(void) {
    mat3 inv;
    ASSERT(mat3_inverse(mat3_translation(5.0, 7.0), &inv));
    ASSERT_MAT3(inv, mat3_translation(-5.0, -7.0));

    ASSERT(mat3_inverse(mat3_rotation(0.9), &inv));
    ASSERT_MAT3(inv, mat3_transpose(mat3_rotation(0.9)));

    ASSERT(mat3_inverse(mat3_scaling(2.0, -4.0), &inv));
    ASSERT_MAT3(inv, mat3_scaling(0.5, -0.25));
}

static void test_mat3_inverse_composite(void) {
    mat3 m = mat3_multiply(mat3_translation(3.0, -2.0),
             mat3_multiply(mat3_rotation(0.7), mat3_scaling(2.0, 3.0)));
    mat3 inv;
    ASSERT(mat3_inverse(m, &inv));
    ASSERT_MAT3(mat3_multiply(m, inv), mat3_identity());
    ASSERT_MAT3(mat3_multiply(inv, m), mat3_identity());

    vec2 p = {1.5, -2.5};
    ASSERT_VEC2(mat3_transform_point(inv, mat3_transform_point(m, p)), p);
}

static void test_mat3_inverse_of_product_reverses_order(void) {
    mat3 t = mat3_translation(4.0, 1.0);
    mat3 r = mat3_rotation(1.2);
    mat3 inv_t, inv_r, inv_tr;
    ASSERT(mat3_inverse(t, &inv_t));
    ASSERT(mat3_inverse(r, &inv_r));
    ASSERT(mat3_inverse(mat3_multiply(t, r), &inv_tr));
    ASSERT_MAT3(inv_tr, mat3_multiply(inv_r, inv_t));
}

static void test_mat3_inverse_singular(void) {
    mat3 inv = mat3_translation(9.0, 9.0);   /* sentinel */
    ASSERT(!mat3_inverse(mat3_scaling(0.0, 1.0), &inv));
    ASSERT_MAT3(inv, mat3_translation(9.0, 9.0));   /* untouched on failure */
}
