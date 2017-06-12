#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init(struct list *l) {
    l->head = NULL;
    l->tail = NULL;
}

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

void print(struct list l) {
    struct node *temp = l.head;
    while (temp != NULL) {
        printf("%i ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void push_front(struct list *l, int i) {
    struct node n;
    struct node *temp = l->head;

    n.val = i;
    n.next = temp;

    l->head = &n;

    free(temp);
}

void push_back(struct list *l, int i) {
    struct node *n = (struct node *) malloc(sizeof(struct node));
    n->val = i;
    n->next = NULL;

    if (l->head == NULL && l->tail == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = l->tail->next;
    }
}

int front(struct list l) {
    return l.head->val;
}

int back(struct list l) {
    return l.tail->val;
}

int pop_back(struct list *l) {
    int val = l->tail->val;
    struct node *temp = l->head;

    if (temp->next == NULL) {
        free(temp);
        init(l);
    } else {
        l->tail = NULL;
        while (temp->next != NULL) {
            l->tail = temp;
            temp = temp->next;
        }
        free(l->tail->next);
        l->tail->next = NULL;
    }

    return val;
}

int remove_front(struct list *l) {
    int val = l->head->val;
    struct node *temp = l->head;

    if (temp->next == NULL)
        init(l);
    else
        l->head = l->head->next;

    free(temp);

    return val;
}

int empty(struct list l) {
    if (l.head == NULL && l.tail == NULL)
        return 1;
    return 0;
}

void delete(struct list *l) {
    struct node *n = l->head;
    while (n != NULL) {
        struct node *temp = n;
        n = n->next;
        free(temp);
    }
}
