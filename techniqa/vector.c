#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector {
    void* data;
    size_t elem_size;
    size_t size;
    size_t capacity;
};

struct vector *vector_new(size_t elems, size_t elem_size) {
    if (elem_size == 0) {
        return NULL;
    }
    
    struct vector* vec = (struct vector*)malloc(sizeof(struct vector));
    if (!vec) {
        return NULL;
    }

    vec->elem_size = elem_size;
    vec->size = elems;
    
    vec->capacity = elems > 0 ? elems : 1;
    
    vec->data = malloc(vec->capacity * elem_size);
    if (!vec->data) {
        free(vec);
        return NULL;
    }

    return vec;
}

int vector_push(struct vector *v, void const *elem) {
    if (!v || !elem) return 1;

    if (v->size >= v->capacity) {
        size_t new_capacity = v->capacity * 2;
        void* new_data = realloc(v->data, new_capacity * v->elem_size);
        if (!new_data) {
            return 1;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }

    void* dest = (char*)v->data + v->size * v->elem_size;
    memcpy(dest, elem, v->elem_size);
    v->size++;
    
    return 0;
}

int vector_pop(struct vector *v, void *elem) {
    if (!v || v->size == 0) {
        return 1;
    }
    
    if (elem) {
        void* src = (char*)v->data + (v->size - 1) * v->elem_size;
        memcpy(elem, src, v->elem_size);
    }
    
    v->size--;
    return 0;
}

int vector_empty(struct vector const *v) {
    if (!v) return 1;
    return v->size == 0;
}

struct vector *vector_delete(struct vector *v) {
    if (!v) return NULL;
    free(v->data);
    free(v);
    return NULL;
}

void vector_print(struct vector const *v, void (*pf)(void const *data)) {
    if (!v || !pf) {
        printf("[]\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < v->size; i++) {
        void* elem_ptr = (char*)v->data + i * v->elem_size;
        pf(elem_ptr);
        
        if (i < v->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int vector_set(struct vector *v, size_t index, void const *elem) {
    if (!v || !elem || index >= v->size) {
        return 1;
    }
    
    void* dest = (char*)v->data + index * v->elem_size;
    memcpy(dest, elem, v->elem_size);
    return 0;
}

int vector_get(struct vector const *v, size_t index, void *elem) {
    if (!v || !elem || index >= v->size) {
        return 1;
    }
    
    void* src = (char*)v->data + index * v->elem_size;
    memcpy(elem, src, v->elem_size);
    return 0;
}

int vector_resize(struct vector *v, size_t new_size) {
    if (!v) return 1;
    
    if (new_size > v->capacity) {
        void* new_data = realloc(v->data, new_size * v->elem_size);
        if (!new_data) {
            return 1;
        }
        v->data = new_data;
        v->capacity = new_size;
    }
    
    v->size = new_size;
    return 0;
}

size_t vector_size(struct vector const *v) {
    if (!v) return 0;
    return v->size;
}
