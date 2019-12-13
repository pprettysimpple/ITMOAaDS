#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

signed main() {
    int n; scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < n; i++) {
        if (i * 2 + 1 < n && a[i] > a[2 * i + 1]) {
            printf("NO\n");
            return 0;
        }
        if (i * 2 + 2 < n && a[i] > a[2 * i + 2]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}