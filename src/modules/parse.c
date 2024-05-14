/**
 * @file parse.c
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#define _GNU_SOURCE

#include "./include/common.h"
#include <ctype.h>
#include <stdbool.h>

data_t parse(const char *filename) {
  FILE *obj = fopen(filename, "r");
  data_t data;

  if(obj) {
    init_data(&data, obj);

    get_data(&data, obj);
    
    fclose(obj);
  } else {

  }

  return data;
}

void init_data(data_t *data, FILE *obj) {
  data->vertex_count = 1;
  data->facet_count = 0;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;

  while ((len = getline(&line, &n, obj)) != -1) {
    if(*line == 'v' && *(line + 1) == ' ') {
      data->vertex_count++; 
    } else if(*line == 'f' && *(line + 1) == ' ') {
      data->facet_count++; 
    }
  }

  data->vertexes = mx_create(data->vertex_count, V_DOTS_CNT);
  data->facets = (facet_t *)malloc(data->facet_count * sizeof(facet_t));

  for(int i = 0; i < data->facet_count; i++) {
    (data->facets + i)->count = 0;
    (data->facets + i)->vertexes = NULL;
  }

  free(line);
  line = NULL;

  rewind(obj);
}

void remove_data(data_t *data) {
  mx_remove(&data->vertexes);

  if(data->facets) {
    for(int i = 0; i < data->facet_count; i++) {
      if((data->facets + i) && (data->facets + i)->vertexes) {
        free((data->facets + i)->vertexes);
        (data->facets + i)->vertexes = NULL;
      }
    }
    free(data->facets);
    data->facets = NULL;
  }
}

void get_data(data_t *data, FILE *obj) {
  char *token = NULL;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;
  int v_cnt = 1;
  int f_cnt = 0;

  while ((len = getline(&line, &n, obj)) != -1) {
    if(*line == 'v' && *(line + 1) == ' ') {
      char *tmp_ptr = line + 2;

      for(int j = 0; j < V_DOTS_CNT; j++) {
        token = strtok((token) ? NULL : tmp_ptr, " ");
        data->vertexes.matrix[v_cnt][j] = atof(token);
      }

      v_cnt++;
      token = NULL;
    } else if(*line == 'f' && *(line + 1) == ' ') {
      char *tmp_ptr = line + 1;
      (data->facets + f_cnt)->count = vert_count_in_facet(line);

      (data->facets + f_cnt)->vertexes = (int *)malloc((data->facets + f_cnt)->count * sizeof(int));

      for(int j = 0; j < (data->facets + f_cnt)->count; j++) {
        token = strtok((token) ? NULL : tmp_ptr, " ");
        *((data->facets + f_cnt)->vertexes + j) = atoi(token);
      }

      f_cnt++;
      token = NULL;
    }
  }

  free(line);
  line = NULL;
}

int vert_count_in_facet(char *line) {
  char *token = NULL;
  int count = 0;

  char str[strlen(line) + 1];
  sprintf(str, "%s", line + 1);

  for(char *ptr  = str + strlen(str) - 1; isdigit(*ptr) == 0; ptr--) {
    *ptr = '\0';
  }

  while ((token = strtok((token) ? NULL : str, " ")) != NULL) count++;

  return count;
}