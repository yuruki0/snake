#include <stdbool.h>

#ifndef snake_board_h
#define snake_board_h

typedef enum TileState {occupied, unoccupied, apple} TileState;

typedef struct Board {
    enum TileState* tiles;
    int size;
} Board;

Board* board_init(int n);
void board_snake_start(Board* b);
enum TileState board_tile_state(Board* b, int x, int y);
void board_delete(Board* b);
void board_move_apple(Board* b);

#endif
