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

void vf_print(data_t data);

int main() {
  char *path = "/home/kossadda/develop/3DViewer_v1.0/data-samples/empty.obj";
  data_t data;
  printf("%d\n", parse(path, &data));
  // data_t data;
  // parse("./../data-samples/bootle.obj", &data);
  
  // vf_print(data);

  // remove_data(&data);
}

void vf_print(data_t data) {
  for(int i = 0; i < data.vertex_count; i++) {
    printf("%d) ", i + 1);
    for(int j = 0; j < V_CNT; j++) {
      printf("%.6f ", data.vertexes.matrix[i * data.vertexes.cols + j]);
    }
    printf("\n");
  }  

  printf("\n\nFacets:\n\n");

  int *ptr = data.facets;

  for(int i = 0; i < data.full_cnt; i++) {
    printf("%d ", data.facets[i]);
    if(i && data.facets[i - 1] != data.facets[i] && *ptr == data.facets[i] && ptr != data.facets + i) {
      ptr = data.facets + i + 1;
      printf("\n");
    }

  }

  printf("\n\n");
}

// void fill(matrix_t *mx, float *arr) {
//     for(int i = 0; i < mx->rows * mx->cols; i++) {
//         mx->matrix[i] = arr[i];
//     }
// }

// void printof(matrix_t *mx) {
//     for(int i = 0; i < mx->rows * mx->cols; i++) {
//         if(i && i % mx->cols == 0) {
//             printf("\n");
//         }
//         printf("%f ", mx->matrix[i]);
//     }
//     printf("\n");
// }

// int main() {
//     matrix_t m1 = mx_create(4, 4);
//     matrix_t m2 = mx_create(4, 4);
//     float arr1[] = {1, 2, 3, 4, 5 , 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; 
//     // float arr2[] = {-2.0, 1.0, 8.0};
//     fill(&m1, arr1);
//     fill(&m2, arr1);

//     mx_affine_mult(m1.matrix, m2.matrix);
//     printof(&m1);

//     mx_remove(&m1);
//     mx_remove(&m2);
// }
