//
// Created by kirill on 27.10.2019.
//

#include <stdlib.h>
#include <stdio.h>

const int MAX_CMP_COUNT = 1000;

int comp(const int *, const int *);

int sort(int *pos_sort, int size_pos, int *cmp, int size_cmp);

signed main() {
    int n;
    while (scanf("%d", &n) && n) {
        int *cmp = malloc(2 * MAX_CMP_COUNT * sizeof(int));
        int size_cmp = 0;
        int *one_pos = malloc(n * sizeof(int));
        int *zero_pos = malloc(n * sizeof(int));
        int size_one = 0, size_zero = 0;
        for (int i = 0; i < n; i++) {
            int b; scanf("%d", &b);
            if (b) {
                one_pos[size_one++] = i;
            } else {
                zero_pos[size_zero++] = i;
            }
        }
        if (!size_one || !size_zero || one_pos[0] > zero_pos[size_zero - 1]) {
            printf("-1\n");
            free(one_pos);
            free(zero_pos);
            free(cmp);
            continue;
        }
        size_cmp = sort(one_pos, size_one, cmp, size_cmp);
        size_cmp = sort(zero_pos, size_zero, cmp, size_cmp);
        int *cur = malloc(n * sizeof(int));
        for (int i = 0; i < size_zero - 1; i++) {
            cur[i] = zero_pos[i];
        }
        for (int i = 1; i < size_one; i++) {
            cur[i + size_zero - 2] = one_pos[i];
        }
        qsort(cur, n - 2, sizeof(int), (int(*)(const void *, const void *))comp);
        size_cmp = sort(cur, n - 2, cmp, size_cmp);
        for (int i = 0; i < size_zero; i++) {
            cur[i] = i;
        }
        size_cmp = sort(cur, size_zero, cmp, size_cmp);
        for (int i = 0; i < size_one; i++) {
            cur[i] = i + size_zero;
        }
        size_cmp = sort(cur, size_one, cmp, size_cmp);
        printf("%d\n", size_cmp / 2);
        for (int i = 0; i < size_cmp; i += 2) {
            printf("%d %d\n", cmp[i] + 1, cmp[i + 1] + 1);
        }
        free(one_pos);
        free(zero_pos);
        free(cmp);
        free(cur);
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int sort(int *pos_sort, int size_pos, int *cmp, int size_cmp) {
    for (int i = 0; i < size_pos; i++) {
        for (int j = i + 1; j < size_pos; j++) {
            if (i != j) {
                cmp[size_cmp++] = min(pos_sort[i], pos_sort[j]);
                cmp[size_cmp++] = max(pos_sort[i], pos_sort[j]);
            }
        }
    }
    return size_cmp;
}

int comp(const int *a, const int *b) {
    return *a - *b;
}