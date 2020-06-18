#include "queue.h"
#include <stdio.h>

int main() {
    int values[] = {4, 2, 1, 2, 3, 1};
    queue q;
    printf("Creating empty queue: ");
    queue_initialize(&q);
    queue_print(&q);
    printf("\nPushing 4, 2, 1, 2: ");
    queue_push(&q, values);
    queue_push(&q, values + 1);
    queue_push(&q, values + 2);
    queue_push(&q, values + 3);
    queue_print(&q);
    printf("\nPopping %d: ", *(int*)queue_pop(&q));
    queue_print(&q);
    printf("\nPushing 3, 1: ");
    queue_push(&q, values + 4);
    queue_push(&q, values + 5);
    queue_print(&q);
    while (!queue_is_empty(&q)) {
        printf("\nPopping %d: ", *(int*)queue_pop(&q));
        queue_print(&q);
    }
    printf("\n");
    queue_delete(&q);
}
