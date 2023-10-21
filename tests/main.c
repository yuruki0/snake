#include <unity/unity.h>
#include <snake/coord_queue.test.c>

void setUp() {}
void tearDown() {}
int main() {
    UNITY_BEGIN();
    coord_queue_runAllTests();
    UNITY_END();
}
