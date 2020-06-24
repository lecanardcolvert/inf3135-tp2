#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void queue_initialize(queue *q) {
    q->first = NULL;
    q->last = NULL;
}

void queue_delete(queue *q) {
    while (!queue_is_empty(q)) {
        queue_pop(q);
    }
}

bool queue_is_empty(const queue *q) {
    assert(q != NULL);
    return q->first == NULL;
}

void queue_push(queue *q, void *value) {
    assert(q != NULL);
    struct queue_node *node = malloc(sizeof(struct queue_node));
    node->value = value;
    node->next = NULL;
    node->prev = q->last;
    if (queue_is_empty(q)) {
        q->first = node;
    } else {
        q->last->next = node;
    }
    q->last = node;
}

void *queue_pop(queue *q) {
    assert(!queue_is_empty(q));
    if (q->first == q->last) q->last = NULL;
    void *value = q->first->value;
    struct queue_node *node = q->first;
    q->first = node->next;
    free(node);
    return value;
}

void *queue_first(const queue *q) {
    assert(!queue_is_empty(q));
    return q->first->value;
}

void *queue_last(const queue *q) {
    assert(!queue_is_empty(q));
    return q->last->value;
}

unsigned int queue_length(const queue *q) {
    assert(q != NULL);
    unsigned int n = 0;
    for (struct queue_node *node = q->first;
         node != NULL;
         node = node->next)
        ++n;
    return n;
}

void queue_print(const queue *q) {
    assert(q != NULL);
    printf("[ ");
    for (struct queue_node *node = q->first;
         node != NULL;
         node = node->next) {
        printf("%p ", node->value);
    }
    printf("]");
}
