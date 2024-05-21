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

#define OBJECT "/home/kossadda/desktop/3DViewer_v1.0/src/_objfiles/in cube 2.obj"

int main() {
  data_t data = parse(OBJECT);

  for(int i = 0; i < data.vertex_count; i++) {
    for(int j = 0; j < V_DOTS_CNT; j++) {
      printf("%.12f ", data.vertexes.matrix[i * data.vertexes.cols + j]);
    }
    printf("\n");
  }

  printf("\n\nFacets:\n\n");

  for(int i = 0, j = 0, *ptr = data.v_in_facet; i < data.full_cnt; i++, j++) {
    if(j >= *ptr * 2) {
      printf("\n");
      j = 0;
      ptr++;
    }
    printf("%d ", data.facets[i]);
  }

  printf("\n\n");

  remove_data(&data);
}