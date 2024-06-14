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

START_TEST(matrix_test_1) {

}

// ============================================================================

Suite *matrix_test(void) {
  Suite *viewer = suite_create("\nmatrix tests\n");

  TCase *tc_matrix_test = tcase_create("matrix test");
  tcase_add_test(tc_matrix_test, matrix_test_1);
  suite_add_tcase(viewer, tc_matrix_test);

  return viewer;
}