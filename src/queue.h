/**
 * queue.h
 *
 * Provides a generic queue data structure and functions operating on it.
 *
 * @author  Alexandre Blondin Massé
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Types //
// ----- //

struct queue_node {          // A node in the queue
    const void *value;       // The value stored in the node
    struct queue_node *prev; // The previous node in the queue
    struct queue_node *next; // The next node in the queue
};

typedef struct {              // A simple queue
    struct queue_node *first; // The first node in the queue
    struct queue_node *last;  // The last node in the queue
} queue;

// Functions //
// --------- //

/**
 * Initialize an empty queue
 *
 * Note: when the queue is not needed anymore, a call to `queue_delete` should
 * be made.
 *
 * @param q  The queue to initialize
 */
void queue_initialize(queue *q);

/**
 * Delete a queue
 *
 * @param q  The queue to delete
 */
void queue_delete(queue *q);

/**
 * Tell if a queue is empty
 *
 * @param q  The queue to check
 * @return   True if and only if the queue is empty
 */
bool queue_is_empty(const queue *q);

/**
 * Push a value at the end of a queue
 *
 * @param q      The queue
 * @param value  The value to push
 */
void queue_push(queue *q, const void *value);

/**
 * Pop the first value of a queue
 *
 * The first value is removed from the queue and returned.
 *
 * @param q  The queue
 * @return   The first value in the queue
 */
const void *queue_pop(queue *q);

/**
 * Prints the given queue
 *
 * @param q  The queue
 */
void queue_print(const queue *q);

#endif
