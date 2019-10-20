//
// Created by kirill on 13.10.2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#pragma GCC optimize("-Ofast")

void slow_sort(int *a, int size) {
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; ++j) {
            if (a[j] > a[j + 1]) {
                a[j + 1] ^= a[j];
                a[j] ^= a[j + 1];
                a[j + 1] ^= a[j];
            }
        }
    }
    for (int k = 0; k + 1 < size; ++k) {
        if (a[k] > a[k + 1]) {
            assert(0);
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int kth_element(int *a, int size, int k) {
    if (size == 1) {
        return a[0];
    }
    for (int i = 0; i < size; i += 5) {
        slow_sort(a + i, (int) (min(5, size - i)));
    }
    int *cur = malloc(((size + 4) / 5) * sizeof(int));
    for (int i = 0; i < size; i += 5) {
        cur[i / 5] = a[i + min(size - i, 5) / 2];
    }
    int x = kth_element(cur, (size + 4) / 5, (size + 4) / 10);
    free(cur);
    int *less = malloc(size * sizeof(int));
    int *more = malloc(size * sizeof(int));
    int cnt_equal = 0, cnt_less = 0, cnt_more = 0;
    for (int i = 0; i < size; i++) {
        if (a[i] < x) {
            less[cnt_less++] = a[i];
        } else if (a[i] > x) {
            more[cnt_more++] = a[i];
        } else {
            cnt_equal++;
        }
    }
    for (int i = 0; i < cnt_less; i++) {
        a[i] = less[i];
    }
    for (int i = 0; i < cnt_equal; i++) {
        a[i + cnt_less] = x;
    }
    for (int i = 0; i < cnt_more; i++) {
        a[i + cnt_equal + cnt_less] = more[i];
    }
    free(less);
    free(more);
    if (k < cnt_less) {
        return kth_element(a, cnt_less, k);
    }
    if (k >= cnt_less + cnt_equal) {
        return kth_element(a + cnt_equal + cnt_less, cnt_more, k - cnt_equal - cnt_less);
    }
    return x;
}

signed main() {
    int n, k, a, b, c;
    scanf("%d%d", &n, &k);
    int *arr = malloc((n + 1) * sizeof(int));
    scanf("%d%d%d%d%d", &a, &b, &c, &arr[0], &arr[1]);
    for (int i = 2; i < n; ++i) {
        arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
    }
    printf("%d", kth_element(arr, n, k - 1));
}