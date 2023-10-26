#ifndef snake_coord_queue_h
#define snake_coord_queue_h

typedef struct coord {
    int x, y;
} coord;

typedef struct coord_queue {
    coord* array;
    int head, tail, capacity;
} coord_queue;

coord_queue* coord_queue_init(int n);
void coord_queue_delete(coord_queue* queue);
void coord_queue_push(coord_queue* queue, coord coords);
coord coord_queue_pop(coord_queue* queue);

#endif
