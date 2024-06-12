/**
 * @file parse.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module by model parsing
 * @version 1.0
 * @date 2024-05-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#define _GNU_SOURCE

#include "./include/parse.h"

/**
 * @brief Parses the model. If the filename is NULL, the structure is simply initialized. If the filename is valid - model parsing
 * 
 * @param[out] filename path to obj file
 * @return data_t - structure filled with data about the model
 */
data_t parse(const char *filename) {
  FILE *obj = NULL;
  data_t data;

  if(filename) {
    obj = fopen(filename, "r");
  }

  init_data(&data, obj);

  if (obj) {
    get_data(&data, obj);
  }
  
  if(filename) {
    fclose(obj);
  }

  return data;
}

/**
 * @brief Initialize the model. If the obj is NULL, the structure is simply initialized. If the obj is valid - memory allocated
 * 
 * @param[out] data models data
 * @param[out] obj obj model file
 */
void init_data(data_t *data, FILE *obj) {
  data->vertex_count = 0;
  data->facet_count = 0;
  data->full_cnt = 0;
  data->max_position = 0.0f;

  if(obj != NULL) {
    char *line = NULL;
    size_t n = 0;
    ssize_t len;

    while ((len = getline(&line, &n, obj)) != -1) {
      if (*line == 'v' && *(line + 1) == ' ') {
        data->vertex_count++;
      } else if (*line == 'f' && *(line + 1) == ' ') {
        ///@todo move full_cnt here
        data->facet_count++;
      }
    }

    data->vertexes = mx_create(data->vertex_count, V_DOTS_CNT);

    rewind(obj);

    while ((len = getline(&line, &n, obj)) != -1) {
      if (*line == 'f' && *(line + 1) == ' ') {
        data->full_cnt += vert_count_in_facet(line + 1);
      }
    }

    data->full_cnt *= 2;

    data->facets = (int *)calloc(data->full_cnt, sizeof(int));

    if(line) {
        free(line);
        line = NULL;
    }

    rewind(obj);
  } else {
    data->facets = NULL;
    data->vertexes.matrix = NULL;
    data->vertexes.rows = 0;
    data->vertexes.cols = 0;
  }
}

/**
 * @brief Clear model of data
 * 
 * @param[out] data models data
 */
void remove_data(data_t *data) {
  mx_remove(&data->vertexes);

  if (data->facets) {
    free(data->facets);
    data->facets = NULL;
  }

  data->vertex_count = 0;
  data->facet_count = 0;
  data->full_cnt = 0;
  data->max_position = 0.0f;
}

void get_data(data_t *data, FILE *obj) {
  char *token = NULL;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;
  float *v_ptr = data->vertexes.matrix;
  int *f_ptr = data->facets;

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

      token = strtok(line + 1, " ");
      
      while (token != NULL) {
        if (f_ptr == begin) {
          *f_ptr++ = atoi(token) - 1;
        } else {
          *f_ptr++ = atoi(token) - 1;
          *f_ptr = *(f_ptr - 1);
          ///@todo prefix/postfix
          f_ptr++;
        }
        token = strtok(NULL, " ");
        if(token && !strpbrk(token, "0123456789")) token = NULL;
      }

      *f_ptr++ = *begin;
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
  data.facets = NULL;
  data.vertexes = mx_create(data.vertex_count, V_DOTS_CNT);

  for (int i = 0; i < data.vertex_count * V_DOTS_CNT; i++) {
    ///@todo memcpy
    data.vertexes.matrix[i] = object->vertexes.matrix[i];
  }

  return data;
}