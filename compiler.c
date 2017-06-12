/*********************************************************************
** Program Filename: compiler.c
** Author: Ethan Shields
** Date: 6/11/17
** Description: Checks a string for matching brackets, parathesis, and braces
** Input: string to validate
** Output: Valid or invalid
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int check_string(struct list *, char *);

/*********************************************************************
** Function: main()
** Description: allocates memory for user inputted string and linked list and calls compiler function
** Parameters: (int) argc - number of command line arguments, (char *[]) argv - command line args
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
int main(int argc, char const *argv[]) {
    // allocates memory for an array of chars and a linked list
    char *s = (char *) malloc(sizeof(char) * 256);
    struct list *stack = (struct list *) malloc(sizeof(struct list));
    init(stack);

    // gets user input
    printf("Enter string: ");
    scanf("%100[^\n]", s);

    // calls validation function and prints result
    if (check_string(stack, s)) printf("Valid\n");
    else printf("Invalid\n");

    // frees all allocated memory
    delete(stack);
    free(stack);
    free(s);

    return 0;
}

/*********************************************************************
** Function: check_string()
** Description: checks if the string has matching brackets, braces, and parenthesis
** Parameters: (struct list *) stack - linked list pointer, (char *) s - string to validate
** Pre-Conditions: stack is a pointer to an initialized linked list, s is an array of chars
** Post-Conditions: return value is an integer between 0 and 1
*********************************************************************/
int check_string(struct list *stack, char *s) {
    int i;
    // checks each character for a bracket, brace, or parathesis
    for (i = 0; i < sizeof(char) * 256; i++) {
        // push a node onto the stack for every opening char
        if (s[i] == '[') push_back(stack, 0);
        else if (s[i] == '{') push_back(stack, 1);
        else if (s[i] == '(') push_back(stack, 2);

        // removes the last node if chars are matching and stack isn't empty
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
    // if stack isn't empty then the string is missing a closing char
    if (empty(*stack)) return 1;
    return 0;
}
