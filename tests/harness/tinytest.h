#ifndef TINYTEST_H
#define TINYTEST_H

#include <stdio.h>
#include <math.h>
#include <pacgfx/geometry/approx.h>

/* One test executable = one translation unit, so static counters are fine. */
static int tt_checks   = 0;
static int tt_failures = 0;

#define ASSERT(cond) \
    do { \
        tt_checks++; \
        if (!(cond)) { \
            tt_failures++; \
            printf("    FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        } \
    } while (0)

/* Compares doubles through approx_equal (PG_EPSILON). */
#define ASSERT_APPROX(a, b) \
    do { \
        double tt_a = (a); \
        double tt_b = (b); \
        tt_checks++; \
        if (!approx_equal(tt_a, tt_b)) { \
            tt_failures++; \
            printf("    FAIL %s:%d: %s ~= %s  (%.17g vs %.17g)\n", \
                   __FILE__, __LINE__, #a, #b, tt_a, tt_b); \
        } \
    } while (0)

/* Needs vec2.h included by the test file. */
#define ASSERT_VEC2(a, b) \
    do { \
        vec2 tt_va = (a); \
        vec2 tt_vb = (b); \
        tt_checks++; \
        if (!vec2_equal(tt_va, tt_vb)) { \
            tt_failures++; \
            printf("    FAIL %s:%d: %s ~= %s  ((%.17g, %.17g) vs (%.17g, %.17g))\n", \
                   __FILE__, __LINE__, #a, #b, tt_va.x, tt_va.y, tt_vb.x, tt_vb.y); \
        } \
    } while (0)

/* Needs mat3.h included by the test file. */
#define ASSERT_MAT3(a, b) \
    do { \
        mat3 tt_ma = (a); \
        mat3 tt_mb = (b); \
        tt_checks++; \
        if (!mat3_equal(tt_ma, tt_mb)) { \
            tt_failures++; \
            printf("    FAIL %s:%d: %s ~= %s\n", __FILE__, __LINE__, #a, #b); \
        } \
    } while (0)

#define TT_RUN(fn) \
    do { \
        int tt_before = tt_failures; \
        fn(); \
        printf("%s  %s\n", tt_failures == tt_before ? "ok  " : "FAIL", #fn); \
    } while (0)

static inline int tt_report(void) {
    printf("\n%d checks, %d failed\n", tt_checks, tt_failures);
    return tt_failures ? 1 : 0;
}

#endif
