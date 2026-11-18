#include "game.h"

/* Depth-first search: can a pawn at (row, column) still reach goal_row? */
int reachable(int row, int column, int goal_row, int used[9][9]) {
    if (row == goal_row) {
        return 1;
    }
    used[row][column] = 1;

    if (possible_moving(row, column, 0) == 1 && used[row-1][column] == 0) {
        if (reachable(row-1, column, goal_row, used) == 1) {
            return 1;
        }
    }
    if (possible_moving(row, column, 1) == 1 && used[row+1][column] == 0) {
        if (reachable(row+1, column, goal_row, used) == 1) {
            return 1;
        }
    }
    if (possible_moving(row, column, 2) == 1 && used[row][column-1] == 0) {
        if (reachable(row, column-1, goal_row, used) == 1) {
            return 1;
        }
    }
    if (possible_moving(row, column, 3) == 1 && used[row][column+1] == 0) {
        if (reachable(row, column+1, goal_row, used) == 1) {
            return 1;
        }
    }
    return 0;
}

int possible_path_A(void) {
    int visited[9][9] = {0};
    return reachable(a_row, a_col, win_A, visited);
}

int possible_path_B(void) {
    int visited[9][9] = {0};
    return reachable(b_row, b_col, win_B, visited);
}
