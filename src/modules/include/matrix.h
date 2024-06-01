/**
 * @file matrix.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct {
  float *matrix;
  int rows;
  int cols;
} matrix_t;

matrix_t mx_create(int rows, int cols);
void mx_remove(matrix_t *mx);
// matrix_t mx_mult(matrix_t *mx_1, matrix_t *mx_2);
void mx_mult(float *data, float *move);

#endif  //_MATRIX_H_