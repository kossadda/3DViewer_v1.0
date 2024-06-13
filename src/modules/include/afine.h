/**
 * @file afine.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Module header for working with transformation matrix
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _AFINE_H_
#define _AFINE_H_

#include "./objects.h"

/// @brief Bit multiplying the result matrix by the scale matrix
#define SCALE 1u

/// @brief Bit multiplying the result matrix by the translate matrix
#define MOVE 1u << 1

/// @brief Bit multiplying the result matrix by the X-axis rotate matrix
#define ROTATE_X 1u << 2

/// @brief Bit multiplying the result matrix by the Y-axis rotate matrix
#define ROTATE_Y 1u << 3

/// @brief Bit multiplying the result matrix by the Z-axis rotate matrix
#define ROTATE_Z 1u << 4

int init_afinne(afinne_t *mx);
void destroy_affine(afinne_t *mx);
void normalize_vertex(data_t *data);
void transform_mx(afinne_t *mx, unsigned int data);

#endif  //_AFINE_H_
