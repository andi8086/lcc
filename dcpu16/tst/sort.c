#include <dcpulib.h>

int in[] = {10, 32, -1, 567, 3, 18, 1, -51, 789, 0};
int insz = (sizeof in)/(sizeof in[0]);
main() {
    sort(in, insz);
    return 0;
}

int *xx;

print() {
    unsigned i;
    for (i = 0; i < insz; i++) {
        printf("%d ", in[i]);
    }
    printf("\n");
}

/* sort - sort a[0..n-1] into increasing order */
sort(a, n) int a[]; {
    quick(xx = a, 0, --n);
}

/* quick - quicksort a[lb..ub] */
quick(a, lb, ub) int a[]; {
    int k, partition();

    if (lb >= ub)
        return;
    k = partition(a, lb, ub);
    quick(a, lb, k - 1);
    quick(a, k + 1, ub);
}

/* partition - partition a[i..j] */
int partition(a, i, j) int a[]; {
    int v, k;

    j++;
    k = i;
    v = a[k];
    while (i < j) {
        i++; while (a[i] < v) i++;
        j--; while (a[j] > v) j--;
        if (i < j) exchange(&a[i], &a[j]);
    }
    exchange(&a[k], &a[j]);
    return j;
}

/* exchange - exchange *x and *y */
exchange(x, y) int *x, *y; {
    int t;

    printf("exchange(%d,%d)\n", x - (unsigned)xx, y - (unsigned)xx);
    t = *x; *x = *y; *y = t;
    print();
}
