/* Test the vmulxs_lane_f32 AArch64 SIMD intrinsic.  */

/* { dg-do run } */
/* { dg-options "-save-temps -O3" } */

#include "arm_neon.h"

extern void abort (void);

float32_t __attribute__ ((noinline))
test_vmulxs_lane_f32_lane0 (float32_t vec1_1, float32x2_t vec1_2)
{
  return vmulxs_lane_f32 (vec1_1, vec1_2, 0);
}

float32_t __attribute__ ((noinline))
test_vmulxs_lane_f32_lane1 (float32_t vec1_1, float32x2_t vec1_2)
{
  return vmulxs_lane_f32 (vec1_1, vec1_2, 1);
}

#define PASS_ARRAY(...) {__VA_ARGS__}

#define SETUP_VEC(V1_D, V2_D, EXP1, EXP2, I)				\
  void set_and_test_case##I ()						\
  {									\
    float32_t vec1 = V1_D;						\
    float32_t vec2_data[] =  V2_D;					\
    float32x2_t vec2 = vld1_f32 (vec2_data);				\
    float32_t expected_lane0 = EXP1;					\
    float32_t expected_lane1 = EXP2;					\
    float32_t actual_lane0 = test_vmulxs_lane_f32_lane0 (vec1, vec2);	\
    if (actual_lane0 != expected_lane0)					\
      abort ();								\
    float32_t actual_lane1 = test_vmulxs_lane_f32_lane1 (vec1, vec2);	\
    if (actual_lane1 != expected_lane1)					\
      abort ();								\
  }									\

float32_t v1 = 3.14159265359;
float32_t v2 = 1.383894;

float32_t v4 = 0.0;
float32_t v5 = -0.0;
float32_t v6 = __builtin_huge_valf ();
float32_t v7 = -__builtin_huge_valf ();

SETUP_VEC (v1, PASS_ARRAY (v1, v2), v1*v1, v1*v2, 1)
SETUP_VEC (v4, PASS_ARRAY (v6, v7), 2.0, -2.0, 2)
SETUP_VEC (v5, PASS_ARRAY (v6, v7), -2.0, 2.0, 3)

int
main (void)
{
  set_and_test_case1 ();
  set_and_test_case2 ();
  set_and_test_case3 ();
  return 0;
}
/* { dg-final { scan-assembler-times "fmulx\[ \t\]+\[sS\]\[0-9\]+, ?\[sS\]\[0-9\]+, ?\[vV\]\[0-9\]+\.\[sS\]\\\[0\\\]\n" 1 } } */
/* { dg-final { scan-assembler-times "fmulx\[ \t\]+\[sS\]\[0-9\]+, ?\[sS\]\[0-9\]+, ?\[vV\]\[0-9\]+\.\[sS\]\\\[1\\\]\n" 1 } } */
