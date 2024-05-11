#include "./brick_game/tetris/include/common.h"

int main() {
  game_t *g = game();
  init_game();


  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      printf("%d ", CELL(i, j));
    }
    printf("\n");
  }
  printf("\n");

  userInput(Action, 0);


  for (int i = 0; i < BL_MAX; i++) {
    for (int j = 0; j < BL_MAX * SIZE; j++) {
      printf("%d ", CELL(i, j));
    }
    printf("\n");
  }
  printf("\n");

}