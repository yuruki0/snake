#include <stdlib.h>
#include <time.h>

#include <unity/unity.h>
#include <snake/coord_queue.h>

void test_OneItemRandomUnseeded(void) {
    CoordQueue* cq = coord_queue_init(1);

    srand(1);
    int x = rand();
    int y = rand();

    coord_queue_push(cq, (Coord) { x, y } );
    TEST_ASSERT(coord_queue_peek_back(cq).x == x);
    TEST_ASSERT(coord_queue_peek_back(cq).y == y);
    Coord c = coord_queue_pop(cq);

    TEST_ASSERT(c.x == x);
    TEST_ASSERT(c.y == y);

    coord_queue_delete(cq);
}

void test_OneItemRandomSeeded(void) {
    CoordQueue* cq = coord_queue_init(1);

    srand(time(NULL));
    int x = rand();
    int y = rand();

    coord_queue_push(cq, (Coord) { x, y } );
    TEST_ASSERT(coord_queue_peek_back(cq).x == x);
    TEST_ASSERT(coord_queue_peek_back(cq).y == y);
    Coord c = coord_queue_pop(cq);

    TEST_ASSERT(c.x == x);
    TEST_ASSERT(c.y == y);

    coord_queue_delete(cq);
}

void test_FiveItemsFullRandomUnseeded(void) {
    CoordQueue* cq = coord_queue_init(5);

    int xa[5];
    int ya[5];

    srand(1);

    for (int i = 0; i < 5; i++) {
        xa[i] = rand();
        ya[i] = rand();
        coord_queue_push(cq, (Coord) { xa[i], ya[i] } );
        TEST_ASSERT(coord_queue_peek_back(cq).x == xa[i]);
        TEST_ASSERT(coord_queue_peek_back(cq).y == ya[i]);
    }

    for (int i = 0; i < 5; i++) {
        Coord c = coord_queue_pop(cq);
        TEST_ASSERT(c.x == xa[i]);
        TEST_ASSERT(c.y == ya[i]);
    }

    coord_queue_delete(cq);
}
void test_ThreeItemsLoopRandomUnseeded(void) {
    CoordQueue* cq = coord_queue_init(5);

    int xa[3];
    int ya[3];

    srand(1);

    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 3; i++) {
            xa[i] = rand();
            ya[i] = rand();
            coord_queue_push(cq, (Coord) { xa[i], ya[i] } );
            TEST_ASSERT(coord_queue_peek_back(cq).x == xa[i]);
            TEST_ASSERT(coord_queue_peek_back(cq).y == ya[i]);
        }
    
        for (int i = 0; i < 3; i++) {
            Coord c = coord_queue_pop(cq);
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
int main() {
    UNITY_BEGIN();
    coord_queue_runAllTests();
    UNITY_END();
}
