#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    void* data;
    size_t elem_size;
    size_t size;
    size_t capacity;
};

struct stack *stack_new(size_t elem_size);
int stack_push(struct stack *st, const void *elem);
int stack_pop (struct stack *st, void *elem); 
int stack_top (struct stack *st, void *elem); 
int stack_empty(struct stack const *st); 
struct stack *stack_delete(struct stack *st); 
void stack_print(struct stack const *st, void (*pf)(void const *st)); 

struct stack *stack_new(size_t elem_size) {
    if (elem_size == 0) {
        return NULL;
    }
    struct stack* st = (void*) calloc (sizeof(struct stack), 1);
    if (st == NULL) {
        return NULL;
    }

    st->elem_size = elem_size;
    st->capacity  = 50;
    st->size      = 0;

    st->data = (void*) calloc (elem_size, st->capacity);
    if (st->data == NULL) {
        free(st);
        return NULL;
    }
    
    return st;
}

int stack_push(struct stack *st, const void *elem) {
    if (!st || !elem) {
        return 1;
    }

    if (st->size >= st->capacity) {
        size_t new_capacity = 2 * st->capacity;
        void* new_data = realloc(st->data, new_capacity * st->elem_size);
        if (!new_data) {
            return 1;
        }
        st->data = new_data;
        st->capacity = new_capacity;
    }

    void* dest = (char*) st->data + st->size * st->elem_size;
    memcpy(dest, elem, st->elem_size);
    st->size++;
    return 0;
}

int stack_pop (struct stack *st, void *elem) {
    if (!st || !elem || st->size == 0) {
        return 1;
    }

    char* src = (char*) st->data + (st->size - 1) * st->elem_size;
    memcpy(elem, src, st->elem_size);
    st->size--;
    return 0;
}

int stack_top (struct stack *st, void *elem) {
    if (!st || !elem || st->size == 0) {
        return 1;
    }

    char* src = (char*) st->data + (st->size - 1) * st->elem_size;
    memcpy(elem, src, st->elem_size);
    return 0;
}

int stack_empty(struct stack const *st) {
    if (!st) return 1;
    return st->size == 0;
}

struct stack *stack_delete(struct stack *st) {
    if (!st) return NULL;
    free(st->data);
    free(st);
    return NULL;
}

void stack_print(struct stack const *st, void (*pf)(void const *st)) {
    if (!st || !pf) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < st->size; i++) {
        char* tmp = (char*) st->data + i * st->elem_size;
        pf (tmp);
        if (i < st->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

