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
    char *path = "./../../../data-samples/cube.obj";
    data_t data = parse(path);
    ck_assert_int_eq(data.vertex_count, 8);
    ck_assert_int_eq(data.facet_count, 12);
    float *vx = data.vertexes.matrix; 

    for(int i = 0; i < V_CNT; i++) {

    }
}

START_TEST(parse_test_2) {
    char *path = "./../../../data-samples/cottage.obj";
    data_t data = parse(path);
    ck_assert_int_eq(data.vertex_count, 353);
    ck_assert_int_eq(data.facet_count, 259);
}

START_TEST(parse_test_3) {
    char *path = "./../../../data-samples/bootle.obj";
    data_t data = parse(path);
    ck_assert_int_eq(data.vertex_count, 26105);
    ck_assert_int_eq(data.facet_count, 65480);
}

// ============================================================================

Suite *parse_test(void) {
  Suite *viewer = suite_create("\nparse tests\n");

  TCase *tc_parse_test = tcase_create("parse test");
  tcase_add_test(tc_parse_test, parse_test_1);
  tcase_add_test(tc_parse_test, parse_test_2);
  tcase_add_test(tc_parse_test, parse_test_3);
  suite_add_tcase(viewer, tc_parse_test);

  return viewer;
}