#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "test_queue.h"

int get_rand(int a, int b) {
    int range = b - a;
    return rand() % range + a;
}

void init_single(int num, int min, int max, int rate) {
    int i, j;
    struct list queue;
    int cashiers[num];

    printf("Single queue:\n\n");

    for (i = 0; i < num; i++)
        cashiers[i] = 0;

    init(&queue);
    for (i = 0; i < 600; i++) {
        if (i % rate == 0) push_back(&queue, get_rand(min, max));
        for (j = 0; j < num; j++) {
            if (cashiers[j] != 0) (cashiers[j])--;
            else if (cashiers[j] == 0 && size(queue) != 0) cashiers[j] = remove_front(&queue);
        }
        if (i == 59 || i == 299 || i == 599)
            printf("%i hour(s):\nNumber of customers in queue: %i\n\n", (i + 1) / 60, size(queue));
    }
    delete(&queue);
}

void init_multi(int num, int min, int max, int rate) {
    int i, j;
    int cashiers[num];
    struct list queues[num];

    printf("Multiple queues:\n\n");

    for (i = 0; i < num; i++) {
        cashiers[i] = 0;
        init(&(queues[i]));
    }

    for (i = 0; i < 600; i++) {
        if (i % rate == 0) {
            int n = 0, s = size(queues[0]);
            for (j = 1; j < num; j++) {
                if (size(queues[j]) < s) {
                    s = size(queues[j]);
                    n = j;
                }
            }
            push_back(&(queues[n]), get_rand(min, max));
        }
        for (j = 0; j < num; j++) {
            if (cashiers[j] != 0)
                (cashiers[j])--;
            else if (cashiers[j] == 0 && size(queues[j]) != 0)
                cashiers[j] = remove_front(&(queues[j]));
        }
        if (i == 59 || i == 299 || i == 599) {
            int c = 0;
            printf("%i hour(s): \n", (i + 1) / 60);
            for (j = 0; j < num; j++) {
                int s = size(queues[j]);
                printf("%i people in queue %i\n", s, j);
                c += s;
            }
            printf("Number of customers in queue: %i\n\n", c);
        }
    }

    for (i = 0; i < num; i++)
        delete(&(queues[i]));
}
