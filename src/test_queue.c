#include "queue.h"
#include <stdio.h>
#include <tap.h>

int main () {
    int values[] = {4, 2, 1, 3, 6, 5};
    diag("Creating empty queue");
    queue q;
    queue_initialize(&q);
    ok(q.first == NULL, "q.first == NULL if q is empty");
    ok(q.last  == NULL, "q.last == NULL if q is empty");
    dies_ok({queue_pop(&q);}, "popping from empty queue crashes");
    diag("Adding values 4, 2, 1, 3");
    queue_push(&q, values);
    queue_push(&q, values + 1);
    queue_push(&q, values + 2);
    queue_push(&q, values + 3);
    ok(*(int*)queue_first(&q) == 4, "first value is 4");
    ok(*(int*)queue_last(&q)  == 3, "last value is 3");
    ok(queue_length(&q)       == 4, "length of queue is 4");
    diag("Popping the first value");
    ok(*(int*)queue_pop(&q)   == 4, "returned value is 4");
    ok(*(int*)queue_first(&q) == 2, "first value is now 2");
    ok(*(int*)queue_last(&q)  == 3, "last value is still 3");
    ok(queue_length(&q)       == 3, "length of queue is now 3");
    diag("Pushing 6, 5");
    queue_push(&q, values + 4);
    queue_push(&q, values + 5);
    ok(*(int*)queue_first(&q) == 2, "first value is still 2");
    ok(*(int*)queue_last(&q)  == 5, "last value is now 5");
    ok(queue_length(&q)       == 5, "length of queue is 5");
    diag("Popping while not empty");
    while (!queue_is_empty(&q)) queue_pop(&q);
    ok(queue_length(&q) == 0, "length of queue is now 0");
    diag("Deleting the queue");
    queue_delete(&q);
    done_testing();
}
