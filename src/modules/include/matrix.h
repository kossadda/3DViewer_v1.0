/**
 * @file matrix.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header of the module for working with matrices
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

/// @brief Number of vertex coordinates
#define V_CNT 3

/// @brief Transformation matrix dimension
#define TR_MX_SIZE 4

/// @brief Matrix struct
typedef struct {
  float *matrix; ///< Matrix array
  int rows; ///< Number of rows
  int cols; ///< Number of columns
} matrix_t;

matrix_t mx_create(int rows, int cols);
void mx_remove(matrix_t *mx);
void mx_copy(float *copy, float *data);
void mx_mult_vector(float *data, float *vertexes, float *vector, int rows);
void mx_mult_4x4(float *current, float *mul);

#endif  //_MATRIX_H_