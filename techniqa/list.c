#include <stdio.h>
#include <stdlib.h>

struct list {
    int elem;
    struct list* next;
};

struct list* list_new(int elem) {
    struct list* node = malloc(sizeof(struct list));
    if (!node) return NULL;
    node->elem = elem;
    node->next = NULL;
    return node;
}

struct list* list_insert(struct list *head, int elem) {
    struct list* new_node = list_new(elem);
    if (!new_node) return head; 

    if (!head) {
        return new_node; 
    }

    struct list* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new_node;
    return head; 
}

struct list* list_find(struct list *head, int elem) {
    struct list* curr = head;
    while (curr) {
        if (curr->elem == elem) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

struct list *list_erase(struct list *head, int elem) {
    if (!head) return NULL;

    if (head->elem == elem) {
        struct list* new_head = head->next;
        free(head);
        return new_head;
    }

    struct list *prev = head;
    while (prev->next && prev->next->elem != elem) {
        prev = prev->next;
    }

    if (!prev->next) {
        return head;
    }

    struct list* to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);

    return head;
}

struct list *list_insert_after(struct list *head, struct list *where, struct list *what) {
    if (!where || !what) {
        return head;
    }

    if (!head) {
        return head;
    }

    struct list *curr = head;
    while (curr && curr != where) {
        curr = curr->next;
    }
    if (!curr) {
        return head; 
    }

    what->next = where->next;
    where->next = what;

    return head;
}

struct list *list_insert_before(struct list *head, struct list *where, struct list *what) {
    if (!where || !what) {
        return head; 
    }

    if (!head) {
        return head; 
    }

    if (head == where) {
        what->next = head;
        return what; 
    }

    struct list* prev = head;
    while (prev->next && prev->next != where) {
        prev = prev->next;
    }

    if (!prev->next) {
        return head;
    }

    what->next = where;
    prev->next = what;

    return head;
}

struct list *list_delete(struct list *head) {
    while (head) {
        struct list *next = head->next;
        free(head);
        head = next;
    }
    return NULL;
}

struct list *list_next(struct list *curr) {
    if (!curr) return NULL;
    return curr->next;
}

void list_print(struct list const *head) {
    printf("[");
    const struct list* curr = head;
    int first = 1;
    while (curr) {
        if (!first) {
            printf(", ");
        }
        printf("%d", curr->elem);
        first = 0;
        curr = curr->next;
    }
    printf("]\n");
}
 
      