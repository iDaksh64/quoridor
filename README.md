# Quoridor (C, terminal)

A two-player, text-based version of the board game Quoridor written in C.
Player **A** starts at the top and must reach the bottom row; player **B** starts at the bottom and must reach the top row. Each player has 10 walls to slow the opponent down — but a wall may never completely block a player's path to their goal.

## Build & run

```bash
make        # builds ./quoridor
make run    # builds and starts the game
make clean  # removes build output
```

Or without make:

```bash
gcc -Wall -Wextra -std=c99 -o quoridor main.c globals.c board.c movement.c path.c walls.c winning.c
./quoridor
```

## How to play

Players alternate turns (A first). On your turn enter one of:

| Command | Meaning | Example |
|---|---|---|
| `move <cell>` | Move your pawn to an adjacent cell (jumping over the opponent is supported) | `move e2` |
| `wall <cell> <H/V>` | Place a horizontal or vertical wall at that position | `wall d4 H` |

- Columns are letters `a`–`i`, rows are numbers `1`–`9`.
- Wall positions use `a`–`h` and `1`–`8`.
- Invalid moves/walls (overlapping, intersecting, out of range, or blocking all paths) are rejected and you retry.

## Project structure

| File | Responsibility |
|---|---|
| `globals.h/.c` | Shared game state: wall grids, pawn positions, walls left, goal rows |
| `board.h/.c` | `print_board` — renders the board and walls |
| `movement.h/.c` | Pawn movement: bounds check, wall-blocking check, legal moves & jumps |
| `path.h/.c` | Path check (DFS) ensuring each player can still reach their goal |
| `walls.h/.c` | Wall placement rules: overlap, intersection, range, path validation |
| `winning.h/.c` | Win detection |
| `main.c` | Input parsing and main game loop |
| `Makefile` | Build rules |

## License

Add a license of your choice before publishing.
