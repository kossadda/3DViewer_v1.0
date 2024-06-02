/**
 * @file objects.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "./matrix.h"

#define V_DOTS_CNT 3

typedef struct {
  int vertex_count;
  matrix_t vertexes;
  int facet_count;
  int *v_in_facet;
  int *facets;
  int full_cnt;
  float max_position;
} data_t;

typedef struct {
  float *current;
  float *identity;
  float *move;
  float *rotate_x;
  float *rotate_y;
  float *rotate_z;
  float *scale;
} afinne_t;

#endif  // _OBJECTS_H_