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

#define OBJECT "/home/kossadda/desktop/data-samples/dragon.obj"

int main() {
  parse(OBJECT);
  // data_t data = parse(OBJECT);
  // printf("Vertexes: %d\nFacets: %d\n", data.vertex_count, data.facet_count);
}