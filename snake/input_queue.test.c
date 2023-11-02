#include <stdlib.h>
#include <time.h>

#include <unity/unity.h>

#include <snake/input_queue.h>

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

void test_FullQueue() {
    srand(time(NULL));
    char c[5];
    c[0] = (char) rand();
    InputQueue* iq = input_queue_init(5, c[0]);
    for (int i = 1; i < 5; i++) {
        c[i] = (char) rand();
        input_queue_push(iq, c[i]);
    }
    TEST_ASSERT(iq->size == 5);
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT(iq->size == 5 - i);
        char c_pop = input_queue_pop(iq);
        TEST_ASSERT(c_pop == c[i]);
    }
    input_queue_delete(iq);
}

void runAllTests() {
    RUN_TEST(test_OneItemRepeatedPop);
    RUN_TEST(test_PushDuplicateItems);
    RUN_TEST(test_FullQueue);
}

void setUp() {}
void tearDown() {}
int main() {
    UNITY_BEGIN();
    runAllTests();
    UNITY_END();
}
