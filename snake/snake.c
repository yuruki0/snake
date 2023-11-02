#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>

#include <unistd.h>

#include <snake/snake.h>
#include <snake/board.h>
#include <snake/gui.h>
#include <snake/input_queue.h>
#include <snake/coord_queue.h>

void snake_start(int size) {
    Board* b = board_init(size);
    CoordQueue* snake = coord_queue_init(size*size);
    InputQueue* iq = input_queue_init(10, RIGHT);

    coord_queue_push(snake, (Coord) {0, 0});
    board_set_tile(b, (Coord) {0, 0}, OCCUPIED);
    board_move_apple(b);

    bool listen = true;
    mtx_t mtx;
    mtx_init(&mtx, mtx_plain);

    struct args_s { InputQueue* inputs; mtx_t* mutex; bool* listen; } input_args;
    input_args.inputs = iq;
    input_args.mutex = &mtx;
    input_args.listen = &listen;
    thrd_t input_listener;
    thrd_create(&input_listener, listen_inputs, &input_args);

    int state;
    while (true) {
        printBoard(b, 1, 1);
        thrd_sleep(&(struct timespec){.tv_nsec=133333333}, NULL);
        mtx_lock(&mtx);
        char c = input_queue_pop(iq);
        state = advance_game_state(b, c, snake);
        if (state == 1) break;
        mtx_unlock(&mtx);
    }
    mtx_lock(&mtx);
    listen = false;
    mtx_unlock(&mtx);
}

int listen_inputs(void* args) {
    struct args_s { InputQueue* inputs; mtx_t* mutex; bool* listen; }* input_args;
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
                if (*(input_args->listen))
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

int advance_game_state(Board* b, char direction, CoordQueue* snake) {
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
