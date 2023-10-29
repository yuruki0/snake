#include <stdlib.h>
#include <time.h>

#include <unity/unity.h>

#include "snake/input_queue.h"

void test_OneItemRepeatedPop() {
    srand(time(NULL));
    char c = (char) rand();
    InputQueue* iq = input_queue_init(3, c);
    for (int i = 0; i < 10; i++) {
        char c_pop = input_queue_pop(iq);
        TEST_ASSERT(c == c_pop);
    }
    input_queue_delete(iq);
}

void test_PushDuplicateItems() {
    srand(time(NULL));
    char c = (char) rand();
    InputQueue* iq = input_queue_init(5, c);
    for (int i = 0; i < 3; i++) {
        input_queue_push(iq, c);
    }
    TEST_ASSERT(iq->size == 1);
    for (int i = 0; i < 5; i++) {
        char c_pop = input_queue_pop(iq);
        TEST_ASSERT(c_pop == c);
        TEST_ASSERT(iq->size == 1);
    }
    input_queue_delete(iq);
}

void runAllTests() {
    RUN_TEST(test_OneItemRepeatedPop);
    RUN_TEST(test_PushDuplicateItems);
}

void setUp() {}
void tearDown() {}
int main() {
    UNITY_BEGIN();
    runAllTests();
    UNITY_END();
}
