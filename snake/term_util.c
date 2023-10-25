#include <snake/term_util.h>

#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

struct termios orig_termios;
struct winsize sz;

void disable_raw_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_terminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_terminal);
    atexit(show_cursor);
    atexit(disable_alt_buffer);

    struct termios raw = orig_termios;
    cfmakeraw(&raw);
    // raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    // raw.c_oflag &= ~(OPOST);
    // raw.c_cflag |= (CS8);
    // raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // raw.c_cc[VMIN] = 0;
    // raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void print_escape_code(char* c) {
    printf("\33%s", c);
}

int get_terminal_width() {
    ioctl(1, TIOCGWINSZ, &sz);
    return sz.ws_col;
}

int get_terminal_height() {
    ioctl(1, TIOCGWINSZ, &sz);
    return sz.ws_row;
}

void hide_cursor() { printf("\33[?25l"); }

void show_cursor() { printf("\33[?25h"); }

void set_cursor(int row, int col) {
    printf("\33[%d;%dH", row, col);
}

void set_color(int color) {
    printf("\33[38;5;%dm", color);
}

void clear_screen() {
    print_escape_code("[2J");
}

void clear_current_line() {
    print_escape_code("[2K");
}

void clear_line(int line) {
    set_cursor(line,1);
    clear_current_line();
}

void enable_alt_buffer() {
    print_escape_code("[?1049h");
}

void disable_alt_buffer() {
    print_escape_code("[?1049l");
}
