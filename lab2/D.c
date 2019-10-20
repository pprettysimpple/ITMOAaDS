//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"

typedef double ld;

int n;
ld *a;

int calc(ld cur) {
    a[1] = cur;
    for (int i = 2; i < n; i++) {
        a[i] = 2. * a[i - 1] - a[i - 2] + 2.;
        if (a[i] < 0) return 0;
    }
    return 1;
}

signed main() {
    scanf("%d", &n);
    a = malloc(n * sizeof(ld));
    scanf("%lf", a);
    ld l = 0, r = a[0];
    for (int i = 0; i < 300; i++) {
        ld m = (l + r) / 2;
        if (calc(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    printf("%.2lf", a[n - 1]);
}