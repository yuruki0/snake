#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unity/unity.h>

#include <snake/snake.h>
#include <snake/board.h>
#include <snake/coord_queue.h>
#include <snake/input_queue.h>
#include <snake/gui.h>
#include <snake/term_util.h>
#include <snake/test_util.h>

bool debug;
int state;
int (*advance) (Board*, char, CoordQueue*);

int debug_advance_game_state(Board* b, char c, CoordQueue* cq) {
    printf("\nAdvancing.\n");
    state = advance_game_state(b, c, cq);
    printf("Board:\n");
    print_board_canonical(b);
    print_coord_queue(cq);
    return state;
}

void test_NoInputThreeSteps() {
    InputQueue* iq = input_queue_init(1, DOWN);
    Board* b = board_init(3);
    CoordQueue* snake = coord_queue_init(9);

    Coord init = (Coord) {0, 0};

    coord_queue_push(snake, init);
    board_set_tile(b, init, OCCUPIED);

    if (debug) {
        printf("====================\n");
        printf("Initial board state.\n");
        printf("Board:\n");
        print_board_canonical(b);
        print_coord_queue(snake);
    }

    state = advance(b, input_queue_pop(iq), snake);
    TEST_ASSERT(state == 0);
    TEST_ASSERT(board_get_tile(b, init) == UNOCCUPIED);
    TEST_ASSERT(board_get_tile(b, (Coord) {0, 1}) == OCCUPIED);

    state = advance(b, input_queue_pop(iq), snake);
    TEST_ASSERT(state == 0);
    TEST_ASSERT(board_get_tile(b, init) == UNOCCUPIED);
    TEST_ASSERT(board_get_tile(b, (Coord) {0, 1}) == UNOCCUPIED);
    TEST_ASSERT(board_get_tile(b, (Coord) {0, 2}) == OCCUPIED);

    state = advance(b, input_queue_pop(iq), snake);
    TEST_ASSERT(state == 1);
    
    input_queue_delete(iq);
    board_delete(b);
    coord_queue_delete(snake);
}

void test_TwoSnakeFiveSteps() {
    InputQueue* iq = input_queue_init(5, RIGHT);
    Board* b = board_init(3);
    CoordQueue* snake = coord_queue_init(9);

    char keys[4] = {DOWN, RIGHT, UP, RIGHT};
    for (int i = 0; i < 4; i++)
        input_queue_push(iq, keys[i]);

    coord_queue_push(snake, (Coord) {0, 2});
    board_set_tile(b, (Coord) {0, 2}, OCCUPIED);
    coord_queue_push(snake, (Coord) {0, 1});
    board_set_tile(b, (Coord) {0, 1}, OCCUPIED);
    int o = OCCUPIED;
    int u = UNOCCUPIED;

    TileState expected[4][9] = {
        {
            u, u, u,
            o, o, u,
            u, u, u,
        },
        {
            u, u, u,
            u, o, u,
            u, o, u,
        },
        {
            u, u, u,
            u, u, u,
            u, o, o,
        },
        {
            u, u, u,
            u, u, o,
            u, u, o,
        }
    };

    if (debug) {
        printf("====================\n");
        printf("Initial board state.\n");
        printf("Board:\n");
        print_board_canonical(b);
        print_coord_queue(snake);
    }

    int state;
    for (int i = 0; i < 5; i++) {
        state = advance(b, input_queue_pop(iq), snake);
        if (i == 4) {
            TEST_ASSERT(state == 1);
            continue;
        }
        TEST_ASSERT(state == 0);
        for (int j = 0; j < 9; j++) {
            TEST_ASSERT(b->tiles[j] == expected[i][j]);
        }
    }

    input_queue_delete(iq);
    board_delete(b);
    coord_queue_delete(snake);
}

void runAllTests() {
    RUN_TEST(test_NoInputThreeSteps);
    RUN_TEST(test_TwoSnakeFiveSteps);
}

void setUp() {}
void tearDown() {}
int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        debug = true;
        advance = &debug_advance_game_state;
        clear_screen();
    } else {
        advance = &advance_game_state;
    }
    UNITY_BEGIN();
    runAllTests();
    UNITY_END();
}
