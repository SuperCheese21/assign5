#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int check_string(struct list *, char *);

int main(int argc, char const *argv[]) {
    char *s = (char *) malloc(sizeof(char) * 256);
    struct list *stack = (struct list *) malloc(sizeof(struct list));
    init(stack);

    printf("Enter string: ");
    scanf("%100[^\n]", s);

    if (check_string(stack, s)) printf("Valid\n");
    else printf("Invalid\n");

    delete(stack);
    free(stack);
    free(s);

    return 0;
}

int check_string(struct list *stack, char *s) {
    int i;
    for (i = 0; i < sizeof(char) * 256; i++) {
        if (s[i] == '[') push_back(stack, 0);
        else if (s[i] == '{') push_back(stack, 1);
        else if (s[i] == '(') push_back(stack, 2);
        else if (s[i] == ']') {
            if (empty(*stack) || back(*stack) != 0) return 0;
            else pop_back(stack);
        } else if (s[i] == '}') {
            if (empty(*stack) || back(*stack) != 1) return 0;
            else pop_back(stack);
        } else if (s[i] == ')') {
            if (empty(*stack) || back(*stack) != 2) return 0;
            else pop_back(stack);
        }
    }
    if (empty(*stack)) return 1;
    return 0;
}
