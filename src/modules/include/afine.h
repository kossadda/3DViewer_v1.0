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
#define CHANGE_SIZE 15

void move_model(data_t *data, float x, float y, float z);
void x_rotate_model(data_t *data, float degree);
void y_rotate_model(data_t *data, float degree);
void z_rotate_model(data_t *data, float degree);
void scale_model(data_t *data, float x, float y, float z);

#endif  //_AFINE_H_
