/**
 * @file parse_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test parse module functions
 * @version 1.0
 * @date 2024-06-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/parse_test.h"

// ============================================================================

START_TEST(parse_test_1) {
  char *path = "./../data-samples/cube.obj";
  data_t data;
  parse(path, &data);
  float v_begin[] = {-1.0f, -1.0f, 2.0f};
  float v_end[] = {1.0f, -1.0f, 0.0f};
  int f_begin[] = {0, 1, 1, 2, 2, 0};
  int f_end[] = {4, 0, 0, 2, 2, 4};

  ck_assert_int_eq(data.vertex_count, 8);
  ck_assert_int_eq(data.facet_count, 12);
  for (int i = 0; i < V_CNT; i++) {
    ck_assert_float_eq_tol(data.vertexes.matrix[i], v_begin[i], 1.0e-6);
    ck_assert_float_eq_tol(
        data.vertexes.matrix[data.vertex_count * V_CNT - V_CNT + i], v_end[i],
        1.0e-6);
  }
  for (int i = 0; i < 6; i++) {
    ck_assert_int_eq(data.facets[i], f_begin[i]);
    ck_assert_int_eq(data.facets[data.full_cnt - 6 + i], f_end[i]);
  }

  remove_data(&data);
}

START_TEST(parse_test_2) {
  char *path = "./../data-samples/cottage.obj";
  data_t data;
  parse(path, &data);
  float v_begin[] = {-63.196327f, 0.077648f, 63.196327f};
  float v_end[] = {-18.588541f, 14.525741f, 1.214437f};
  int f_begin[] = {0, 1, 1, 3, 3, 2, 2, 0};
  int f_end[] = {346, 343, 343, 349, 349, 352, 352, 346};

  ck_assert_int_eq(data.vertex_count, 353);
  ck_assert_int_eq(data.facet_count, 259);
  for (int i = 0; i < V_CNT; i++) {
    ck_assert_float_eq_tol(data.vertexes.matrix[i], v_begin[i], 1.0e-6);
    ck_assert_float_eq_tol(
        data.vertexes.matrix[data.vertex_count * V_CNT - V_CNT + i], v_end[i],
        1.0e-6);
  }
  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(data.facets[i], f_begin[i]);
    ck_assert_int_eq(data.facets[data.full_cnt - 8 + i], f_end[i]);
  }

  remove_data(&data);
}

START_TEST(parse_test_3) {
  char *path = "./../data-samples/bootle.obj";
  data_t data;
  parse(path, &data);
  float v_begin[] = {0.185778f, 0.464630f, 0.071157f};
  float v_end[] = {0.000000f, 0.371327f, 0.543379f};
  int f_begin[] = {1, 0, 0, 1};
  int f_end[] = {1530, 1535, 1535, 1530};

  ck_assert_int_eq(data.vertex_count, 26105);
  ck_assert_int_eq(data.facet_count, 65480);
  for (int i = 0; i < V_CNT; i++) {
    ck_assert_float_eq_tol(data.vertexes.matrix[i], v_begin[i], 1.0e-6);
    ck_assert_float_eq_tol(
        data.vertexes.matrix[data.vertex_count * V_CNT - V_CNT + i], v_end[i],
        1.0e-6);
  }
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(data.facets[i], f_begin[i]);
    ck_assert_int_eq(data.facets[data.full_cnt - 4 + i], f_end[i]);
  }

  remove_data(&data);
}

START_TEST(parse_no_file_1) {
  data_t data;

  ck_assert_int_eq(parse(NULL, &data), false);
  remove_data(&data);
}

START_TEST(parse_no_file_2) {
  char *path = "./../data-samples/not_exist.obj";
  data_t data;

  ck_assert_int_eq(parse(path, &data), true);
}

START_TEST(parse_invalid_1) {
  char *path = "./../data-samples/invalid.obj";
  data_t data;

  ck_assert_int_eq(parse(path, &data), true);
  remove_data(&data);
}

START_TEST(parse_invalid_2) {
  char *path = "./../data-samples/empty.obj";
  data_t data;

  ck_assert_int_eq(parse(path, &data), true);
  remove_data(&data);
}

START_TEST(copy_data_test) {
  char *path = "./../data-samples/cube.obj";
  data_t data;
  parse(path, &data);
  data_t copy = copy_data(&data);

  for (int i = 0; i < copy.vertex_count * V_CNT; i++) {
    ck_assert_float_eq(data.vertexes.matrix[i], copy.vertexes.matrix[i]);
  }

  remove_data(&data);
  remove_data(&copy);
}

// ============================================================================

Suite *parse_test(void) {
  Suite *viewer = suite_create("\nparse tests\n");

  TCase *tc_parse_test = tcase_create("parse test");
  tcase_add_test(tc_parse_test, parse_test_1);
  tcase_add_test(tc_parse_test, parse_test_2);
  tcase_add_test(tc_parse_test, parse_test_3);
  tcase_add_test(tc_parse_test, parse_no_file_1);
  tcase_add_test(tc_parse_test, parse_no_file_2);
  tcase_add_test(tc_parse_test, parse_invalid_1);
  tcase_add_test(tc_parse_test, parse_invalid_2);
  tcase_add_test(tc_parse_test, copy_data_test);
  suite_add_tcase(viewer, tc_parse_test);

  return viewer;
}