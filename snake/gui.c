#include <stdlib.h>
#include <stdio.h>
#include <threads.h>

#include <unistd.h>

#include <snake/board.h>
#include <snake/gui.h>
#include <snake/term_util.h>

void printBoard(Board* b, int x, int y) {
    set_cursor(y, x);
    int j;
    printf("┏");
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┓");
    set_cursor(y + 1, x);
    printf("┃");
    for (int i = 0; i < b->size * b-> size; i++) {
        if (i % b->size == 0 && i != 0) {
            printf("┃");
            set_cursor(y + 1 + i / b->size, x);
            printf("┃");
        }
        TileState* tiles = b->tiles;
        if (tiles[i] == apple)
            printf("🍎");
        if (tiles[i] == unoccupied)
            printf("  ");
        if (tiles[i] == occupied)
            printf("██");
    }
    printf("┃");
    set_cursor(y + 1 + b->size, x);
    printf("┗");
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┛\r\n");
}
void printBoardCentered(Board* b);
