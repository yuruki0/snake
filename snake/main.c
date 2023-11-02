#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#include <unistd.h>
#include <sys/ioctl.h>

#include <snake/term_util.h>
#include <snake/snake.h>

int main() {
    enable_raw_terminal();
    enable_alt_buffer();
    clear_screen();
    hide_cursor();

    snake_start(get_terminal_width() / 2 - 1);

    return 0;
}
