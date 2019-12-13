#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int *p, *size;

void init(int n) {
    p = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = i;
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
}

signed main() {
    int n, m, k; scanf("%d%d%d%*c", &n, &m, &k);
    init(n);

    for (int i = 0; i < m; i++) scanf("%*d%*d%*c");

    int* type = malloc(k * sizeof(int));
    int* v = malloc(2 * k * sizeof(int));

    char c;
    for (int current = 0; scanf("%c", &c) && current < k; current++) {
        char _c;
        while (scanf("%c", &_c) && (_c >= 'a' && _c <= 'z'));
        if (c == 'c') {
            type[current] = 0;
        } else {
            type[current] = 1;
        }
        scanf("%d%d%*c", v + 2 * current, v + 2 * current + 1);
        --v[2 * current];
        --v[2 * current + 1];
    }

    int *ans = malloc(k * sizeof(int));
    int pos = 0;

    for (int i = k - 1; i >= 0; i--) {
        if (type[i]) {
            ans[pos++] = (get(v[2 * i]) == get(v[2 * i + 1]));
        } else {
            unite(v[2 * i], v[2 * i + 1]);
        }
    }

    for (int i = pos - 1; i >= 0; i--) {
        if (ans[i]) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}