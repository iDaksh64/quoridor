#include <stdio.h>
#include "game.h"

int GameOver(int p) {
    if (p == 0) {
        if (a_row == 8) {
            printf("A won the game!!\n");
            return 1;
        }
    }
    else if (p == 1) {
        if (b_row == 0) {
            printf("B won the game!!\n");
            return 1;
        }
    }
    return 0;
}
