/*********************************************************************
** Program Filename: list.c
** Author: Ethan Shields
** Date: 6/11/17
** Description: Defines functions that modify linked lists
** Input:
** Output:
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*********************************************************************
** Function: init()
** Description: initialize linked list head and tail pointers to null
** Parameters: (struct list *) l - linked list pointer
** Pre-Conditions: l is a pointer to a linked list struct
** Post-Conditions: linked list is initialized
*********************************************************************/
void init(struct list *l) {
    l->head = NULL;
    l->tail = NULL;
}

/*********************************************************************
** Function: size()
** Description: determines the number of nodes in a linked list
** Parameters: (struct list) l - linked list struct
** Pre-Conditions: l is a linked list struct
** Post-Conditions: return value is an integer greater than or equal to 0
*********************************************************************/
int size(struct list l) {
    int n = 0;
    struct node *temp = l.head;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }
    free(temp);

    return n;
}

/*********************************************************************
** Function: print()
** Description: prints out all node values in a linked list
** Parameters: (struct list) l - linked list struct
** Pre-Conditions: l is a linked list struct
** Post-Conditions: none
*********************************************************************/
void print(struct list l) {
    struct node *temp = l.head;
    while (temp != NULL) {
        printf("%i ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

/*********************************************************************
** Function: push_front()
** Description: adds a node to the front of the linked list
** Parameters: (struct list *) l - linked list pointer, (int) i - value to add
** Pre-Conditions: l is a linked list pointer, i is an integer
** Post-Conditions:
*********************************************************************/
void push_front(struct list *l, int i) {
    struct node n;
    struct node *temp = l->head;

    n.val = i;
    n.next = temp;

    l->head = &n;

    free(temp);
}

/*********************************************************************
** Function: push_back()
** Description: adds a node to the end of a linked list
** Parameters: (struct list *) l - linked list pointer, (int) i - value to add
** Pre-Conditions: l is a linked list pointer, i is an integer
** Post-Conditions:
*********************************************************************/
void push_back(struct list *l, int i) {
    struct node *n = (struct node *) malloc(sizeof(struct node)); // allocates memory for new node
    n->val = i;
    n->next = NULL;

    // if linked list is empty
    if (l->head == NULL && l->tail == NULL) {
        l->head = n;
        l->tail = n;
    } else { // if linked list isn't empty
        l->tail->next = n;
        l->tail = l->tail->next;
    }
}

/*********************************************************************
** Function: front()
** Description: returns the first value in a linked list
** Parameters: (struct list) l - linked list struct
** Pre-Conditions: l is a linked list struct
** Post-Conditions: return value is an integer
*********************************************************************/
int front(struct list l) {
    return l.head->val;
}

/*********************************************************************
** Function: back()
** Description: returns the last value in a linked list
** Parameters: (struct list) l - linked list struct
** Pre-Conditions: l is a linked list struct
** Post-Conditions: return value is an integer
*********************************************************************/
int back(struct list l) {
    return l.tail->val;
}

/*********************************************************************
** Function: pop_back()
** Description: removes last node in a linked list and returns it's value
** Parameters: (struct list *) l - linked list pointer
** Pre-Conditions: l is a pointer to a linked list struct
** Post-Conditions: return value is an integer
*********************************************************************/
int pop_back(struct list *l) {
    int val = l->tail->val;
    struct node *temp = l->head;

    // if there is only one node
    if (temp->next == NULL) {
        free(temp);
        init(l);
    } else { // if there is more than one node
        l->tail = NULL;
        // finds second to last node
        while (temp->next != NULL) {
            l->tail = temp;
            temp = temp->next;
        }
        free(l->tail->next);
        l->tail->next = NULL;
    }

    return val;
}

/*********************************************************************
** Function: remove_front()
** Description: removes the first node in a linked list and returns it's value
** Parameters: (struct list *) l - linked list pointer
** Pre-Conditions: l is a pointer to a linked list struct
** Post-Conditions: return value is an integer
*********************************************************************/
int remove_front(struct list *l) {
    int val = l->head->val;
    struct node *temp = l->head;

    // if there is only one node
    if (temp->next == NULL)
        init(l);
    else // if there is more than one node
        l->head = l->head->next;

    free(temp);

    return val;
}

/*********************************************************************
** Function: empty()
** Description: determines if a linked list is empty or not
** Parameters: (struct list) l - linked list struct
** Pre-Conditions: l is a linked list
** Post-Conditions: return value is an integer between 0 and 1
*********************************************************************/
int empty(struct list l) {
    // linked list is empty if head and tail both point to null
    if (l.head == NULL && l.tail == NULL)
        return 1;
    return 0;
}

/*********************************************************************
** Function: delete()
** Description: deletes
** Parameters: (struct list *) l - linked list pointer
** Pre-Conditions: l is a pointer to a linked list struct
** Post-Conditions:
*********************************************************************/
void delete(struct list *l) {
    struct node *n = l->head;
    while (n != NULL) {
        struct node *temp = n;
        n = n->next;
        free(temp);
    }
}
