#include <asm/termbits.h>
#include <sys/ioctl.h>

#include <unity/unity.h>

#include <snake/board.h>

void printBoard(Board* b) {
    int j;
    printf("┏");
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┓\n┃");
    for (int i = 0; i < b->size * b-> size; i++) {
        if (i % b->size == 0 && i != 0)
            printf("┃\n┃");
        TileState* tiles = b->tiles;
        if (tiles[i] == apple)
            printf("🍎");
        if (tiles[i] == unoccupied)
            printf("  ");
        if (tiles[i] == occupied)
            printf("██");
    }
    printf("┃\n┗");
    for (j = 0; j < b->size; j++)
        printf("━━");
    printf("┛");
    printf("\n");
}

void setUp() {}
void tearDown() {}
int main() {
    struct winsize sz;
    ioctl(1, TIOCGWINSZ, &sz);

    printf("\nPrinting a random initialized board.\n");
    Board* b = board_init(sz.ws_col/2 - 1);
    board_snake_start(b);
    printBoard(b);
}
