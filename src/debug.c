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

#include "./modules/include/common.h"

#define OBJECT "/home/kossadda/desktop/3DViewer_v1.0/src/_objfiles/1000 Glass.obj"

int main() {
  data_t data = parse(OBJECT);

  for(int i = 1; i < data.vertex_count; i++) {
    for(int j = 0; j < V_DOTS_CNT; j++) {
      printf("%.12f ", data.vertexes.matrix[i][j]);
    }
    printf("\n");
  }

  printf("\n\nFacets:\n\n");

  for(int i = 0; i < data.facet_count; i++) {
    for(int j = 0; j < (data.facets + i)->count; j++) {
      printf("%d ", *((data.facets + i)->vertexes + j));
    }
    printf("\n");
  }

  remove_data(&data);
}