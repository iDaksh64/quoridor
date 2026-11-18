#include <stdio.h>
#include <string.h>
#include "game.h"

int move(int p, int row, int column) {
    if (row < 0 || row > 8 || column < 0 || column > 8) {
        printf("Invalid : out of range\n");
        return 0;
    }
    

    int taken = 0;
    if (p == 0 && b_row == row && b_col == column) {
        taken = 1;
    }
    if (p == 1 && a_row == row && a_col == column) {
        taken = 1;
    }
    if (taken == 1) {
        printf("Position already taken\n");
        return 0;
    }
    
    int correct = 0;
    
    if (p == 0) {
        a_row = row;
        a_col = column;
    }
    else {
        b_row = row;
        b_col = column;
    }

    return 1;;
}
