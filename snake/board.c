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
}
TileState board_get_tile(Board* b, int x, int y) {
    return b->tiles[x + b->size * y];
}
void board_delete(Board* b) {
    free(b->tiles);
    free(b);
}
void board_move_apple(Board* b) {
    int i = rand() % (b->size * b->size);
    while (b->tiles[i] == occupied) {
        if (++i == b->size * b->size)
            i = 0;
    }
    b->tiles[i] = apple;
}
