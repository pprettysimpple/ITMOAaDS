//
// Created by kirill on 28.10.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int *p, *size, *right;

int max(int x, int y) {
    return (x > y) ? x : y;
}

void init(int n) {
    p = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));
    right = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = i;
        right[i] = i;
        size[i] = 1;
    }
}

int get(int x) {
    return (p[x] == x) ? x : (p[x] = get(p[x]));
}

void unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return;
    size[y] += size[x];
    p[x] = y;
}

signed main() {
    int n; scanf("%d%*c", &n);
    init(n);

    int *used = malloc(n * sizeof(int));
    memset(used, 0, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        --x;
        if (!used[x]) {
            used[x] = 1;
            printf("%d ", x + 1);
            continue;
        }
        while (used[(right[get(x)] + 1) % n]) {
            unite(x, (right[get(x)] + 1) % n);
        }
        used[(right[get(x)] + 1) % n] = 1;
        printf("%d ", (right[get(x)] + 1) % n + 1);
        unite(x, (right[get(x)] + 1) % n);
    }
    return 0;
}