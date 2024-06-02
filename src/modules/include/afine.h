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

#define PATH "/home/kossadda/data-samples/"
#define NAME "100000_sirus_city"

#define OBJECT (PATH NAME ".obj")

#define SCALE 1u
#define MOVE 1u << 1
#define ROTATE_X 1u << 2
#define ROTATE_Y 1u << 3
#define ROTATE_Z 1u << 4

afinne_t init_afinne();
void destroy_affine(afinne_t *mx);
void move_model(data_t *data, data_t *object, float x, float y, float z);
void x_rotate_model(data_t *data, data_t *object, float degree);
void y_rotate_model(data_t *data, data_t *object, float degree);
void z_rotate_model(data_t *data, data_t *object, float degree);
void scale_model(data_t *data, data_t *object, float x, float y, float z);
void normalize_vertex(data_t *data);
void transform_mx(afinne_t *mx, unsigned int data);

#endif  //_AFINE_H_
