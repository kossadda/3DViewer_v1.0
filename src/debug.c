/**
 * @file debug.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./modules/common.h"

#define OBJECT "/home/kossadda/develop/3DViewer_v1.0/data-samples/cube.obj"

int main() {
  data_t data = parse(OBJECT);
  printf("Vertexes: %d\nFacets: %d\n", data.vertex_count, data.facet_count);
}