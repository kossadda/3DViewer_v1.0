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

void move_model(data_t *data, float x, float y, float z) {
  float move[] = {1.0f, 0.0f, 0.0f, x, 0.0f, 1.0f, 0.0f, y,
                  0.0f, 0.0f, 1.0f, z, 0.0f, 0.0f, 0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, move, data->vertexes.rows);
}

void x_rotate_model(data_t *data, float degree) {
  float rotate[] = {1.0f, 0.0f,         0.0f,          0.0f,
                    0.0f, cosf(degree), -sinf(degree), 0.0f,
                    0.0f, sinf(degree), cosf(degree),  0.0f,
                    0.0f, 0.0f,         0.0f,          1.0f};

  mx_mult(data->vertexes.matrix, rotate, data->vertexes.rows);
}

void y_rotate_model(data_t *data, float degree) {
  float rotate[] = {cosf(degree), 0.0f, sinf(degree),  0.0f, 0.0f,         1.0f,
                    0.0f,         0.0f, -sinf(degree), 0.0f, cosf(degree), 0.0f,
                    0.0f,         0.0f, 0.0f,          1.0f};

  mx_mult(data->vertexes.matrix, rotate, data->vertexes.rows);
}

void z_rotate_model(data_t *data, float degree) {
  float rotate[] = {cosf(degree), -sinf(degree), 0.0f, 0.0f,
                    sinf(degree), cosf(degree),  0.0f, 0.0f,
                    0.0f,         0.0f,          1.0f, 0.0f,
                    0.0f,         0.0f,          0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, rotate, data->vertexes.rows);
}

void scale_model(data_t *data, float x, float y, float z) {
  float move[] = {x,    0.0f, 0.0f, 0.0f, 0.0f, y,    0.0f, 0.0f,
                  0.0f, 0.0f, z,    0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  mx_mult(data->vertexes.matrix, move, data->vertexes.rows);
}