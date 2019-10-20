//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

typedef double ld;

int n, m, k;
char **arr, **new;
int *cnt;
int alpha = 'z' - 'a' + 1;

void sort_kth(int k) {
    memset(cnt, 0, alpha * sizeof(int));
    for (int i = 0; i < n; i++) {
        cnt[arr[i][k]]++;
    }
    for (int i = 1; i < alpha; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        new[--cnt[arr[i][k]]] = arr[i];
    }
    char ** tmp = arr;
    arr = new;
    new = tmp;
}

signed main() {
    cnt = malloc(alpha * sizeof(int));
    scanf("%d%d%d%*c", &n, &m, &k);
    new = malloc(n * sizeof(char*));
    arr = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(m * sizeof(char));
        for (int j = 0; j < m; j++) {
            scanf("%c", &arr[i][j]);
            arr[i][j] -= 'a';
        }
        scanf("%*c");
    }
    for (int i = m - 1; i >= m - k; i--) {
        sort_kth(i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", arr[i][j] + 'a');
        }
        printf("\n");
    }
}