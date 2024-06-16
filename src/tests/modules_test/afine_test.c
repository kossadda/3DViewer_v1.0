/**
 * @file afine_test.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for test afine module functions
 * @version 1.0
 * @date 2024-06-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include_test/afine_test.h"

// ============================================================================

START_TEST(test_move_x) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.move[3] = 1.0f;
  transform_mx(&mx, 1u | MOVE);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {0.0f, -1.0f, 2.0f, 2.0f,  -1.0f, 2.0f, 0.0f,  1.0f,
                      2.0f, 2.0f,  1.0f, 2.0f,  0.0f,  1.0f, 0.0f,  2.0f,
                      1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  2.0f, -1.0f, 0.0f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_move_y) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.move[7] = 1.0f;
  transform_mx(&mx, 1u | MOVE);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {-1.0f, 0.0f, 2.0f,  1.0f, 0.0f,  2.0f, -1.0f, 2.0f,
                      2.0f,  1.0f, 2.0f,  2.0f, -1.0f, 2.0f, 0.0f,  1.0f,
                      2.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_move_z) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.move[11] = 1.0f;
  transform_mx(&mx, 1u | MOVE);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {-1.0f, -1.0f, 3.0f,  1.0f,  -1.0f, 3.0f, -1.0f, 1.0f,
                      3.0f,  1.0f,  1.0f,  3.0f,  -1.0f, 1.0f, 1.0f,  1.0f,
                      1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_move) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.move[3] = 1.0f;
  mx.move[7] = 1.0f;
  mx.move[11] = 1.0f;
  transform_mx(&mx, 1u | MOVE);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {0.0f, 0.0f, 3.0f, 2.0f, 0.0f, 3.0f, 0.0f, 2.0f,
                      3.0f, 2.0f, 2.0f, 3.0f, 0.0f, 2.0f, 1.0f, 2.0f,
                      2.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 1.0f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_rotate_x) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.rotate_x[5] = mx.rotate_x[10] = cosf(RAD);
  mx.rotate_x[9] = sin(RAD);
  mx.rotate_x[6] = -mx.rotate_x[9];
  transform_mx(&mx, 1u | ROTATE_X);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {
      -1.000000f, -1.034752f, 1.982243f,  1.000000f, -1.034752f, 1.982243f,
      -1.000000f, 0.964943f,  2.017148f,  1.000000f, 0.964943f,  2.017148f,
      -1.000000f, 0.999848f,  0.017452f,  1.000000f, 0.999848f,  0.017452f,
      -1.000000f, -0.999848f, -0.017452f, 1.000000f, -0.999848f, -0.017452f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_rotate_y) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.rotate_y[0] = mx.rotate_y[10] = cosf(RAD);
  mx.rotate_y[2] = sin(RAD);
  mx.rotate_y[8] = -mx.rotate_y[2];
  transform_mx(&mx, 1u | ROTATE_Y);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {
      -0.964943f, -1.000000f, 2.017148f, 1.034752f, -1.000000f, 1.982243f,
      -0.964943f, 1.000000f,  2.017148f, 1.034752f, 1.000000f,  1.982243f,
      -0.999848f, 1.000000f,  0.017452f, 0.999848f, 1.000000f,  -0.017452f,
      -0.999848f, -1.000000f, 0.017452f, 0.999848f, -1.000000f, -0.017452f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_rotate_z) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.rotate_z[0] = mx.rotate_z[5] = cosf(RAD);
  mx.rotate_z[4] = sin(RAD);
  mx.rotate_z[1] = -mx.rotate_z[4];
  transform_mx(&mx, 1u | ROTATE_Z);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {
      -0.982395f, -1.017300f, 2.000000f, 1.017300f, -0.982395f, 2.000000f,
      -1.017300f, 0.982395f,  2.000000f, 0.982395f, 1.017300f,  2.000000f,
      -1.017300f, 0.982395f,  0.000000f, 0.982395f, 1.017300f,  0.000000f,
      -0.982395f, -1.017300f, 0.000000f, 1.017300f, -0.982395f, 0.000000f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_rotate) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.rotate_x[5] = mx.rotate_x[10] = cosf(RAD);
  mx.rotate_x[9] = sin(RAD);
  mx.rotate_x[6] = -mx.rotate_x[9];
  mx.rotate_y[0] = mx.rotate_y[10] = cosf(RAD);
  mx.rotate_y[2] = sin(RAD);
  mx.rotate_y[8] = -mx.rotate_y[2];
  mx.rotate_z[0] = mx.rotate_z[5] = cosf(RAD);
  mx.rotate_z[4] = sin(RAD);
  mx.rotate_z[1] = -mx.rotate_z[4];
  transform_mx(&mx, 1u | ROTATE_X | ROTATE_Y | ROTATE_Z);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {
      -0.947341f, -1.052344f, 1.998779f,  1.052050f, -1.016835f, 1.964494f,
      -0.982240f, 0.947036f,  2.034288f,  1.017151f, 0.982545f,  2.000003f,
      -1.017145f, 0.981936f,  0.034897f,  0.982246f, 1.017444f,  0.000612f,
      -0.982246f, -1.017444f, -0.000612f, 1.017145f, -0.981936f, -0.034897f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_scale) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.scale[0] = mx.scale[5] = mx.scale[10] = 1.05f;
  transform_mx(&mx, 1u | SCALE);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {
      -1.050000f, -1.050000f, 2.100000f, 1.050000f, -1.050000f, 2.100000f,
      -1.050000f, 1.050000f,  2.100000f, 1.050000f, 1.050000f,  2.100000f,
      -1.050000f, 1.050000f,  0.000000f, 1.050000f, 1.050000f,  0.000000f,
      -1.050000f, -1.050000f, 0.000000f, 1.050000f, -1.050000f, 0.000000f,
  };

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_all_transformations) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);
  data_t copy = copy_data(&cube);

  afinne_t mx;
  init_afinne(&mx);
  mx.rotate_x[5] = mx.rotate_x[10] = cosf(RAD);
  mx.rotate_x[9] = sin(RAD);
  mx.rotate_x[6] = -mx.rotate_x[9];
  mx.rotate_y[0] = mx.rotate_y[10] = cosf(RAD);
  mx.rotate_y[2] = sin(RAD);
  mx.rotate_y[8] = -mx.rotate_y[2];
  mx.rotate_z[0] = mx.rotate_z[5] = cosf(RAD);
  mx.rotate_z[4] = sin(RAD);
  mx.rotate_z[1] = -mx.rotate_z[4];
  mx.scale[0] = mx.scale[5] = mx.scale[10] = 1.05f;
  mx.move[3] = 1.0f;
  mx.move[7] = 1.0f;
  mx.move[11] = 1.0f;
  transform_mx(&mx, ~0u);

  mx_mult_vector(cube.vertexes.matrix, copy.vertexes.matrix, mx.current,
                 cube.vertex_count);

  float expected[] = {0.054975f, -0.054967f, 3.149041f,  2.154335f, -0.017683f,
                      3.113041f, 0.018331f,  2.044383f,  3.186325f, 2.117691f,
                      2.081666f, 3.150325f,  -0.018319f, 2.081027f, 1.086964f,
                      2.081041f, 2.118311f,  1.050965f,  0.018325f, -0.018322f,
                      1.049680f, 2.117685f,  0.018962f,  1.013681f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&copy);
  destroy_affine(&mx);
}
END_TEST

START_TEST(test_normalize) {
  char *path = "./../data-samples/cube.obj";
  data_t cube;
  parse(path, &cube);

  normalize_vertex(&cube);
  float expected[] = {
      -0.500000f, -0.500000f, 1.000000f, 0.500000f, -0.500000f, 1.000000f,
      -0.500000f, 0.500000f,  1.000000f, 0.500000f, 0.500000f,  1.000000f,
      -0.500000f, 0.500000f,  0.000000f, 0.500000f, 0.500000f,  0.000000f,
      -0.500000f, -0.500000f, 0.000000f, 0.500000f, -0.500000f, 0.000000f};

  for (int i = 0; i < cube.vertex_count * V_CNT; i++) {
    ck_assert_float_eq_tol(cube.vertexes.matrix[i], expected[i], 1e-6);
  }

  remove_data(&cube);
  remove_data(&cube);
}
END_TEST

// ============================================================================

Suite *afine_test(void) {
  Suite *viewer = suite_create("\nafine tests\n");

  TCase *tc_afine_test = tcase_create("afine test");
  tcase_add_test(tc_afine_test, test_move_x);
  tcase_add_test(tc_afine_test, test_move_y);
  tcase_add_test(tc_afine_test, test_move_z);
  tcase_add_test(tc_afine_test, test_move);
  tcase_add_test(tc_afine_test, test_rotate_x);
  tcase_add_test(tc_afine_test, test_rotate_y);
  tcase_add_test(tc_afine_test, test_rotate_z);
  tcase_add_test(tc_afine_test, test_rotate);
  tcase_add_test(tc_afine_test, test_scale);
  tcase_add_test(tc_afine_test, test_all_transformations);
  tcase_add_test(tc_afine_test, test_normalize);
  suite_add_tcase(viewer, tc_afine_test);

  return viewer;
}