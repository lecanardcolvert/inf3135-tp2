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
    return q->first == NULL;
}

void queue_push(queue *q, const void *value) {
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

const void *queue_pop(queue *q) {
    assert(!queue_is_empty(q));
    if (q->first == q->last) q->last = NULL;
    const void *value = q->first->value;
    struct queue_node *node = q->first;
    q->first = node->next;
    free(node);
    return value;
}

void queue_print(const queue *q) {
    printf("[ ");
    for (struct queue_node *node = q->first;
         node != NULL;
         node = node->next) {
        printf("%p ", node->value);
    }
    printf("]");
}
