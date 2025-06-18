#include <stdio.h>
#define QUEUE_MAX_SIZE 100

typedef struct {
    int queue[QUEUE_MAX_SIZE];
    int size;
} Buffer;


void push(Buffer *buffer, int value) {
    if (buffer->size == QUEUE_MAX_SIZE) {
        return;
    }

    buffer->queue[buffer->size] = value;
    buffer->size++;
}

int pop(Buffer* buffer) {
    if (buffer->size == 0) {
        return 0;
    }

    int first_in_queue = buffer->queue[0];

    for (int i = 0; i < buffer->size - 1; i++) {
        buffer->queue[i] = buffer->queue[i+1];
    }

    buffer->queue[buffer->size] = 0;

    buffer->size--;
    return first_in_queue;
}

int size(Buffer *buffer) {
    return buffer->size;
}

int clear(Buffer *buffer) {
    buffer->size = 0;
    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        buffer->queue[i] = 0;
    }
}

void print_buffer(Buffer *buffer) {
    printf("Queue: ");
    for (int i = 0; i < buffer->size; i++) {
        printf("%d ", buffer->queue[i]);
    }
    printf("\n");
}

int main() {
    Buffer buffer;
    clear(&buffer);

    print_buffer(&buffer);

    push(&buffer, 5);
    push(&buffer, 6);
    push(&buffer, 7);
    print_buffer(&buffer);
    pop(&buffer);
    print_buffer(&buffer);

    clear(&buffer);
    print_buffer(&buffer);

    return 0;
}
