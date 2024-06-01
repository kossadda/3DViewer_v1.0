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

#define OBJECT "/home/kossadda/develop/3DViewer_v1.0/data-samples/sphere.obj"

void fill(matrix_t *mx, float *arr) {
    for(int i = 0; i < mx->rows * mx->cols; i++) {
        mx->matrix[i] = arr[i];
    }
}

void printof(matrix_t *mx) {
    for(int i = 0; i < mx->rows * mx->cols; i++) {
        if(i && i % mx->cols == 0) {
            printf("\n");
        }
        printf("%f ", mx->matrix[i]);
    }
    printf("\n");
}

int main() {
    matrix_t m1 = mx_create(3, 3);
    matrix_t m2 = mx_create(3, 1);
    float arr1[] = {0.5, -0.75, 5.0, 2.0, 1.0 / 3.0, -0.5, 4.0, -7.0, 0.75}; 
    float arr2[] = {-2.0, 1.0, 8.0};
    fill(&m1, arr1);
    fill(&m2, arr2);

    matrix_t res = mx_mult(&m1, &m2);
    printof(&res);

    mx_remove(&m1);
    mx_remove(&m2);
    mx_remove(&res);
}



// int main() {
//   data_t data = parse(OBJECT);

//   for(int i = 0; i < data.vertex_count; i++) {
//     printf("%d) ", i + 1);
//     for(int j = 0; j < V_DOTS_CNT; j++) {
//       printf("%.12f ", data.vertexes.matrix[i * data.vertexes.cols + j]);
//     }
//     printf("\n");
//   }

//   printf("\n\nFacets:\n\n");

//   for(int i = 0, j = 0, *ptr = data.v_in_facet; i < data.full_cnt; i++, j++) {
//     if(j >= *ptr * 2) {
//       printf("\n");
//       j = 0;
//       ptr++;
//     }
//     printf("%d ", data.facets[i]);
//   }

//   printf("\n\n");

//   remove_data(&data);
// }