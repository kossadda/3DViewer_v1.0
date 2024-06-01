/**
 * @file afine.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <math.h>

#include "./include/common.h"

void move_model(data_t *data, data_t *object, float x, float y, float z) {
  float move[] = {1.0f, 0.0f, 0.0f, x, 0.0f, 1.0f, 0.0f, y,
                  0.0f, 0.0f, 1.0f, z, 0.0f, 0.0f, 0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, object->vertexes.matrix, move,
          data->vertexes.rows);
}

void x_rotate_model(data_t *data, data_t *object, float degree) {
  float rotate[] = {1.0f, 0.0f,         0.0f,          0.0f,
                    0.0f, cosf(degree), -sinf(degree), 0.0f,
                    0.0f, sinf(degree), cosf(degree),  0.0f,
                    0.0f, 0.0f,         0.0f,          1.0f};

  mx_mult(data->vertexes.matrix, object->vertexes.matrix, rotate,
          data->vertexes.rows);
}

void y_rotate_model(data_t *data, data_t *object, float degree) {
  float rotate[] = {cosf(degree), 0.0f, sinf(degree),  0.0f, 0.0f,         1.0f,
                    0.0f,         0.0f, -sinf(degree), 0.0f, cosf(degree), 0.0f,
                    0.0f,         0.0f, 0.0f,          1.0f};

  mx_mult(data->vertexes.matrix, object->vertexes.matrix, rotate,
          data->vertexes.rows);
}

void z_rotate_model(data_t *data, data_t *object, float degree) {
  float rotate[] = {cosf(degree), -sinf(degree), 0.0f, 0.0f,
                    sinf(degree), cosf(degree),  0.0f, 0.0f,
                    0.0f,         0.0f,          1.0f, 0.0f,
                    0.0f,         0.0f,          0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, object->vertexes.matrix, rotate,
          data->vertexes.rows);
}

void scale_model(data_t *data, data_t *object, float x, float y, float z) {
  float move[] = {x,    0.0f, 0.0f, 0.0f, 0.0f, y,    0.0f, 0.0f,
                  0.0f, 0.0f, z,    0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, object->vertexes.matrix, move,
          data->vertexes.rows);
}

void normalize_vertex(data_t *data) {
  float *vertex = data->vertexes.matrix;

  for (int i = 0; i < data->vertex_count; i++, vertex += 3) {
    for (int j = 0; j < 3; j++) {
      vertex[j] /= data->max_position;
    }
  }
}