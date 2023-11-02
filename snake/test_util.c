#include <stdio.h>

#include <snake/coord_queue.h>
#include <snake/board.h>

#include <snake/test_util.h>

void print_coord_queue(CoordQueue* cq) {
    printf("CoordQueue:\n");
    for (int i = 0; i < cq->capacity; i++) {
        printf("  [%d]: (%d,%d)", i, cq->array[i].x, cq->array[i].y);
        if (i == cq->head)
            printf(" 😯");
        if (i == cq->tail)
            printf(" 🐒");
        printf("\n");
    }
}

void print_board_canonical(Board*b) {
    printf("┏");
    int j;
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┓\n┃");
    TileState* tile;
    for (int i = 0; i < b->size * b-> size; i++) {
        if (i % b->size == 0 && i != 0)
            printf("┃\n┃");
        tile = b->tiles;
        if (tile[i] == APPLE)
            printf("🍎");
        if (tile[i] == UNOCCUPIED)
            printf("  ");
        if (tile[i] == OCCUPIED)
            printf("██");
    }
    printf("┃\n┗");
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┛\n");
}
