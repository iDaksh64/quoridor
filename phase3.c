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
                if (wall_vertical[i][j] || (i > 0 && wall_vertical[i-1][j])) printf("|"); 
                else printf(" ");
            }
        }

        printf("\n");

        if (i < 8) {
            printf("    ");

            for (j = 0; j < 9; j++) {
                if (wall_horizontal[i][j] || (j > 0 && wall_horizontal[i][j-1])) printf("---");
                else printf("   ");

    if (j < 8) {
        if (wall_horizontal[i][j]) printf("-");
        else printf(" ");
}
            }
            printf("\n");
        }
    }
    printf("\n");
}

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

    if (row == current_row - 1 && col == current_column) {
        return possible_moving(current_row, current_column, 0);}
    if (row == current_row + 1 && col == current_column) {
        return possible_moving(current_row, current_column, 1);}
    if (row == current_row && col == current_column - 1) {
        return possible_moving(current_row, current_column, 2);}
    if (row == current_row && col == current_column + 1) {
        return possible_moving(current_row, current_column, 3);}

    
    if (opponent_row == current_row - 1 && opponent_column == current_column && possible_moving(current_row, current_column, 0)) {
        if (possible_moving(opponent_row, opponent_column, 0)) {
            return (row == opponent_row - 1 && col == opponent_column);}
        if (possible_moving(opponent_row, opponent_column, 2) && row == opponent_row && col == opponent_column - 1) return 1;
        if (possible_moving(opponent_row, opponent_column, 3) && row == opponent_row && col == opponent_column + 1) return 1;
        return 0;
    }

    
    if (opponent_row == current_row + 1 && opponent_column == current_column  && possible_moving(current_row, current_column, 1)) {
        if (possible_moving(opponent_row, opponent_column, 1))
            return (row == opponent_row + 1 && col == opponent_column);
        if (possible_moving(opponent_row, opponent_column, 2) && row == opponent_row && col == opponent_column - 1) return 1;
        if (possible_moving(opponent_row, opponent_column, 3) && row == opponent_row && col == opponent_column + 1) return 1;
        return 0;
    }

    
    if (opponent_row == current_row && opponent_column == current_column - 1 && possible_moving(current_row, current_column, 2)) {
        if (possible_moving(opponent_row, opponent_column, 2)) {
            return (row == opponent_row && col == opponent_column - 1);}
        if (possible_moving(opponent_row, opponent_column, 0) && row == opponent_row - 1 && col == opponent_column) return 1;
        if (possible_moving(opponent_row, opponent_column, 1) && row == opponent_row + 1 && col == opponent_column) return 1;
        return 0;
    }

    
    if (opponent_row == current_row && opponent_column == current_column + 1 && possible_moving(current_row, current_column, 3)) {
        if (possible_moving(opponent_row, opponent_column, 3)) {
            return (row == opponent_row && col == opponent_column + 1);}
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


int GameOver (int p){
    if (p == 0) {
        if (a_row == 8) {
            printf("A won the game!!\n");
            return 1;
        }
    }
    else if (p ==1) {
        if (b_row == 0) {
            printf("B won the game!!\n");
            return 1;
        }
    }
    return 0;
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
            if (wall(p, row, column, (orientation[0])) == 1) moves++;
        }
    }
    else {
        printf("write move/wall\n");
    }
}
    return 0;
}