#include <stdio.h>
#include <string.h>

int wall_horizontal[10][10], wall_vertical[10][10];
int a_row, a_col, b_row, b_col;
int walls_A = 10, walls_B = 10;
int win_A = 8, win_B = 0;

void print_board() {
    int i, j;

    printf("\n     a   b   c   d   e   f   g   h   i\n");

    for (i = 0; i < 9; i++) {
        printf("  %d ", i + 1);

        for (j = 0; j < 9; j++) {
            if (a_row == i && a_col == j)
                printf(" %c ", 'A');
            else if (b_row == i && b_col == j)
                printf(" %c ", 'B');
            else
                printf(" . ");

            if (j < 8) {
                if (wall_vertical[i][j]) printf("|");
                else printf(" ");
            }
        }

        printf("\n");

        if (i < 8) {
            printf("    ");

            for (j = 0; j < 9; j++) {
                if (wall_horizontal[i][j]) printf("---");
                else printf("   ");
                if (j < 8) printf(" ");
            }

            printf("\n");
        }
    }

    printf("\n");
}

int possible_moving(int row, int column, int direction) {
    if (direction == 0) {
        if (row == 0) return 0;
        if (wall_horizontal[row-1][column] == 1) return 0;
    }
    else if (direction == 1) {
        if (row == 8) return 0;
        if (wall_horizontal[row][column] == 1) return 0;
    }
    else if (direction == 2) {
        if (column == 0) return 0;
        if (wall_vertical[row][column-1] == 1) return 0;
    }
    else if (direction == 3){
        if (column == 8) return 0;
        if (wall_vertical[row][column] == 1) return 0;
    }
    return 1;
}


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

int possible_path_A() {
    int visited[9][9] = {0};
    return reachable(a_row, a_col, win_A, visited);
}
int possible_path_B() {
    int visited[9][9] = {0};
    return reachable(b_row, b_col, win_B, visited);
}


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

int wall(int p, int row, int column, char orientation) {
    int flag = 0, correct = 0;

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
    }

        
        else {
        if (orientation == 'H') {
            if (wall_horizontal[row][column] == 1) {
                printf("Invalid Input\n");
                return 0;
            }
            wall_horizontal[row][column] = 1;
            if (possible_path_A() == 0 || possible_path_B() == 0) {
                wall_horizontal[row][column] = 0;
                printf("Invalid Input\n");
                return 0;
            }
        }
        else {
            if (wall_vertical[row][column] == 1) {
                printf("Invalid Input\n");
                return 0;
            }
            wall_vertical[row][column] = 1;
            if (possible_path_A() == 0 || possible_path_B() == 0) {
                wall_vertical[row][column] = 0;
                printf("Invalid Input\n");
                return 0;
            }
        }
        if (p == 0) {
            walls_A--;
        }
        else {
            walls_B--;
        }
        correct = 1;
    }

    return correct;
}

int main() {
    printf("Start Game!\n");
    printf("Write [move notation] OR write [wall notation orientation(H/V)]\n");
    a_row = 0;  a_col = 4; b_row = 8;  b_col = 4;
    
    char input[15], position[5], orientation[5];
    int moves = 0; char player;
    int _continue = 1;
    int row, column;
    
    while (_continue == 1) {
        print_board();
        if (moves % 2 == 0)
            player = 'A';
        else
            player = 'B';
        printf("Player %c:", player);
        
        scanf("%s", input);
        
        if (strcmp(input, "move") == 0) {
            scanf("%s", position);
            if (strlen(position) != 2 || position[1] < '1' || position[1] > '9' || position[0] < 'a' || position[0] > 'i') {
                printf("Invalid : wrong format or range\n");
            }
            else {
                column = position[0] - 'a';
                row = position[1] - '1';

                if (move(moves % 2, row, column) == 1) moves++;
            }
        }

        else if (strcmp(input, "wall") == 0) {
            scanf("%s", position);
            scanf("%s", orientation);
            if (strlen(position) != 2 || position[1] < '1' || position[1] > '8' || position[0] < 'a' || position[0] > 'h') {
                printf("Invalid : wrong format or range\n");
            }
            else {
                column = position[0] - 'a';
                row = position[1] - '1';

                if (wall(moves % 2, row, column, orientation[0]) == 1) moves++;
            }
        }

        else {
            printf("write move/wall\n");
        }
    }

    return 0;
}