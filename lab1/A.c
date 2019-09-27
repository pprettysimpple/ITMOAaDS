#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

int *a;
unsigned int capacity, size;

void initialize() {
    a = malloc(sizeof(int));
    capacity = 1;
    size = 0;
}

void increase_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity * 2);
    memcpy(tmp_a, a, sizeof(int) * size);
    free(a);
    a = tmp_a;
    capacity *= 2;
}

void decrease_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity / 2);
    memcpy(tmp_a, a, sizeof(int) * size);
    free(a);
    a = tmp_a;
    capacity /= 2;
}

void push(int value) {
    if (size == capacity) {
        increase_capacity();
    }
    a[size++] = value;
}

int pop() {
    int tmp = a[--size];
    if (size && size * 4 <= capacity) {
        decrease_capacity();
    }
    return tmp;
}

void delete() {
    free(a);
}

int main() {
    int n;
    scanf("%d%*c", &n);
    initialize();
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
    delete();
    return 0;
}