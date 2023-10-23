#include <snake/term_util.h>

#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disable_raw_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_terminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_terminal);

    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void print_escape_code(char* c) {
    printf("\33%s", c);
}
