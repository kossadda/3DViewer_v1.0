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

// tmp
#define CHANGE_SIZE 0.05
#define PATH "/home/kossadda/data-samples/"
#define NAME "cube"

#define OBJECT (PATH NAME ".obj")

void move_model(data_t *data, data_t *object, float x, float y, float z);
void x_rotate_model(data_t *data, data_t *object, float degree);
void y_rotate_model(data_t *data, data_t *object, float degree);
void z_rotate_model(data_t *data, data_t *object, float degree);
void scale_model(data_t *data, data_t *object, float x, float y, float z);
void normalize_vertex(data_t *data);

#endif  //_AFINE_H_
