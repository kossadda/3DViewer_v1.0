/**
 * @file matrix.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for working with matrices
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./include/matrix.h"

/**
 * @brief Creates a matrix
 *
 * @param[in] rows number of rows
 * @param[in] cols number of columns
 * @return matrix_t - created matrix
 */
matrix_t mx_create(int rows, int cols) {
  matrix_t create;

  create.rows = rows;
  create.cols = cols;
  create.matrix = (float *)calloc(rows * cols, sizeof(float));

  return create;
}

/**
 * @brief Clears the memory allocated to the matrix
 *
 * @param[out] mx matrix
 */
void mx_remove(matrix_t *mx) {
  if (mx->matrix) {
    free(mx->matrix);
    mx->matrix = NULL;
  }

  mx->rows = 0;
  mx->cols = 0;
}

/**
 * @brief Multiplies a 4x4 matrix by a 4x1 column vector
 *
 * @param[out] data vertices subject to affine transformations
 * @param[in] vertexes initial values ​​of vertex coordinates
 * @param[in] vector transformation matrix
 * @param[in] rows number of vertices
 */
void mx_mult_vector(float *data, float *vertexes, float *vector, int rows) {
  for (int k = 0; k < rows; k++, vertexes += V_CNT, data += V_CNT) {
    float *vr = vector;

    for (int i = 0; i < V_CNT; i++, vr += TR_MX_SIZE) {
      data[i] = vr[0] * vertexes[0] + vr[1] * vertexes[1] +
                vr[2] * vertexes[2] + vr[3];
    }
  }
}

/**
 * @brief Multiplies a 4x4 matrix by a 4x4 matrix
 *
 * @param[out] current effective transformation matrix
 * @param[in] mul affine transformation matrix
 */
void mx_mult_4x4(float *current, float *mul) {
  float tmp[TR_MX_SIZE * TR_MX_SIZE];
  float sum;

  for (int i = 0; i < TR_MX_SIZE; i++) {
    for (int j = 0; j < TR_MX_SIZE; j++) {
      sum = 0;

      for (int k = 0; k < TR_MX_SIZE; k++) {
        sum += current[i * TR_MX_SIZE + k] * mul[k * TR_MX_SIZE + j];
      }

      tmp[i * TR_MX_SIZE + j] = sum;
    }
  }

  mx_copy(current, tmp);
}

/**
 * @brief Copies the values ​​of one 4x4 matrix to another
 *
 * @param[out] copy where to copy
 * @param[in] data where to copy from
 */
void mx_copy(float *copy, float *data) {
  memcpy(copy, data, TR_MX_SIZE * TR_MX_SIZE * sizeof(float));
}