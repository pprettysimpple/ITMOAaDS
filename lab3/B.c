#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int *p, *size, *mi, *ma;

int min(int x, int y) {
    return (x < y) ? x : y;
}

int max(int x, int y) {
    return (x > y) ? x : y;
}

void init(int n) {
    p = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));
    mi = malloc(n * sizeof(int));
    ma = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = i;
        mi[i] = ma[i] = i + 1;
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
    if (size[x] > size[y]) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    size[y] += size[x];
    p[x] = y;
    mi[y] = min(mi[y], mi[x]);
    ma[y] = max(ma[y], ma[x]);
}

signed main() {
    int n; scanf("%d%*c", &n);
    init(n);

    char c;
    while (scanf("%c", &c) != EOF) {
        char _c;
        while (scanf("%c", &_c) && (_c >= 'a' && _c <= 'z'));
        if (c == 'g') {
            int x; scanf("%d%*c", &x);
            x = get(x - 1);
            printf("%d %d %d\n", mi[x], ma[x], size[x]);
        } else {
            int x, y; scanf("%d%d%*c", &x, &y);
            unite(x - 1, y - 1);
        }
    }
    return 0;
}