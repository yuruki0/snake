#ifndef snake_coord_queue_h
#define snake_coord_queue_h

typedef struct coord {
    int x, y;
} Coord;

typedef struct coord_queue {
    Coord* array;
    int head, tail, capacity;
} CoordQueue;

CoordQueue* coord_queue_init(int n);
void coord_queue_delete(CoordQueue* queue);
void coord_queue_push(CoordQueue* queue, Coord coords);
Coord coord_queue_pop(CoordQueue* queue);
Coord coord_queue_peek_back(CoordQueue* queue);
Coord coord_queue_peek(CoordQueue* queue);

#endif
