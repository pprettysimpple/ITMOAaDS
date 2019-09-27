#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

int *stacks;
unsigned int capacity, size;

void initialize() {
    stacks = malloc(sizeof(int));
    capacity = 1;
    size = 0;
}

void increase_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity * 2);
    memcpy(tmp_a, stacks, sizeof(int) * size);
    free(stacks);
    stacks = tmp_a;
    capacity *= 2;
}

void decrease_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity / 2);
    memcpy(tmp_a, stacks, sizeof(int) * size);
    free(stacks);
    stacks = tmp_a;
    capacity /= 2;
}

void push(int value) {
    if (size == capacity) {
        increase_capacity();
    }
    stacks[size++] = value;
}

int pop() {
    int tmp = stacks[--size];
    if (size && size * 4 <= capacity) {
        decrease_capacity();
    }
    return tmp;
}

int main() {
    initialize();
    char c;
    while (scanf("%c", &c) == 1) {
        if (c == '+' || c == '-' || c == '*') {
            int b = pop();
            int a = pop();
            int res = INT_MIN;
            if (c == '+') {
                res = a + b;
            }
            if (c == '*') {
                res = a * b;
            }
            if (c == '-') {
                res = a - b;
            }
            push(res);
        }
        if (c >= '0' && c <= '9') {
            int value = (c - '0');
            while (scanf("%c", &c) == 1 && (c >= '0' && c <= '9')) {
                value = value * 10 + c - '0';
            }
            push(value);
        }
    }
    printf("%d\n", pop());
    return 0;
}