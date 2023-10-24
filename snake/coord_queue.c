#include <snake/coord_queue.h>

#include <stdlib.h>

coord_queue* coord_queue_init(int n) {
    coord_queue* newSnake = malloc(sizeof(coord_queue));
    newSnake->array = malloc(n * sizeof(coord));
    newSnake->size = n;
    newSnake->head = 0;
    newSnake->tail = 0;
    return newSnake;
}
void coord_queue_delete(coord_queue* queue) {
    free(queue->array);
    free(queue);
}
void coord_queue_push(coord_queue* queue, coord coords) {
    queue->array[queue->head] = coords;
    queue->head += 1;
    if (queue->head >= queue->size)
        queue->head = 0;
}
coord coord_queue_pop(coord_queue* queue) {
    coord coords = queue->array[queue->tail];
    queue->tail += 1;
    if (queue->tail >= queue->size)
        queue->tail = 0;
    return coords;
}
