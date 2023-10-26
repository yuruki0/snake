#ifndef snake_input_queue_h
#define snake_input_queue_h

typedef struct InputQueue {
    char* array;
    int head, tail, size, capacity;
} InputQueue;

InputQueue* input_queue_init(int capacity, char initial);
void input_queue_delete(InputQueue* iq);
void input_queue_push(InputQueue* iq, char c);
char input_queue_pop(InputQueue* iq);

#endif
