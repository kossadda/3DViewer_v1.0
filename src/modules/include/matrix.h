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
#include <stdio.h>
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
void mx_mult(float *data, float *vertexes, float *vector, int rows);
void mx_copy(float *copy, float *data);
void mx_print(float *mx);
void mx_affine_mult(float *current, float *mul);

#endif  //_MATRIX_H_