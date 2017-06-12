/*********************************************************************
** Program Filename: test_queue.c
** Author: Ethan Shields
** Date: 6/11/17
** Description: Defines functions listed in test_queue.h
** Input:
** Output:
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "test_queue.h"

/*********************************************************************
** Function: get_rand()
** Description: returns a random integer between the upper and lower bounds
** Parameters: (int) a - lower bound, (int) b - upper bound
** Pre-Conditions: b is greater than a
** Post-Conditions: return value is between a and b
*********************************************************************/
int get_rand(int a, int b) {
    int range = b - a;
    return rand() % range + a;
}

/*********************************************************************
** Function: init_single()
** Description: simulates a restaurant queueing system with one queue
** Parameters: (int) num - number of cashiers, (int) min - minimum time, (int) max - maximum time, (int) rate - rate of customer arrival
** Pre-Conditions: all arguments are integers
** Post-Conditions: none
*********************************************************************/
void init_single(int num, int min, int max, int rate) {
    int i, j;
    int cashiers[num]; // array representing number of minutes remaining for each cashier
    struct list queue;

    printf("Single queue:\n\n");

    // initializes cashiers array to 0
    for (i = 0; i < num; i++)
        cashiers[i] = 0;

    // initializes queue
    init(&queue);

    // loops through each minute for 10 hours
    for (i = 0; i < 600; i++) {
        // adds a customer at an inteval of rate minutes
        if (i % rate == 0) push_back(&queue, get_rand(min, max));

        // if there are any open cashiers then remove a customer from front of line
        for (j = 0; j < num; j++) {
            if (cashiers[j] != 0) (cashiers[j])--;
            else if (cashiers[j] == 0 && size(queue) != 0) cashiers[j] = remove_front(&queue);
        }

        // prints information at 1 hour, 5 hours, and 10 hours
        if (i == 59 || i == 299 || i == 599)
            printf("%i hour(s):\nNumber of customers in queue: %i\n\n", (i + 1) / 60, size(queue));
    }

    // deletes nodes in queue
    delete(&queue);
}

/*********************************************************************
** Function: init_multi()
** Description: simulates a restaurant queueing system with multiple queues
** Parameters: (int) num - number of cashiers, (int) min - minimum time, (int) max - maximum time, (int) rate - rate of customer arrival
** Pre-Conditions: all arguments are integers
** Post-Conditions: none
*********************************************************************/
void init_multi(int num, int min, int max, int rate) {
    int i, j;
    int cashiers[num]; // array representing number of minutes remaining for each cashier
    struct list queues[num]; // array of linked list structs representing a line in front of each cashier

    printf("Multiple queues:\n\n");

    // initializes cashiers array to 0 and initializes each linked list
    for (i = 0; i < num; i++) {
        cashiers[i] = 0;
        init(&(queues[i]));
    }

    // loops through each minute for 10 hours
    for (i = 0; i < 600; i++) {
        // adds a customer at an inteval of rate minutes
        if (i % rate == 0) {
            // finds shortest line
            int n = 0, s = size(queues[0]);
            for (j = 1; j < num; j++) {
                if (size(queues[j]) < s) {
                    s = size(queues[j]);
                    n = j;
                }
            }
            push_back(&(queues[n]), get_rand(min, max));
        }

        // if there are any open cashiers then remove a customer from front of line
        for (j = 0; j < num; j++) {
            if (cashiers[j] != 0)
                (cashiers[j])--;
            else if (cashiers[j] == 0 && size(queues[j]) != 0)
                cashiers[j] = remove_front(&(queues[j]));
        }

        // prints information at 1 hour, 5 hours, and 10 hours
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

    // deletes nodes in each queue
    for (i = 0; i < num; i++)
        delete(&(queues[i]));
}
