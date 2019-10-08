//
// Created by kirill on 02.10.2019.
//

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

typedef unsigned int uint;
typedef unsigned long long ull;

const uint BLOCK_SIZE = (1u << 16);
const uint GET_LOW = (1u << 16) - 1;

uint cur = 0, a, b;

__attribute__((always_inline))
uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

__attribute__((always_inline))
uint nextRand32() {
    uint cur_a = nextRand24();
    uint cur_b = nextRand24();
    return (cur_a << 8) ^ cur_b;
}
uint *bucket, *first_order, *sec_order;
uint n;

__attribute__((always_inline))
void preprocess() {
    bucket = malloc(sizeof(uint) * BLOCK_SIZE);
    first_order = malloc(sizeof(uint) * n);
    sec_order = malloc(sizeof(uint) * n);
}

__attribute__((always_inline))
ull sort_this_thing(uint *v) {
    memset(bucket, 0, (sizeof(uint) * BLOCK_SIZE));
    uint *cur_v = v;
    for (uint i = 0; i < n; ++i, ++cur_v) {
        ++bucket[(*cur_v) & GET_LOW];
    }
    uint *cur_bucket = bucket;
    for (uint i = 0; i + 1 < BLOCK_SIZE; ++i, ++cur_bucket) {
        *(cur_bucket + 1) += *cur_bucket;
    }
    cur_v = v;
    for (int i = 0; i < n; ++i, ++cur_v) {
        first_order[--bucket[(*cur_v) & GET_LOW]] = i;
    }
    memset(bucket, 0, BLOCK_SIZE * sizeof(uint));
    cur_v = v;
    for (int i = 0; i < n; ++i, ++cur_v) {
        ++bucket[(*cur_v) >> 16];
    }
    cur_bucket = bucket;
    for (uint i = 0; i + 1 < BLOCK_SIZE; ++i, ++cur_bucket) {
        *(cur_bucket + 1) += *cur_bucket;
    }
    uint *cur_first_order = first_order + n - 1;
    for (int i = n - 1; i >= 0; --i, --cur_first_order) {
        sec_order[--bucket[v[*cur_first_order] >> 16]] = *cur_first_order;
    }
    ull ans = 0;
    uint *cur_sec_order = sec_order;
    for (int i = 0; i < n; ++i, ++cur_sec_order) {
        ans += (ull) v[*cur_sec_order] * ((ull) (i + 1u));
    }
    return ans;
}

signed main() {
    uint t;
    scanf("%u%u", &t, &n);
    preprocess();
    uint *v = malloc(sizeof(uint) * n);
    while (t--) {
        scanf("%u%u", &a, &b);
        for (uint i = 0; i < n; ++i) {
            v[i] = nextRand32();
        }

        printf("%llu\n", sort_this_thing(v));
    }
    return 0;
}
