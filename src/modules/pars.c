/**
 * @file pars.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./common.h"

data_t parse(char *filename) {
  FILE *obj = fopen(filename, "r");
  data_t data;
  init_data(&data, obj);

  fclose(obj);
  return data;
}

void init_data(data_t *data, FILE *obj) {
  data->vertex_count = 0;
  data->facet_count = 0;
  char line[255];

  while (fgets(line, 255, obj)) {
    if(*line == 'v' && *(line + 1) == ' ') {
      data->vertex_count++; 
    } else if(*line == 'f' && *(line + 1) == ' ') {
      data->facet_count++; 
    }
  }

  data->vertexes = mx_create(data->vertex_count, V_DOTS_CNT);
  data->facets = (facet_t *)malloc(data->facet_count * sizeof(facet_t));

  rewind(obj);
}