/**
 * @file matrix_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test matrix module functions
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/matrix_test.h"

// ============================================================================

START_TEST(test_mx_mult_vector_1) {
  float vertexes[] = {1.0f, 2.0f, 3.0f};
  float vector[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  float data[V_CNT] = {0.0f};
  float expected[] = {1.0f, 2.0f, 3.0f};

  mx_mult_vector(data, vertexes, vector, 1);

  for (int i = 0; i < V_CNT; i++) {
    ck_assert_float_eq_tol(data[i], expected[i], 1e-6);
  }
}
END_TEST

START_TEST(test_mx_mult_vector_2) {
  float vertexes[] = {4, 5, 2};
  float vector[] = {5, 2, 4, 2, 2, 3, 1, 5, 2, 4, 6, 2, 2, 6, 3, 1};
  float data[V_CNT] = {0};
  float expected[] = {40.0f, 30.0f, 42.0f};

  mx_mult_vector(data, vertexes, vector, 1);

  for (int i = 0; i < V_CNT; i++) {
    ck_assert_float_eq_tol(data[i], expected[i], 1e-6);
  }
}
END_TEST

START_TEST(test_mx_mult_4x4_1) {
  float matrix1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  float matrix2[] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  float expected[] = {80,  70,  60,  50,  240, 214, 188, 162,
                      400, 358, 316, 274, 560, 502, 444, 386};

  float result[TR_MX_SIZE * TR_MX_SIZE] = {0};
  mx_copy(result, matrix1);

  mx_mult_4x4(result, matrix2);

  for (int i = 0; i < TR_MX_SIZE * TR_MX_SIZE; i++) {
    ck_assert_float_eq_tol(result[i], expected[i], 1e-6);
  }
}
END_TEST

START_TEST(test_mx_mult_4x4_2) {
  float matrix1[] = {1.5,    2.25,   3.75,  4.125,  5.5,    6.625,
                     7.75,   8.875,  9.25,  10.125, 11.375, 12.5,
                     13.875, 14.625, 15.75, 16.875};

  float matrix2[] = {16.875, 15.5, 14.25, 13.125, 12.875, 11.5,  10.25, 9.125,
                     8.875,  7.75, 6.5,   5.375,  4.25,   3.125, 2.875, 1.5};

  float expected[] = {105.09375,  91.078125,  80.671875,  66.5625,
                      284.609375, 249.234375, 222.171875, 187.609375,
                      440.53125,  387.03125,  345.46875,  293.6875,
                      633.9375,   558.046875, 498.515625, 425.53125};

  float result[TR_MX_SIZE * TR_MX_SIZE] = {0};
  mx_copy(result, matrix1);

  mx_mult_4x4(result, matrix2);

  for (int i = 0; i < TR_MX_SIZE * TR_MX_SIZE; i++) {
    ck_assert_float_eq_tol(result[i], expected[i], 1e-6);
  }
}
END_TEST

// ============================================================================

Suite *matrix_test(void) {
  Suite *viewer = suite_create("\nmatrix tests\n");

  TCase *tc_matrix_test = tcase_create("matrix test");
  tcase_add_test(tc_matrix_test, test_mx_mult_vector_1);
  tcase_add_test(tc_matrix_test, test_mx_mult_vector_2);
  tcase_add_test(tc_matrix_test, test_mx_mult_4x4_1);
  tcase_add_test(tc_matrix_test, test_mx_mult_4x4_2);
  suite_add_tcase(viewer, tc_matrix_test);

  return viewer;
}