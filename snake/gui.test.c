#include <asm/termbits.h>
#include <sys/ioctl.h>

#include <unity/unity.h>

#include <snake/board.h>
#include <snake/term_util.h>
#include <snake/gui.h>

void setUp() {}
void tearDown() {}
int main() {
    printf("\nPrinting a random initialized board.\n");
    Board* b = board_init(get_terminal_width() / 2 - 1);
    board_snake_start(b);
    board_move_apple(b);
    clear_screen();
    printBoard(b, 1, 1);
}
