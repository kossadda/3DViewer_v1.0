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

#include <ctype.h>
#include <stdbool.h>

#include "./include/common.h"

data_t parse(const char *filename) {
  FILE *obj = fopen(filename, "r");
  data_t data;

  if (obj) {
    init_data(&data, obj);

    get_data(&data, obj);

    fclose(obj);
  } else {
  }

  return data;
}

void init_data(data_t *data, FILE *obj) {
  data->vertex_count = 0;
  data->facet_count = 0;
  data->full_cnt = 0;
  data->max_position = 0.0;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;

  while ((len = getline(&line, &n, obj)) != -1) {
    if (*line == 'v' && *(line + 1) == ' ') {
      data->vertex_count++;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      data->facet_count++;
    }
  }

  data->vertexes = mx_create(data->vertex_count, V_DOTS_CNT);
  data->v_in_facet = (int *)calloc(data->facet_count, sizeof(int));

  rewind(obj);

  int *ptr = data->v_in_facet;

  while ((len = getline(&line, &n, obj)) != -1) {
    if (*line == 'f' && *(line + 1) == ' ') {
      *ptr++ = vert_count_in_facet(line + 1);
      data->full_cnt += *(ptr - 1) * 2;
    }
  }

  data->facets = (int *)calloc(data->full_cnt, sizeof(int));

  free(line);
  line = NULL;

  rewind(obj);
}

void remove_data(data_t *data) {
  mx_remove(&data->vertexes);

  if (data->v_in_facet) {
    free(data->v_in_facet);
    data->v_in_facet = NULL;
  }

  if (data->facets) {
    free(data->facets);
    data->facets = NULL;
  }
}

void get_data(data_t *data, FILE *obj) {
  char *token = NULL;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;
  float *v_ptr = data->vertexes.matrix;
  int *f_ptr = data->facets;
  int *f_cnt = data->v_in_facet;

  while ((len = getline(&line, &n, obj)) != -1) {
    if (*line == 'v' && *(line + 1) == ' ') {
      for (int j = 0; j < V_DOTS_CNT; j++, v_ptr++) {
        token = strtok((token) ? NULL : (line + 1), " ");
        *v_ptr = atof(token);
        if (data->max_position < fabsf(*v_ptr)) {
          data->max_position = fabs(*v_ptr);
        }
      }

      token = NULL;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      int *begin = f_ptr;

      for (int j = 0; j < *f_cnt; j++) {
        token = strtok((token) ? NULL : (line + 1), " ");
        if (f_ptr == begin) {
          *f_ptr++ = atoi(token) - 1;
        } else {
          *f_ptr++ = atoi(token) - 1;
          *f_ptr = *(f_ptr - 1);
          f_ptr++;
          if (j == *f_cnt - 1) {
            *f_ptr++ = *begin;
          }
        }
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

  for (char *ptr = str + strlen(str) - 1; isdigit(*ptr) == 0; ptr--) {
    *ptr = '\0';
  }

  while ((token = strtok((token) ? NULL : str, " ")) != NULL) count++;

  return count;
}

data_t copy_data(data_t *object) {
  data_t data;

  data.vertex_count = object->vertex_count;
  data.facet_count = object->facet_count;
  data.full_cnt = object->full_cnt;
  data.max_position = object->max_position;
  data.v_in_facet = NULL;
  data.facets = NULL;

  data.vertexes = mx_create(data.vertex_count, V_DOTS_CNT);

  for (int i = 0; i < data.vertex_count * V_DOTS_CNT; i++) {
    data.vertexes.matrix[i] = object->vertexes.matrix[i];
  }

  return data;
}