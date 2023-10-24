#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/ioctl.h>

#include <snake/term_util.h>

int main() {
    enable_raw_terminal();

    struct winsize sz;
    ioctl(1, TIOCGWINSZ, &sz);

    char* hello = "My cursor is here.";

    print_escape_code("[2J");
    print_escape_code("[1;1H");
    printf("\33[%d;%dH", sz.ws_row/2, sz.ws_col/2 - (int)strlen(hello)/2);
    fflush(stdout);

    printf("%s\r", hello);
    fflush(stdout);

    char c = '1';
    while (c != 'q') {
        read(STDIN_FILENO, &c, 1);
    }

    print_escape_code("[2K");
    printf("\33[%d;%dH", sz.ws_row, 1);
    printf("Farewell...\r\n");
    return 0;
}
