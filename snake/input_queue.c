#include <stdlib.h>

#include <snake/input_queue.h>
#include <snake/snake.h>

InputQueue* input_queue_init(int capacity, char initial) {
    InputQueue* iq = malloc(sizeof(InputQueue));
    iq->array = malloc(4 * sizeof(char));
    iq->array[0] = initial;
    iq->capacity = capacity;
    iq->size = 1;
    iq->head = 0;
    iq->tail = 0;
    return iq;
}
void input_queue_delete(InputQueue* iq) {
    free(iq->array);
    free(iq);
}
void input_queue_push(InputQueue* iq, char c) {
    if (iq->size == iq->capacity) return;
    if (iq->array[iq->head] == c) return;

    switch (iq->array[iq->head]) {
        case UP:
            if (c == DOWN) return;
            break;
        case DOWN:
            if (c == UP) return;
            break;
        case LEFT:
            if (c == RIGHT) return;
            break;
        case RIGHT:
            if (c == LEFT) return;
            break;
    }

    iq->size += 1;
    iq->head += 1;
    if (iq->head >= iq->capacity)
        iq->head = 0;
    iq->array[iq->head] = c;
}
char input_queue_pop(InputQueue* iq) {
    char c = iq->array[iq->tail];
    if (iq->size <= 1) return c;

    iq->size -= 1;
    iq->tail += 1;

    if (iq->tail >= iq->capacity)
        iq->tail = 0;

    return c;
}
