#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#pragma GCC optimize("Ofast, fast-math")

const int VALUE = 0, MIN = 1, FIRST_STACK = 0, SECOND_STACK = 1;

int *stacks[2][2];
unsigned int capacity[2], size[2];

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void initialize_stack(int stack_number) {
    stacks[stack_number][VALUE] = malloc(sizeof(int));
    stacks[stack_number][MIN] = malloc(sizeof(int));
    capacity[stack_number] = 1;
    size[stack_number] = 0;
}

void increase_capacity_stack(int stack_number) {
    int *tmp_value = malloc(sizeof(int) * capacity[stack_number] * 2);
    int *tmp_min = malloc(sizeof(int) * capacity[stack_number] * 2);
    memcpy(tmp_value, stacks[stack_number][VALUE], sizeof(int) * size[stack_number]);
    memcpy(tmp_min, stacks[stack_number][MIN], sizeof(int) * size[stack_number]);
    free(stacks[stack_number][VALUE]);
    free(stacks[stack_number][MIN]);
    stacks[stack_number][VALUE] = tmp_value;
    stacks[stack_number][MIN] = tmp_min;
    capacity[stack_number] *= 2;
}

void decrease_capacity_stack(int stack_number) {
    int *tmp_value = malloc(sizeof(int) * capacity[stack_number] / 2);
    int *tmp_min = malloc(sizeof(int) * capacity[stack_number] / 2);
    memcpy(tmp_value, stacks[stack_number][VALUE], sizeof(int) * size[stack_number]);
    memcpy(tmp_min, stacks[stack_number][MIN], sizeof(int) * size[stack_number]);
    free(stacks[stack_number][VALUE]);
    free(stacks[stack_number][MIN]);
    stacks[stack_number][VALUE] = tmp_value;
    stacks[stack_number][MIN] = tmp_min;
    capacity[stack_number] /= 2;
}

void push_stack(int value, int stack_number) {
    if (size[stack_number] == capacity[stack_number]) {
        increase_capacity_stack(stack_number);
    }
    stacks[stack_number][VALUE][size[stack_number]] = value;
    if (size[stack_number]) {
        stacks[stack_number][MIN][size[stack_number]] = min(value, stacks[stack_number][MIN][size[stack_number] - 1]);
    } else {
        stacks[stack_number][MIN][size[stack_number]] = value;
    }
    size[stack_number]++;
}

int pop_stack(int stack_number) {
    int tmp = stacks[stack_number][VALUE][--size[stack_number]];
    if (size[stack_number] && size[stack_number] * 8 <= capacity[stack_number]) {
        decrease_capacity_stack(stack_number);
    }
    return tmp;
}

int get_stack_min(int stack_number) {
    return size[stack_number] ? stacks[stack_number][MIN][size[stack_number] - 1] : INT_MAX;
}

void move_queue() {
    while (size[SECOND_STACK]) {
        push_stack(pop_stack(SECOND_STACK), FIRST_STACK);
    }
}

void push_queue(int value) {
    push_stack(value, SECOND_STACK);
}

int pop_queue() {
    if (!size[FIRST_STACK]) {
        move_queue();
    }
    return pop_stack(FIRST_STACK);
}

int get_queue_min() {
    return min(get_stack_min(FIRST_STACK), get_stack_min(SECOND_STACK));
}

int main() {
    initialize_stack(0);
    initialize_stack(1);

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    int *x = malloc(sizeof(int) * k);

    for (int i = 0; i < k; i++) {
        scanf("%d", &x[i]);
    }

    long long answer = 0;

    int p_last = -1, last = -1;
    bool flag = false;

    for (int i = 0; i < n; i++) {
        if (i >= m) {
            int tmp = get_queue_min();
            answer += tmp;
            pop_queue();
        }
        if (i < k) {
            push_queue(x[i]);
        } else {
            if (!flag) {
                p_last = x[k - 2];
                last = x[k - 1];
                flag = true;
            }
            push_queue(p_last = (p_last * a + last * b + c));
            last ^= p_last;
            p_last ^= last;
            last ^= p_last;
        }
    }

    answer += get_queue_min();

    printf("%lld", answer);
    return 0;
}