#include <stdio.h>
#include <string.h>
#include "game.h"

int main(void) {
    printf("Start Game!\n");
    printf("Write [move notation] OR write [wall notation orientation(H/V)]\n");
    a_row = 0;  a_col = 4;
    b_row = 8;  b_col = 4;

    char input[15], position[5], orientation[5];
    int moves = 0;
    int _continue = 1;
    int row, column;

    while (_continue == 1) {
        int p = moves % 2;
        print_board();
        printf("Walls left  A:%d  B:%d\n", walls_A, walls_B);
        printf("Player %c: ", p == 0 ? 'A' : 'B');

        scanf("%s", input);

        if (strcmp(input, "move") == 0) {
            scanf("%s", position);
            if (strlen(position) != 2 || position[1] < '1' || position[1] > '9'
                || position[0] < 'a' || position[0] > 'i') {
                printf("Invalid : wrong format or range\n");
            }
            else {
                column = position[0] - 'a';
                row = position[1] - '1';
                if (move(p, row, column) == 1) {
                    if (GameOver(p) == 1) {
                        print_board();
                        break;
                    }
                    moves++;
                }
            }
        }
        else if (strcmp(input, "wall") == 0) {
            scanf("%s", position);
            scanf("%s", orientation);
            if (strlen(position) != 2 || position[1] < '1' || position[1] > '8'
                || position[0] < 'a' || position[0] > 'h') {
                printf("Invalid : wrong format or range\n");
            }
            else {
                column = position[0] - 'a';
                row = position[1] - '1';
                if (wall(p, row, column, orientation[0]) == 1) moves++;
            }
        }
        else {
            printf("write move/wall\n");
        }
    }
    return 0;
}
