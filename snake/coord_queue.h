#ifndef coord_queue_h
#define coord_queue_h

typedef struct coord {
    int x, y;
} coord;

typedef struct coord_queue {
    coord* array;
    int head, tail, size;
} coord_queue;

coord_queue* coord_queue_init(int n);
void coord_queue_push(coord_queue* queue, coord coords);
coord coord_queue_pop(coord_queue* queue);

#endif
