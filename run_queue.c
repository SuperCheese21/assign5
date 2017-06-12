#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "test_queue.h"

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
