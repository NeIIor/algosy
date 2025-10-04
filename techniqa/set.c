#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h> 

#define BITS_PER_WORD (sizeof(unsigned long) * CHAR_BIT)

struct set {
    unsigned long *bits;
    size_t capacity;
    size_t word_count;
};

struct set *set_new(size_t capacity) {
    if (capacity == 0) {
        struct set *s = malloc(sizeof(struct set));
        if (!s) return NULL;
        s->capacity = 0;
        s->word_count = 0;
        s->bits = NULL;
        return s;
    }

    struct set *s = malloc(sizeof(struct set));
    if (!s) return NULL;

    s->capacity = capacity;
    s->word_count = (capacity + BITS_PER_WORD - 1) / BITS_PER_WORD; 
    s->bits = calloc(s->word_count, sizeof(unsigned long)); 

    if (!s->bits) {
        free(s);
        return NULL;
    }

    return s;
}

int set_insert(struct set *s, size_t elem) {
    if (!s || elem >= s->capacity) return 1;

    size_t word_index = elem / BITS_PER_WORD;
    size_t bit_index = elem % BITS_PER_WORD;

    s->bits[word_index] |= (1UL << bit_index); 

    return 0;
}

int set_erase(struct set *s, size_t elem) {
    if (!s || elem >= s->capacity) return 1;

    size_t word_index = elem / BITS_PER_WORD;
    size_t bit_index = elem % BITS_PER_WORD;

    s->bits[word_index] &= ~(1UL << bit_index);

    return 0;
}

int set_find(struct set const *s, size_t elem) {
    if (!s || elem >= s->capacity) return 0;

    size_t word_index = elem / BITS_PER_WORD;
    size_t bit_index = elem % BITS_PER_WORD;

    return (s->bits[word_index] >> bit_index) & 1UL;
}

struct set *set_delete(struct set *s) {
    if (!s) return NULL;
    free(s->bits);
    free(s);
    return NULL;
}

int set_empty(struct set const *s) {
    if (!s) return 0;

    for (size_t i = 0; i < s->word_count; ++i) {
        if (s->bits[i] != 0) return 1; 
    }
    return 0; 
}

ssize_t set_findfirst(struct set const *s, size_t start) {
    if (!s || start >= s->capacity) return -1;

    size_t start_word = start / BITS_PER_WORD;
    size_t start_bit = start % BITS_PER_WORD;

    for (size_t w = start_word; w < s->word_count; ++w) {
        unsigned long word = s->bits[w];
        size_t bit = 0;
        
        if (w == start_word) {
            word &= ~((1UL << start_bit) - 1); 
        }

        if (word == 0) continue;

        if (w == start_word) bit = start_bit;
        
        while (!(word & (1UL << bit))) {
            bit++;
        }

        return (ssize_t)(w * BITS_PER_WORD + bit);
    }

    return -1; 
}

size_t set_size(struct set const *s) {
    if (!s) return 0;

    size_t count = 0;
    for (size_t i = 0; i < s->word_count; ++i) {
        unsigned long word = s->bits[i];
        while (word) {
            count += word & 1;
            word >>= 1;
        }
    }
    return count;
}

void set_print(struct set const *s) {
    if (!s) {
        printf("[]\n");
        return;
    }

    printf("[");
    int first = 1;

    for (size_t i = 0; i < s->capacity; ++i) {
        if (set_find(s, i)) {
            if (!first) printf(", ");
            printf("%zu", i);
            first = 0;
        }
    }
    printf("]\n");
}

  