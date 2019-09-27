#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

char *a;
unsigned int capacity, size;

void initialize() {
    a = malloc(sizeof(int));
    capacity = 1;
    size = 0;
}

void increase_capacity() {
    char *tmp_a = malloc(sizeof(char) * capacity * 2);
    memcpy(tmp_a, a, sizeof(char) * size);
    free(a);
    a = tmp_a;
    capacity *= 2;
}

void decrease_capacity() {
    char *tmp_a = malloc(sizeof(char) * capacity / 2);
    memcpy(tmp_a, a, sizeof(char) * size);
    free(a);
    a = tmp_a;
    capacity /= 2;
}

void push(char value) {
    if (size == capacity) {
        increase_capacity();
    }
    a[size++] = value;
}

void pop() {
    if (--size && size * 4 <= capacity) {
        decrease_capacity();
    }
}

void clear() {
    if (a) {
        free(a);
    }
    initialize();
}

char get_last() {
    return a[size - 1];
}

bool is_empty() {
    return !size;
}

bool is_match(char c1, char c2) {
    return (c1 == '[' && c2 == ']') || (c1 == '(' && c2 == ')');
}

int main() {
    int n;
    scanf("%d%*c", &n);
    initialize();
    char c;
    while (scanf("%c", &c) == 1) {
        push(c);
        while (scanf("%c", &c) && c != '\n') {
            if (is_empty() || !is_match(get_last(), c)) {
                push(c);
            } else {
                if (!is_empty()) {
                    pop();
                }
            }
        }
        printf(is_empty() ? "YES\n" : "NO\n");
        clear();
    }
    return 0;
}