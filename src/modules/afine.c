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

#include "./include/common.h"

void move_model(data_t *data, float x, float y, float z) {
  static float move_mx[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  move_mx[3] = x;
  move_mx[7] = y;
  move_mx[11] = z;

  for (int i = 0; i < data->vertex_count * 3; i += 3) {
    mx_mult(data->vertexes.matrix + i, move_mx);
  }
}