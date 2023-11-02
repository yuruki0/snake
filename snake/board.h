#include <stdbool.h>
#include <snake/coord_queue.h>

#ifndef snake_board_h
#define snake_board_h

typedef enum TileState {
    OCCUPIED,
    UNOCCUPIED,
    APPLE
} TileState;

typedef struct Board {
    enum TileState* tiles;
    int size;
} Board;

Board* board_init(int n);
void board_snake_start(Board* b);
enum TileState board_get_tile(Board* b, Coord c);
void board_set_tile(Board* b, Coord c, TileState t);
void board_delete(Board* b);
void board_move_apple(Board* b);
bool validate_coord(Board* b, Coord c);

#endif
