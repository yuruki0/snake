#include <snake/coord_queue.h>
#include <snake/input_queue.h>
#include <snake/board.h>

#ifndef snake_h
#define snake_h

enum input_keys {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd',
    QUIT = 'q'
};

void snake_start(int size);

int listen_inputs(void* args);

int advance_game_state(Board* b, char direction, CoordQueue* snake);

#endif
