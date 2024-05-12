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

#include "./matrix.h"

#define V_DOTS_CNT 3

typedef struct {
  int *vertexes;
  int count;
} facet_t;

typedef struct {
  matrix_t vertexes;
  int vertex_count;
  facet_t *facets;
  int facet_count;
} data_t;

#endif // _OBJECTS_H_