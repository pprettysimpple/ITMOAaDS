//
// Created by kirill on 23.10.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n, k, m;
int **cmp_first;
int **cmp_second;
int *cnt;

int get(int x, int pos) {
    return ((x >> pos) & 1);
}

signed main() {
    scanf("%d", &n);
    m = 0;

    cmp_first = malloc(16 * sizeof(int*));
    cmp_second = malloc(16 * sizeof(int*));
    for (int i = 0; i < 16; i++) {
        cmp_first[i] = malloc(16 * sizeof(int));
        cmp_second[i] = malloc(16 * sizeof(int));
    }
    cnt = malloc(16 * sizeof(int));
    memset(cnt, 0, 16 * sizeof(int));

    int layer = 0;
    for (int big_step = 1; big_step <= 4; big_step++) {
        int max_layer = layer;
        for (int j = 0; j < 16; j += (1 << big_step)) {
            int cur_layer = layer;
            _Bool has_cmp = 0;
            //unite prev sort_layer to bitonic sequence
            for (int pos = j; pos < j + (1 << (big_step - 1)); pos++) {
                int x = pos;
                int y = j + (1 << big_step) - pos + j - 1;
                if (x < n && y < n) {
                    m++;
                    cmp_first[cur_layer][cnt[cur_layer]] = x;
                    cmp_second[cur_layer][cnt[cur_layer]++] = y;
                    has_cmp = 1;
                }
            }
            cur_layer += has_cmp;
            //sort bitonic sequence
            for (int step = big_step - 1; step > 0; step--) {
                has_cmp = 0;
                for (int start_pos = j; start_pos < j + (1 << big_step); start_pos += (1 << step)) {
                    for (int pos = start_pos; pos < start_pos + (1 << (step - 1)); pos++) {
                        int x = pos;
                        int y = pos + (1 << (step - 1));
                        if (x < n && y < n) {
                            m++;
                            cmp_first[cur_layer][cnt[cur_layer]] = x;
                            cmp_second[cur_layer][cnt[cur_layer]++] = y;
                            has_cmp = 1;
                        }
                    }
                }
                cur_layer += has_cmp;
            }
            if (max_layer < cur_layer) max_layer = cur_layer;
        }
        layer = max_layer;
    }

    printf("%d %d %d\n", n, m, layer);

    for (int i = 0; i < layer; i++) {
        printf("%d ", cnt[i]);
        for (int j = 0; j < cnt[i]; j++) {
            printf("%d %d ", cmp_first[i][j] + 1, cmp_second[i][j] + 1);
        }
        putchar('\n');
    }
}