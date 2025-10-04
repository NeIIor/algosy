#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue {
    void* data;
    size_t elem_size;
    size_t head;
    size_t tail;
    size_t size;
    size_t capacity;
};

struct queue *queue_new(size_t elem_size) {
    if (!elem_size) return NULL;

    struct queue* q = malloc(sizeof(struct queue));
    if (!q) return NULL;

    q->elem_size = elem_size;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->capacity = 8;

    q->data = malloc(q->capacity * q->elem_size);
    if (!q->data) {
        free(q);
        return NULL;
    }

    return q;
}

int queue_push(struct queue *q, const void *elem) {
    if (!q || !elem) return 1;

    if (q->size >= q->capacity) {
        size_t new_capacity = q->capacity * 2;
        void* new_data = malloc(new_capacity * q->elem_size);
        if (!new_data) return 1;

        for (size_t i = 0; i < q->size; ++i) {
            size_t src_index = (q->head + i) % q->capacity;
            char* dst = (char*)new_data + i * q->elem_size;
            char* src = (char*)q->data + src_index * q->elem_size;
            memcpy(dst, src, q->elem_size);
        }

        free(q->data);
        q->data = new_data;
        q->capacity = new_capacity;
        q->head = 0;
        q->tail = q->size;
    }

    char* dest = (char*)q->data + q->tail * q->elem_size;
    memcpy(dest, elem, q->elem_size);
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;

    return 0;
}

int queue_pop(struct queue *q, void *elem) {
    if (!q || !elem || !q->size) return 1;

    char* src = (char*)q->data + q->head * q->elem_size;
    memcpy(elem, src, q->elem_size);

    q->head = (q->head + 1) % q->capacity;
    q->size--;

    return 0;
}

int queue_empty(struct queue const *q) {
    if (!q) return 1;
    return q->size == 0;
}

struct queue *queue_delete(struct queue *q) {
    if (!q) return NULL;
    free(q->data);
    free(q);
    return NULL;
}

void queue_print(struct queue const *q, void (*pf)(void const *data)) {
    if (!q || !pf) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < q->size; ++i) {
        size_t index = (q->tail - 1 - i + q->capacity) % q->capacity;   
        char* elem_ptr = (char*)q->data + index * q->elem_size;
        pf(elem_ptr);
        if (i < q->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

