#ifndef GAME_H
#define GAME_H

/* ---------- 1. Globals (globals.c) ---------- */
/* wall_horizontal[r][c] / wall_vertical[r][c] = 1 if a wall is placed there */
extern int wall_horizontal[10][10], wall_vertical[10][10];
/* Pawn positions (0-indexed row/column) */
extern int a_row, a_col, b_row, b_col;
/* Remaining walls per player */
extern int walls_A, walls_B;
/* Goal rows: A must reach row 8, B must reach row 0 */
extern int win_A, win_B;

/* ---------- 2. Board (board.c) ---------- */
void print_board(void);

/* ---------- 3. Pawn movement (movement.c) ---------- */
/* direction: 0 = up, 1 = down, 2 = left, 3 = right */
int inside_board(int row, int col);
int possible_moving(int row, int column, int direction);
int legal_move(int p, int row, int col);
int move(int p, int row, int column);

/* ---------- 4. Path check (path.c) ---------- */
int reachable(int row, int column, int goal_row, int used[9][9]);
int possible_path_A(void);
int possible_path_B(void);

/* ---------- 5. Walls (walls.c) ---------- */
int overlapping_walls(int row, int column, char orientation);
int intersecting_walls(int row, int column, char orientation);
int wall(int p, int row, int column, char orientation);

/* ---------- 6. Winning (winning.c) ---------- */
/* Returns 1 (and prints the winner) if player p has reached the goal row */
int GameOver(int p);

#endif
