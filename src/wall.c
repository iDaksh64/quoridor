#include <stdio.h>
#include "game.h"

int overlapping_walls(int row, int column, char orientation) {
    if (orientation == 'H') {
        if ((column > 0 && wall_horizontal[row][column-1] == 1) || wall_horizontal[row][column] == 1 || wall_horizontal[row][column+1] == 1) {
            printf("invalid : wall overlaps\n");
            return 1;
        }
    }
    if (orientation == 'V') {
        if ((row > 0 && wall_vertical[row-1][column] == 1) || wall_vertical[row][column] == 1 || wall_vertical[row+1][column] == 1) {
            printf("invalid : wall overlaps\n");
            return 1;
        }
    }
    return 0;
}

int intersecting_walls(int row, int column, char orientation) {
    if (orientation == 'H') {
        if (wall_vertical[row][column] == 1) {
            printf("invalid : walls will intersect\n");
            return 1;
        }
    }
    else if (orientation == 'V') {
        if (wall_horizontal[row][column] == 1) {
            printf("invalid : walls will intersect\n");
            return 1;
        }
    }
    return 0;
}

int wall(int p, int row, int column, char orientation) {
    if (orientation != 'H' && orientation != 'V') {
        printf("invalid : orientation is H/V\n");
        return 0;
    }
    if ((p == 0 && walls_A == 0) || (p == 1 && walls_B == 0)) {
        printf("invalid : 0 walls left\n");
        return 0;
    }

    if (row < 0 || row > 7 || column < 0 || column > 7) {
        printf("invalid :  out of range\n");
        return 0;
    }
    if (overlapping_walls(row, column, orientation) == 1) {
        return 0;
    }
    if (intersecting_walls(row, column, orientation) == 1) {
        return 0;
    }

    if (orientation == 'H') {
        if (wall_horizontal[row][column] == 1) {
            printf("Invalid input\n");
            return 0;
        }
        wall_horizontal[row][column] = 1;
        if (possible_path_A() == 0 || possible_path_B() == 0) {
            wall_horizontal[row][column] = 0;
            printf("Invalid input\n");
            return 0;
        }
    }
    else {
        if (wall_vertical[row][column] == 1) {
            printf("Invalid input\n");
            return 0;
        }
        wall_vertical[row][column] = 1;
        if (possible_path_A() == 0 || possible_path_B() == 0) {
            wall_vertical[row][column] = 0;
            printf("Invalid input\n");
            return 0;
        }
    }

    if (p == 0) {
        walls_A--;
    }
    else {
        walls_B--;
    }
    return 1;
}
