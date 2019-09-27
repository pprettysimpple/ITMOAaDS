#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

int *a;
unsigned int capacity, size, head, tail;

void initialize() {
    a = malloc(sizeof(int));
    capacity = 1;
    size = 0;
    head = tail = 0;
}

void copy(int *from, int *to) {
    for (int i = 0; i < size; i++) {
        to[i] = from[(head + i) % capacity];
    }
    head = 0, tail = size;
}

void increase_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity * 2);
    copy(a, tmp_a);
    free(a);
    a = tmp_a;
    capacity *= 2;
}

void decrease_capacity() {
    int *tmp_a = malloc(sizeof(int) * capacity / 2);
    copy(a, tmp_a);
    free(a);
    a = tmp_a;
    capacity /= 2;
}

void push(int value) {
    if (size == capacity) {
        increase_capacity();
    }
    size++, a[tail] = value;
    tail = (tail + 1) % capacity;
}

int pop() {
    int tmp = a[head];
    head = (head + 1) % capacity;
    size--;
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