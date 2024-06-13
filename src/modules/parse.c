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
 * @param[in] filename path to obj file
 * @return data_t - structure filled with data about the model
 */
int parse(char *filename, data_t *data) {
  FILE *obj = NULL;
  int err = false;

  if(filename) {
    obj = fopen(filename, "r");
  }

  err = init_data(data, obj);

  if (obj && !err) {
    err = get_data(data, obj);
  }
  
  if(filename) {
    fclose(obj);
  }

  return err;
}

/**
 * @brief Initialize the model. If the obj is NULL, the structure is simply initialized. If the obj is valid - memory allocated
 * 
 * @param[out] data models data
 * @param[in] obj obj model file
 */
int init_data(data_t *data, FILE *obj) {
  int err = false;
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

    data->vertexes = mx_create(data->vertex_count, V_CNT);
    if (data->vertexes.matrix == NULL) err = true;

    rewind(obj);

    while ((len = getline(&line, &n, obj)) != -1) {
      if (*line == 'f' && *(line + 1) == ' ') {
        data->full_cnt += vert_count_in_facet(line + 2);
      }
    }

    data->full_cnt *= 2;

    data->facets = (int *)calloc(data->full_cnt, sizeof(int));
    if (data->facets == NULL) err = true;

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

  return err;
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

/**
 * @brief Fill the structure with data about the 3D model
 * 
 * @param[out] data models data struct
 * @param[in] obj obj model file
 */
int get_data(data_t *data, FILE *obj) {
  int err = false;
  char *token = NULL;
  char *line = NULL;
  size_t n = 0;
  ssize_t len;
  float *v_ptr = data->vertexes.matrix;
  int *f_ptr = data->facets;

  while ((len = getline(&line, &n, obj)) != -1) {
    if (*line == 'v' && *(line + 1) == ' ') {
      for (int j = 0; j < V_CNT; j++, v_ptr++) {
        token = strtok((token) ? NULL : (line + 1), " ");

        if (token && (strlen(token) > 1 && !strpbrk(token, "0123456789"))) {
          err = true;
        } else if (token) {
          *v_ptr = atof(token);
        }

        if (data->max_position < fabsf(*v_ptr)) {
          data->max_position = fabs(*v_ptr);
        }
      }

      token = NULL;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      int *begin = f_ptr;

      token = strtok(line + 1, " ");
      
      while (token != NULL) {
        int vertex = atoi(token);

        if (!vertex) {
          err = true;
        } else if (f_ptr == begin) {
          *f_ptr++ = vertex - 1;
        } else {
          *f_ptr++ = vertex - 1;
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

  if (line) {
    free(line);
    line = NULL;
  }

  return err;
}

/**
 * @brief Determines the number of vertices in one facet
 * 
 * @param[in] line string with vertices of one facet
 * @return int - number of vertices
 */
int vert_count_in_facet(char *line) {
  char *token = NULL;
  int count = 0;

  char str[strlen(line) + 1];
  sprintf(str, "%s", line);

  for(int i = strlen(str) - 1; i >= 0 && isdigit(str[i]) == 0; i--) {
    str[i] = '\0';
  }

  while ((token = strtok((token) ? NULL : str, " ")) != NULL) count++;

  return count;
}

/**
 * @brief Creates a copy of 3D model vertex data
 * 
 * @param[in] object 3D model data
 * @return data_t - copy of the model
 */
data_t copy_data(data_t *object) {
  data_t data;

  data.vertex_count = object->vertex_count;
  data.facet_count = object->facet_count;
  data.full_cnt = object->full_cnt;
  data.max_position = object->max_position;
  data.facets = NULL;
  data.vertexes = mx_create(data.vertex_count, V_CNT);

  for (int i = 0; i < data.vertex_count * V_CNT; i++) {
    ///@todo memcpy
    data.vertexes.matrix[i] = object->vertexes.matrix[i];
  }

  return data;
}
