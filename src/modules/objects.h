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
  unsigned int *vertexes;
  unsigned int one_facet_count;
} facet_t;

typedef struct {
  unsigned int vertex_count;
  unsigned int facet_count;
  matrix_t vertexes;
  facet_t *facets;
} data_t;

#endif // _OBJECTS_H_