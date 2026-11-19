#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Comparator for qsort (ascending order) */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/*
 * Checks in O(n^2) time whether there exist elements A[i], B[k], C[j]
 * forming collinear points across three parallel lines (A[i] + C[j] = 2 * B[k]).
 */
int check_collinear(const int *A, const int *B, const int *C, int n) {
    int *B_double = (int *)malloc(n * sizeof(int));
    int *C_prime = (int *)malloc(n * sizeof(int));
    if (!B_double || !C_prime) {
        free(B_double);
        free(C_prime);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        B_double[i] = B[i];
        C_prime[i] = C[i];
    }

    /* Sort B and C in O(n log n) */
    qsort(B_double, n, sizeof(int), compare);
    qsort(C_prime, n, sizeof(int), compare);

    /* Compute 2 * B for direct comparison */
    for (int i = 0; i < n; i++) {
        B_double[i] *= 2;
    }

    int *D = (int *)malloc(n * sizeof(int));
    if (!D) {
        free(B_double);
        free(C_prime);
        exit(1);
    }

    /* Fix anchor A[i] and find intersection between (A[i] + C') and 2*B via two pointers */
    for (int i = 0; i < n; i++) {
        int anchor = A[i];
        for (int j = 0; j < n; j++) {
            D[j] = anchor + C_prime[j];
        }

        int idx_B = 0;
        int idx_D = 0;

        while (idx_B < n && idx_D < n) {
            if (B_double[idx_B] == D[idx_D]) {
                free(D);
                free(B_double);
                free(C_prime);
                return 1;
            } else if (B_double[idx_B] < D[idx_D]) {
                idx_B++;
            } else {
                idx_D++;
            }
        }
    }

    free(D);
    free(B_double);
    free(C_prime);
    return 0;
}

int main(void) {
    /* Test 1: Valid case (A=2, C=6 => 2 + 6 = 8 = 2 * 4) */
    int A1[] = {9, 2, 14};
    int B1[] = {10, 4, 15};
    int C1[] = {6, 20, 11};
    assert(check_collinear(A1, B1, C1, 3) == 1);

    /* Test 2: Invalid case (no valid triplet) */
    int A2[] = {1, 3, 5};
    int B2[] = {10, 12, 14};
    int C2[] = {2, 4, 6};
    assert(check_collinear(A2, B2, C2, 3) == 0);

    /* Test 3: Negative and zero coordinates (-5 + 5 = 2 * 0) */
    int A3[] = {-5, 10, -2};
    int B3[] = {3, 0, 7};
    int C3[] = {8, 5, -1};
    assert(check_collinear(A3, B3, C3, 3) == 1);

    printf("All 3SUM collinearity tests passed.\n");
    return 0;
}
