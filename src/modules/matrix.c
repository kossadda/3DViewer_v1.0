/**
 * @file matrix.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./include/matrix.h"

matrix_t mx_create(int rows, int cols) {
  matrix_t create;

  create.rows = rows;
  create.cols = cols;
  create.matrix = (float *)calloc(rows * cols, sizeof(float));

  return create;
}

void mx_remove(matrix_t *mx) {
  if (mx->matrix) {
    free(mx->matrix);
    mx->matrix = NULL;
  }

  mx->rows = 0;
  mx->cols = 0;
}

void mx_mult(float *data, float *vertexes, float *vector, int rows) {
  for (int k = 0; k < rows; k++, vertexes += 3, data += 3) {
    float vx[4] = {vertexes[0], vertexes[1], vertexes[2], 1.0f};
    float *vr = vector;

    for (int i = 0; i < 3; i++, vr += 4) {
      float tmp = 0;

      for (int j = 0; j < 4; j++) {
        tmp += vr[j] * vx[j];
      }

      data[i] = tmp;
    }
  }
}

void mx_affine_mult(float *current, float *mul) {
  float tmp[4 * 4];
  float sum;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      sum = 0;

      for (int k = 0; k < 4; k++) {
        sum += current[i * 4 + k] * mul[k * 4 + j];
      }

      tmp[i * 4 + j] = sum;
    }
  }

  mx_copy(current, tmp);
}

void mx_copy(float *copy, float *data) {
  for (int i = 0; i < 4 * 4; i++) {
    copy[i] = data[i];
  }
}

void mx_print(float *mx) {
  for (int i = 0; i < 16; i++) {
    if (i && i % 4 == 0) {
      printf("\n");
    }

    printf("%f ", mx[i]);
  }

  printf("\n\n");
}