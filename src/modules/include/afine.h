/**
 * @file afine.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _AFINE_H_
#define _AFINE_H_

#include "./objects.h"

#define SCALE 1u
#define MOVE 1u << 1
#define ROTATE_X 1u << 2
#define ROTATE_Y 1u << 3
#define ROTATE_Z 1u << 4

afinne_t init_afinne();
void destroy_affine(afinne_t *mx);
void normalize_vertex(data_t *data);
void transform_mx(afinne_t *mx, unsigned int data, int mode);

#endif  //_AFINE_H_
