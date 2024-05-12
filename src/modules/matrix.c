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

#include "./matrix.h"

matrix_t mx_create(int rows, int cols) {
  matrix_t create;

  create.rows = rows;
  create.cols = cols;
  create.matrix = (double **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    create.matrix[i] = (double *)calloc(cols, sizeof(double));
  }

  return create;
}

void mx_remove(matrix_t *mx) {
  if(mx->matrix) {
    for(int i = 0; i < mx->rows; i++) {
      if(mx->matrix[i]) {
        free(mx->matrix[i]);
        mx->matrix[i] = NULL;
      }
    }

    free(mx->matrix);
    mx->matrix = NULL;
  }
  
  mx->rows = 0;
  mx->cols = 0;
}