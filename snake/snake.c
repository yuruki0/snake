#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>

#include <unistd.h>

#include <snake/snake.h>
#include <snake/board.h>
#include <snake/input_queue.h>
#include <snake/coord_queue.h>

void snake_start(int size) {
    while (true) {
    }
}

int listen_inputs(void* args) {
    struct args_s { InputQueue* inputs; mtx_t* mutex; }* input_args;
    input_args = (struct args_s*) args;

    char c = '\0';
    while (1) {
        read(STDIN_FILENO, &c, 1);
        switch (c) {
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                mtx_lock(input_args->mutex);
                input_queue_push(input_args->inputs, c);
                mtx_unlock(input_args->mutex);
                break;
            case QUIT:
                exit(0);
                break;
        }
    }
    
    return 0;
}

int advance_game_state(Board* b, InputQueue* iq, CoordQueue* snake) {
    char direction = input_queue_pop(iq);
    Coord coord = coord_queue_peek_back(snake);
    switch (direction) {
        case UP:
            coord.y--;
            break;
        case LEFT:
            coord.x--;
            break;
        case DOWN:
            coord.y++;
            break;
        case RIGHT:
            coord.x++;
            break;
    }
    if (!validate_coord(b, coord))
        return 1;

    TileState next = board_get_tile(b, coord);

    Coord prev = coord_queue_peek(snake);

    switch (next) {
        case OCCUPIED:
            return 1;
            break;
        case UNOCCUPIED:
            coord_queue_push(snake, coord);
            coord_queue_pop(snake);
            board_set_tile(b, prev, UNOCCUPIED);
            break;
        case APPLE:
            coord_queue_push(snake, coord);
            board_move_apple(b);
            break;
    }

    board_set_tile(b, coord, OCCUPIED);

    return 0;
}
