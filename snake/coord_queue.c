#include <snake/coord_queue.h>

#include <stdlib.h>

CoordQueue* coord_queue_init(int n) {
    CoordQueue* newSnake = malloc(sizeof(CoordQueue));
    newSnake->array = malloc(n * sizeof(Coord));
    newSnake->capacity = n;
    newSnake->head = 0;
    newSnake->tail = 0;
    return newSnake;
}
void coord_queue_delete(CoordQueue* queue) {
    free(queue->array);
    free(queue);
}
void coord_queue_push(CoordQueue* queue, Coord coords) {
    queue->array[queue->head] = coords;
    queue->head += 1;
    if (queue->head >= queue->capacity)
        queue->head = 0;
}
Coord coord_queue_pop(CoordQueue* queue) {
    Coord coords = queue->array[queue->tail];
    queue->tail += 1;
    if (queue->tail >= queue->capacity)
        queue->tail = 0;
    return coords;
}

Coord coord_queue_peek_back(CoordQueue* queue) {
    if (queue->head == 0) return queue->array[queue->capacity - 1];
    else return queue->array[queue->head - 1];
}
Coord coord_queue_peek(CoordQueue* queue) {
    return queue->array[queue->tail];
}
