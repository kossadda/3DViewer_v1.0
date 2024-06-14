/**
 * @file parse.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Module header by model parsing
 * @version 1.0
 * @date 2024-06-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _PARSE_H_
#define _PARSE_H_

#include <ctype.h>

#include "./objects.h"

/// @brief 1 degree in radians
#define RAD 0.0174532925199433

int parse(char *filename, data_t *data);
data_t copy_data(data_t *object);
void remove_data(data_t *data);

#endif  // _PARSE_H_