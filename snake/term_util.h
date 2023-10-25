#ifndef snake_term_util_h
#define snake_term_util_h

void disable_raw_terminal();

void enable_raw_terminal();

void print_escape_code(char* c);

int get_terminal_width();

int get_terminal_height();

void hide_cursor();

void show_cursor();

void set_cursor(int row, int col);

void set_color(int color);

void clear_screen();

void clear_current_line();

void clear_line(int line);

void enable_alt_buffer();

void disable_alt_buffer();

#endif
