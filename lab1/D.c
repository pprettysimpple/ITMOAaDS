#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev, *next;
};
typedef struct node *pnode;

pnode head = 0, tail = 0;

void push_queue(int value) {
    pnode v = malloc(sizeof(struct node));
    v->value = value;
    v->prev = tail;
    v->next = NULL;
    if (tail) {
        tail->next = v;
    } else {
        head = v;
    }
    tail = v;
}

int pop_queue() {
    pnode tmp = head->next;
    int value = head->value;
    free(head);
    if (tmp) {
        tmp->prev = NULL;
    } else {
        tail = NULL;
    }
    head = tmp;
    return value;
}

int main() {
    int n;
    scanf("%d%*c", &n);
    while (n--) {
        char c;
        scanf("%c%*c", &c);
        if (c == '+') {
            int value;
            scanf("%d%*c", &value);
            push_queue(value);
        } else {
            printf("%d\n", pop_queue());
        }
    }
    return 0;
}