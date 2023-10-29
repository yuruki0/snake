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
TileState board_get_tile(Board* b, Coord c) {
    return b->tiles[c.x + b->size * c.y];
}
void board_set_tile(Board* b, Coord c, TileState t) {
    b->tiles[c.x + b->size * c.y] = t;
}
void board_delete(Board* b) {
    free(b->tiles);
    free(b);
}
void board_move_apple(Board* b) {
    int i = rand() % (b->size * b->size);
    while (b->tiles[i] != unoccupied) {
        if (++i == b->size * b->size)
            i = 0;
    }
    b->tiles[i] = apple;
}
bool validate_coord(Board* b, Coord* c) {
    if (c->x < 0)
        return false;
    if (c->x >= b->size)
        return false;
    if (c->y < 0)
        return false;
    if (c->y >= b->size)
        return false;
    return true;
}
