/**
 * @file parse.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-06-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _PARSE_H_
#define _PARSE_H_

#include "./objects.h"

#define RAD 0.0174532925199433

data_t parse(const char *filename);
data_t copy_data(data_t *object);
void init_data(data_t *data, FILE *obj);
void remove_data(data_t *data);
void get_data(data_t *data, FILE *obj);
int vert_count_in_facet(char *line);

#endif  // _PARSE_H_
