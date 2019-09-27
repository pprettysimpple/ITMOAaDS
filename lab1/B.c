#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev;
};
typedef struct node *pnode;

pnode last = 0;

void push(int value) {
    pnode v = malloc(sizeof(struct node));
    v->value = value;
    v->prev = last;
    last = v;
}

int pop() {
    pnode tmp = last->prev;
    int value = last->value;
    free(last);
    last = tmp;
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
            push(value);
        } else {
            printf("%d\n", pop());
        }
    }
    return 0;
}