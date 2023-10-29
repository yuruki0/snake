#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#include <unistd.h>
#include <sys/ioctl.h>

#include <snake/term_util.h>

void centeredText(char* s) {
    set_cursor(
            get_terminal_height() / 2,
            get_terminal_width() / 2 - (int) strlen(s) / 2
            );
    printf("%s\r", s);
    fflush(stdout);
}

int helloEverynyan(void* arg) {
    for (int i = 0; i <= 255; i++) {
        set_color(i);
        centeredText("Hello everynyan.");
        thrd_sleep(&(struct timespec){.tv_nsec=33333333}, NULL);
        clear_line(get_terminal_height() / 2);
        if (i == 255) i = 0;
    }
    return 0;
}

int main() {
    enable_raw_terminal();
    enable_alt_buffer();
    clear_screen();
    hide_cursor();

    char* info = "Press Q to quit.";
    set_cursor(
            get_terminal_height() / 2 + 2,
            get_terminal_width() / 2 - (int) strlen(info) / 2
            );
    printf("%s", info);

    thrd_t hallo;
    thrd_create(&hallo, helloEverynyan, NULL);

    char c = '1';
    while (c != 'q') {
        read(STDIN_FILENO, &c, 1);
        if (c == 'e') {
            printf("\r\n");
            for (int i = 0; i < get_terminal_width(); i++) {
                printf("#");
            }
            printf("\r");
            fflush(stdout);
        }
    }

    clear_current_line();
    clear_line(get_terminal_height() / 2 + 2);
    disable_alt_buffer();
    set_color(3);
    printf("Farewell everynyan...\r\n");
    return 0;
}
