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
#include "stdio.h"

data_t parse(char *filename);
void init_data(data_t *data, FILE *obj);

#endif // _COMMON_H_