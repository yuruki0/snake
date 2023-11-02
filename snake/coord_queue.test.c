#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <unity/unity.h>
#include <snake/coord_queue.h>
#include <snake/test_util.h>

bool debug = false;
void (*push) (CoordQueue*, Coord);
CoordQueue* (*init) (int);
Coord (*pop) (CoordQueue*);

void debug_push(CoordQueue* cq, Coord coord) {
    printf("Pushing (%d, %d).\n", coord.x, coord.y);
    coord_queue_push(cq, coord);
    print_coord_queue(cq);
}

CoordQueue* debug_init(int n) {
    CoordQueue* cq = coord_queue_init(n);
    printf("==========================\n");
    printf("Initial CoordQueue values:");
    print_coord_queue(cq);
    return cq;
}

Coord debug_pop(CoordQueue* cq) {
    Coord coord = coord_queue_pop(cq);
    printf("Popped (%d, %d).\n", coord.x, coord.y);
    print_coord_queue(cq);
    return coord;
}

void test_OneItemRandomUnseeded(void) {
    CoordQueue* cq = init(1);

    srand(1);
    int x = rand();
    int y = rand();

    push(cq, (Coord) { x, y } );
    TEST_ASSERT(coord_queue_peek_back(cq).x == x);
    TEST_ASSERT(coord_queue_peek_back(cq).y == y);
    Coord c = pop(cq);

    TEST_ASSERT(c.x == x);
    TEST_ASSERT(c.y == y);

    coord_queue_delete(cq);
}

void test_OneItemRandomSeeded(void) {
    CoordQueue* cq = init(1);

    srand(time(NULL));
    int x = rand();
    int y = rand();

    push(cq, (Coord) { x, y } );
    TEST_ASSERT(coord_queue_peek_back(cq).x == x);
    TEST_ASSERT(coord_queue_peek_back(cq).y == y);
    Coord c = pop(cq);

    TEST_ASSERT(c.x == x);
    TEST_ASSERT(c.y == y);

    coord_queue_delete(cq);
}

void test_FiveItemsFullRandomUnseeded(void) {
    CoordQueue* cq = init(5);

    int xa[5];
    int ya[5];

    srand(1);

    for (int i = 0; i < 5; i++) {
        xa[i] = rand();
        ya[i] = rand();
        push(cq, (Coord) { xa[i], ya[i] } );
        TEST_ASSERT(coord_queue_peek_back(cq).x == xa[i]);
        TEST_ASSERT(coord_queue_peek_back(cq).y == ya[i]);
    }

    for (int i = 0; i < 5; i++) {
        Coord c = pop(cq);
        TEST_ASSERT(c.x == xa[i]);
        TEST_ASSERT(c.y == ya[i]);
    }

    coord_queue_delete(cq);
}
void test_ThreeItemsLoopRandomUnseeded(void) {
    CoordQueue* cq = init(5);

    int xa[3];
    int ya[3];

    srand(1);

    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 3; i++) {
            xa[i] = rand();
            ya[i] = rand();
            push(cq, (Coord) { xa[i], ya[i] } );
            TEST_ASSERT(coord_queue_peek_back(cq).x == xa[i]);
            TEST_ASSERT(coord_queue_peek_back(cq).y == ya[i]);
        }
    
        for (int i = 0; i < 3; i++) {
            Coord c = pop(cq);
            TEST_ASSERT(c.x == xa[i]);
            TEST_ASSERT(c.y == ya[i]);
        }
    }

    coord_queue_delete(cq);
}

void coord_queue_runAllTests() {
    RUN_TEST(test_OneItemRandomUnseeded);
    RUN_TEST(test_OneItemRandomSeeded);
    RUN_TEST(test_FiveItemsFullRandomUnseeded);
    RUN_TEST(test_ThreeItemsLoopRandomUnseeded);
}

void setUp() {}
void tearDown() {}
int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        debug = true;
        push = &debug_push;
        init = &debug_init;
        pop = &debug_pop;
    } else {
        push = &coord_queue_push;
        init = &coord_queue_init;
        pop = &coord_queue_pop;
    }
    UNITY_BEGIN();
    coord_queue_runAllTests();
    UNITY_END();
}
