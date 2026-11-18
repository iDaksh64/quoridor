#include <stdio.h>
#include "game.h"

int inside_board(int row, int col) {
    if (row >= 0 && row <= 8 && col >= 0 && col <= 8) return 1;
    return 0;
}

int possible_moving(int row, int column, int direction) {
    if (direction == 0) {
        if (row == 0) return 0;
        else if (wall_horizontal[row-1][column] == 1) return 0;
        else if (column > 0 && wall_horizontal[row-1][column-1] == 1) return 0;
    }
    else if (direction == 1) {
        if (row == 8) return 0;
        else if (wall_horizontal[row][column] == 1) return 0;
        else if (column > 0 && wall_horizontal[row][column-1] == 1) return 0;
    }
    else if (direction == 2) {
        if (column == 0) return 0;
        else if (wall_vertical[row][column-1] == 1) return 0;
        if (row > 0 && wall_vertical[row-1][column-1] == 1) return 0;
    }
    else if (direction == 3) {
        if (column == 8) return 0;
        else if (wall_vertical[row][column] == 1) return 0;
        else if (row > 0 && wall_vertical[row-1][column] == 1) return 0;
    }
    return 1;
}

int legal_move(int p, int row, int col) {
    int current_row, current_column, opponent_row, opponent_column;

    if (p == 0) {
        current_row = a_row;      current_column = a_col;
        opponent_row = b_row;     opponent_column = b_col;
    } else {
        current_row = b_row;      current_column = b_col;
        opponent_row = a_row;     opponent_column = a_col;
    }

    if (!inside_board(row, col)) return 0;
    if (row == opponent_row && col == opponent_column) return 0;

    /* Normal one-step moves */
    if (row == current_row - 1 && col == current_column)
        return possible_moving(current_row, current_column, 0);
    if (row == current_row + 1 && col == current_column)
        return possible_moving(current_row, current_column, 1);
    if (row == current_row && col == current_column - 1)
        return possible_moving(current_row, current_column, 2);
    if (row == current_row && col == current_column + 1)
        return possible_moving(current_row, current_column, 3);

    /* Jump: opponent directly above */
    if (opponent_row == current_row - 1 && opponent_column == current_column
        && possible_moving(current_row, current_column, 0)) {
        if (possible_moving(opponent_row, opponent_column, 0))
            return (row == opponent_row - 1 && col == opponent_column);
        if (possible_moving(opponent_row, opponent_column, 2) && row == opponent_row && col == opponent_column - 1) return 1;
        if (possible_moving(opponent_row, opponent_column, 3) && row == opponent_row && col == opponent_column + 1) return 1;
        return 0;
    }

    /* Jump: opponent directly below */
    if (opponent_row == current_row + 1 && opponent_column == current_column
        && possible_moving(current_row, current_column, 1)) {
        if (possible_moving(opponent_row, opponent_column, 1))
            return (row == opponent_row + 1 && col == opponent_column);
        if (possible_moving(opponent_row, opponent_column, 2) && row == opponent_row && col == opponent_column - 1) return 1;
        if (possible_moving(opponent_row, opponent_column, 3) && row == opponent_row && col == opponent_column + 1) return 1;
        return 0;
    }

    /* Jump: opponent directly left */
    if (opponent_row == current_row && opponent_column == current_column - 1
        && possible_moving(current_row, current_column, 2)) {
        if (possible_moving(opponent_row, opponent_column, 2))
            return (row == opponent_row && col == opponent_column - 1);
        if (possible_moving(opponent_row, opponent_column, 0) && row == opponent_row - 1 && col == opponent_column) return 1;
        if (possible_moving(opponent_row, opponent_column, 1) && row == opponent_row + 1 && col == opponent_column) return 1;
        return 0;
    }

    /* Jump: opponent directly right */
    if (opponent_row == current_row && opponent_column == current_column + 1
        && possible_moving(current_row, current_column, 3)) {
        if (possible_moving(opponent_row, opponent_column, 3))
            return (row == opponent_row && col == opponent_column + 1);
        if (possible_moving(opponent_row, opponent_column, 0) && row == opponent_row - 1 && col == opponent_column) return 1;
        if (possible_moving(opponent_row, opponent_column, 1) && row == opponent_row + 1 && col == opponent_column) return 1;
        return 0;
    }

    return 0;
}

int move(int p, int row, int column) {
    if (!legal_move(p, row, column)) {
        printf("Invalid move\n");
        return 0;
    }
    if (p == 0) {
        a_row = row;
        a_col = column;
    } else {
        b_row = row;
        b_col = column;
    }
    return 1;
}
