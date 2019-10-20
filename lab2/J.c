//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

typedef unsigned int uint;
typedef long long int ll;

uint cur = 0, a, b;
uint rand24() {
    cur = cur * a + b;
    return cur >> 8;
}

uint rand32() {
    uint _a = rand24(), _b = rand24();
    return (_a << 8) ^ _b;
}

ll* merge(ll *first, int sz1, ll *second, int sz2) { // returns pointer to NEW memory size(sz1+sz2) with sorted array
    int p1 = 0, p2 = 0;
    ll *tmp = malloc((sz1 + sz2) * sizeof(ll));
    while (p1 < sz1 && p2 < sz2) {
        if (first[p1] <= second[p2]) {
            *tmp = first[p1++];
        } else {
            *tmp = second[p2++];
        }
        tmp++;
    }
    while (p1 < sz1) {
        *tmp = first[p1++];
        tmp++;
    }
    while (p2 < sz2) {
        *tmp = second[p2++];
        tmp++;
    }
    tmp -= sz1 + sz2;
    return tmp;
}

ll solve(ll *arr, ll n, ll k, ll* arr2) {
    if (n <= 1) return arr2[0] >= k;

    ll left_sum = arr2[n / 2 - 1];
    for (int i = n / 2; i < n; i++) arr[i] -= left_sum;
    for (int i = n / 2; i < n; i++) arr2[i] -= left_sum;
    ll result =
            solve(arr, n / 2, k, arr2) +
            solve(arr + n / 2, n - n / 2, k, arr2 + n / 2);
    for (int i = n / 2; i < n; i++) arr[i] += left_sum;
    for (int i = n / 2; i < n; i++) arr2[i] += left_sum;

    for (int p = n / 2 - 1, i = n - 1; i >= n / 2; i--) {
        while (p >= 0 && arr[p] > (arr[i] - k)) {
            p--;
        }
        result += p + 1 + (arr[i] >= k) - ((arr[i] - left_sum) >= k);
    }

    ll *tmp = merge(arr, n / 2, arr + n / 2, n - n / 2);
    memcpy(arr, tmp, sizeof(ll) * n);
    free(tmp);
    return result;
}

//void test() {
//    int n, k;
//    scanf("%d%d", &n, &k);
//    ll *arr = malloc(n * sizeof(ll));
//    ll *arr2 = malloc(n * sizeof(ll));
//    for (int i = 0; i < n; ++i) {
//        scanf("%lld", &arr[i]);
//        arr2[i] = arr[i];
//    }
//    for (int i = 1; i < n; i++) {
//        arr[i] = arr[i] + arr[i - 1];
//        arr2[i] = arr[i];
//    }
//    printf("%lld", solve(arr, n, k, arr2));
//}

signed main() {
    ll n, k;
    scanf("%lld%lld%u%u", &n, &k, &a, &b);
    ll *arr = malloc(n * sizeof(ll));
    ll *arr2 = malloc(n * sizeof(ll));
    arr[0] = (int)rand32();
    arr2[0] = arr[0];
    for (int i = 1; i < n; i++) {
        arr[i] = (int)rand32() + arr[i - 1];
        arr2[i] = arr[i];
    }
    printf("%lld", solve(arr, n, k, arr2));
}
