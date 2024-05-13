/**
 * @file common.h
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include "./objects.h"

data_t parse(const char *filename);
void init_data(data_t *data, FILE *obj);
void remove_data(data_t *data);
void get_data(data_t *data, FILE *obj);

#endif // _COMMON_H_