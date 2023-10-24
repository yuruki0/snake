#include <snake/board.h>

#include <stdlib.h>
#include <time.h>

Board* board_init(int n) {
    Board* b = malloc(sizeof(Board));
    b->size = n;
    b->tiles = malloc(sizeof(TileState) * n * n);
    for (int i = 0; i < n * n; i++)
        b->tiles[i] = unoccupied;
    return b;
}
void board_snake_start(Board* b) {
    srand(time(NULL));
    int i_apple = (int) (rand() % (b->size * b->size));

    b->tiles[i_apple] = apple;
}
TileState board_get_tile(Board* b, int x, int y) {
    return b->tiles[x + b->size * y];
}
void board_delete(Board* b) {
}
