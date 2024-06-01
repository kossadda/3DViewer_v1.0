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

// matrix_t mx_mult(matrix_t *mx_1, matrix_t *mx_2) {
//     matrix_t res = mx_create(mx_2->rows, mx_2->cols);

//     for(int i = 0; i < mx_2->rows; i++) {
//         for(int j = 0; j < mx_1->cols; j++) {
//             res.matrix[i] += mx_1->matrix[i * mx_1->cols + j] *
//             mx_2->matrix[j];
//         }
//     }

//     return res;
// }

void mx_mult(float *data, float *move) {
  for (int i = 0; i < 3; i++, move += 4) {
    *(data + i) = (*move + *(move + 1) + *(move + 2)) * *(data + i) + *(move + 3);
  }
}