// #include <stddef.h>
#include <stdlib.h>
// #include <string.h>

typedef struct Coordinate {
    int x, y;
} Coordinate;

typedef struct SnakeQueue {
    Coordinate* array;
    int head, tail, size;
} SnakeQueue;

SnakeQueue* snake_init(int n) {
    SnakeQueue* newSnake = malloc(sizeof(SnakeQueue));
    newSnake->array = malloc(n * sizeof(Coordinate));
    newSnake->size = n;
    newSnake->head = 0;
    newSnake->tail = 0;
    return newSnake;
}
void snake_push(SnakeQueue* queue, Coordinate coords) {
    queue->array[queue->head] = coords;
    queue->head += 1;
    if (queue->head >= queue->size)
        queue->head = 0;
}
Coordinate snake_pop(SnakeQueue* queue) {
    Coordinate coords = queue->array[queue->tail];
    queue->tail += 1;
    if (queue->tail >= queue->size)
        queue->tail = 0;
    return coords;
}
