/**
 * @file afine.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for working with transformation matrix
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./include/afine.h"

/**
 * @brief Initialize transformation matrices
 * 
 * @return afinne_t - object with allocated memory
 */
afinne_t init_afinne() {
  afinne_t mx;

  mx.current = (float *)calloc(4 * 4, sizeof(float));
  mx.identity = (float *)calloc(4 * 4, sizeof(float));
  mx.move = (float *)calloc(4 * 4, sizeof(float));
  mx.scale = (float *)calloc(4 * 4, sizeof(float));
  mx.rotate_x = (float *)calloc(4 * 4, sizeof(float));
  mx.rotate_y = (float *)calloc(4 * 4, sizeof(float));
  mx.rotate_z = (float *)calloc(4 * 4, sizeof(float));

  mx.identity[0] = mx.identity[5] = mx.identity[10] = mx.identity[15] = 1.0f;
  mx.move[0] = mx.move[5] = mx.move[10] = mx.move[15] = 1.0f;
  mx.scale[0] = mx.scale[5] = mx.scale[10] = mx.scale[15] = 1.0f;
  mx.rotate_x[0] = mx.rotate_x[5] = mx.rotate_x[10] = mx.rotate_x[15] = 1.0f;
  mx.rotate_y[0] = mx.rotate_y[5] = mx.rotate_y[10] = mx.rotate_y[15] = 1.0f;
  mx.rotate_z[0] = mx.rotate_z[5] = mx.rotate_z[10] = mx.rotate_z[15] = 1.0f;

  return mx;
}

/**
 * @brief Clears memory allocated for conversion matrices
 * 
 * @param[out] mx - matrix data struct
 */
void destroy_affine(afinne_t *mx) {
  if (mx->current) {
    free(mx->current);
    mx->current = NULL;
  }

  if (mx->identity) {
    free(mx->identity);
    mx->identity = NULL;
  }

  if (mx->move) {
    free(mx->move);
    mx->move = NULL;
  }

  if (mx->scale) {
    free(mx->scale);
    mx->scale = NULL;
  }

  if (mx->rotate_x) {
    free(mx->rotate_x);
    mx->rotate_x = NULL;
  }

  if (mx->rotate_y) {
    free(mx->rotate_y);
    mx->rotate_y = NULL;
  }

  if (mx->rotate_y) {
    free(mx->rotate_y);
    mx->rotate_y = NULL;
  }
}

/**
 * @brief Normalizes model coordinates to a range [-1;1]
 * 
 * @param[out] data models data struct
 */
void normalize_vertex(data_t *data) {
  float *vertex = data->vertexes.matrix;

  for (int i = 0; i < data->vertex_count; i++, vertex += 3) {
    for (int j = 0; j < 3; j++) {
      vertex[j] /= data->max_position;
    }
  }
}

/**
 * @brief Multiplies transformation matrices into one result matrix
 * 
 * @param[out] mx struct of transformation matrices
 * @param[in] data bitwise representation of changes in transformation matrices
 * @param[in] mode model rotation mode. 0 - around its axis, 1 - around the coordinate axes
 */
void transform_mx(afinne_t *mx, unsigned int data, int mode) {
  mx_copy(mx->current, mx->identity);

  if(mode == 0) {
    if (data & SCALE) mx_mult_4x4(mx->current, mx->scale);
    if (data & ROTATE_X) mx_mult_4x4(mx->current, mx->rotate_x);
    if (data & ROTATE_Y) mx_mult_4x4(mx->current, mx->rotate_y);
    if (data & ROTATE_Z) mx_mult_4x4(mx->current, mx->rotate_z);
    if (data & MOVE) mx_mult_4x4(mx->current, mx->move);
  } else {
    if (data & SCALE) mx_mult_4x4(mx->current, mx->scale);
    if (data & ROTATE_X) mx_mult_4x4(mx->current, mx->rotate_x);
    if (data & ROTATE_Y) mx_mult_4x4(mx->current, mx->rotate_y);
    if (data & ROTATE_Z) mx_mult_4x4(mx->current, mx->rotate_z);
    if (data & MOVE) mx_mult_4x4(mx->current, mx->move);
  }
}
