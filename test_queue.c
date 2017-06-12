#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int get_rand(int a, int b) {
    int range = b - a;
    return rand() % range + a;
}

void init_multi(int num, int min, int max, int rate) {
    int i, j;
    struct list *queues = (struct list *) malloc(sizeof(struct list) * num);
    int cashiers[num];

    printf("Multiple queues:\n\n");

    for (i = 0; i < num; i++) {
        cashiers[i] = 0;
        init(&(queues[i]));
    }

    for (i = 0; i < 600; i++) {
        if (i % rate == 0) {
            int n, s = size(queues[0]);
            for (j = 1; j < num; j++) {
                if (size(queues[j]) < s)
                    n = j;
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
            for (j = 0; j < num; j++)
                c += size(queues[j]);
            printf("%i hour(s):\nNumber of customers in queue: %i\n\n", (i + 1) / 60, c);
        }
    }

    for (i = 0; i < num; i++) {
        delete(&(queues[i]));
    }

    free(queues);
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
        if (i % rate == 0)
            push_back(&queue, get_rand(min, max));
        for (j = 0; j < num; j++) {
            if (cashiers[j] != 0)
                (cashiers[j])--;
            else if (cashiers[j] == 0 && size(queue) != 0)
                cashiers[j] = remove_front(&queue);
        }
        if (i == 59 || i == 299 || i == 599)
            printf("%i hour(s):\nNumber of customers in queue: %i\n\n", (i + 1) / 60, size(queue));
    }
    delete(&queue);
}

int main(int argc, char const *argv[]) {
    int i, num, min, max, rate;

    for (i = 1; i < argc; i += 2) {
        int n = atoi(argv[i + 1]);
        char a = argv[i][1];

        if (a == 'n') num = n;
        else if (a == 's') min = n;
        else if (a == 'e') max = n;
        else if (a == 'c') rate = n;
        else printf("Invalid arg -%c\n", a);
    }

    srand(time(NULL));

    init_multi(num, min, max, rate);
    init_single(num, min, max, rate);

    return 0;
}
