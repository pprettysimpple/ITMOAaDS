//
// Created by kirill on 23.09.2019.
//

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef unsigned short us;

const int ALPHABET = 256;

struct node_trie {
    int term;
    struct node_trie **next;
};

typedef struct node_trie *p_node_trie;

p_node_trie init_new_node_trie() {
    p_node_trie p = malloc(sizeof(struct node_trie));
    p->term = -1;
    p->next = malloc(sizeof(p_node_trie) * ALPHABET);
    memset(p->next, 0, sizeof(p_node_trie) * ALPHABET);
    return p;
}

p_node_trie root = 0;

void add_label(char *p, int size, int where) {
    p_node_trie current_root = root;
    for (int i = 0; i < size; i++) {
        if (current_root->next[(int)p[i]] == NULL) {
            current_root->next[(int)p[i]] = init_new_node_trie();
        }
        current_root = (p_node_trie) current_root->next[(int)p[i]];
    }
    current_root->term = where;
}

int find_label(char *p, int size) {
    p_node_trie current_root = root;
    for (int i = 0; i < size; i++) {
        current_root = (p_node_trie) current_root->next[(int)p[i]];
    }
    return current_root->term;
}


struct node_queue {
    us value;
    struct node_queue *next;
};

typedef struct node_queue *p_node_queue;

p_node_queue head = 0, tail = 0;

void push_queue(us value) {
    p_node_queue v = malloc(sizeof(struct node_queue));
    v->value = value;
    v->next = NULL;
    if (tail) {
        tail->next = v;
    } else {
        head = v;
    }
    tail = v;
}

us pop_queue() {
    p_node_queue tmp = head->next;
    us value = head->value;
    free(head);
    if (tmp) {
    } else {
        tail = NULL;
    }
    head = tmp;
    return value;
}


char *stack;
unsigned int capacity, size;

void increase_capacity() {
    char *tmp_a = malloc(sizeof(char) * capacity * 2);
    memcpy(tmp_a, stack, sizeof(char) * size);
    free(stack);
    stack = tmp_a;
    capacity *= 2;
}

void push_stack(char value) {
    if (size == capacity) {
        increase_capacity();
    }
    stack[size++] = value;
}

void initialize() {
    root = init_new_node_trie();
    stack = malloc(sizeof(char));
    capacity = 1;
    size = 0;
}

int *regs;

int main() {
    regs = malloc(sizeof(int) * ALPHABET);
    memset(regs, 0, sizeof(int) * ALPHABET);
    initialize();

    char c;
    while (scanf("%c", &c) != EOF) {
        if (c == '\n') {
            c = ' ';
        }
        push_stack(c);
    }
    push_stack(' ');

    for (int i = 0; i < size; i++) {
        if (stack[i] == ':') {
            char *p = stack + i + 1;
            int sz = 0;
            while (p[sz] != ' ') {
                sz++;
            }
            add_label(p, sz, i + sz);
            for (int j = 0; j <= sz; j++) {
                stack[i + j] = ' ';
            }
            i += sz;
        }
    }

    for (int i = 0; i < size; i++) {
        c = stack[i];
        if (c == ' ') {
            continue;
        }
        if (c == '+') {
            push_queue(pop_queue() + pop_queue());
        }
        if (c == '-') {
            int a = pop_queue();
            int b = pop_queue();
            push_queue(a - b);
        }
        if (c == '*') {
            push_queue(pop_queue() * pop_queue());
        }
        if (c == '/') {
            int a = pop_queue();
            int b = pop_queue();
            if (!b) {
                b = 1;
            }
            push_queue(a / b);
        }
        if (c == '%') {
            int a = pop_queue();
            int b = pop_queue();
            if (!b) {
                b = 1;
            }
            push_queue(a % b);
        }
        if (c == '>') {
            regs[stack[++i] - 'a'] = pop_queue();
        }
        if (c == '<') {
            push_queue(regs[stack[++i] - 'a']);
        }
        if (c == 'P') {
            if (stack[++i] == ' ') {
                printf("%u\n", pop_queue());
            } else {
                printf("%u\n", regs[stack[i] - 'a']);
            }
        }
        if (c == 'C') {
            if (stack[++i] == ' ') {
                printf("%c", pop_queue());
            } else {
                printf("%c", regs[stack[i] - 'a']);
            }
        }
        if (c == 'J') {
            char *p = stack + i + 1;
            int sz = 0;
            while (p[sz] != ' ') {
                sz++;
            }
            int new_i = find_label(p, sz);
            i = new_i;
        }
        if (c == 'Z') {
            char *p = stack + i + 2;
            int sz = 0;
            while (p[sz] != ' ') {
                sz++;
            }
            if (!regs[stack[i + 1] - 'a']) {
                i = find_label(p, sz);
            } else {
                i += sz + 1;
            }
        }
        if (c == 'E') {
            char *p = stack + i + 3;
            int sz = 0;
            while (p[sz] != ' ') {
                sz++;
            }
            if (regs[stack[i + 1] - 'a'] == regs[stack[i + 2] - 'a']) {
                i = find_label(p, sz);
            } else {
                i += sz + 2;
            }
        }
        if (c == 'G') {
            char *p = stack + i + 3;
            int sz = 0;
            while (p[sz] != ' ') {
                sz++;
            }
            if (regs[stack[i + 1] - 'a'] > regs[stack[i + 2] - 'a']) {
                i = find_label(p, sz);
            } else {
                i += sz + 2;
            }
        }
        if (c == 'Q') {
            break;
        }
        if (c >= '0' && c <= '9') {
            us value = c - '0';
            while (stack[i + 1] != ' ') {
                value = value * 10 + stack[i + 1] - '0';
                i++;
            }
            push_queue(value);
        }
    }
    return 0;
}