/*********************************************************************
** Program Filename: run_queue.c
** Author: Ethan Shields
** Date: 6/11/17
** Description: Simulates a restaurant queueing system
** Input: number of queues, min time, max time, customer arrival rate
** Output: results for both queueing systems
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test_queue.h"

/*********************************************************************
** Function: main()
** Description: parses command line arguments and calls queue simulation functions
** Parameters: (int) argc - number of command line arguments, (char *[]) argv - command line args
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
int main(int argc, char const *argv[]) {
    int i, num, min, max, rate;

    // checks command line flags and sets variables
    for (i = 1; i < argc; i += 2) {
        int n = atoi(argv[i + 1]);
        char a = argv[i][1];

        if (a == 'n') num = n;
        else if (a == 's') min = n;
        else if (a == 'e') max = n;
        else if (a == 'c') rate = n;
        else printf("Invalid arg -%c\n", a);
    }

    // seeds random number generator
    srand(time(NULL));

    // calls queue simulation functions
    init_multi(num, min, max, rate);
    init_single(num, min, max, rate);

    return 0;
}
