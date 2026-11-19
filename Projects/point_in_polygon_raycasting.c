#include <stdio.h>
#include <assert.h>

/*
 * Determines the position of point M(xM, yM) relative to a simple polygon
 * using horizontal ray casting and integer orientation determinants.
 * Returns:
 *    1  if M is strictly inside the polygon
 *   -1  if M is strictly outside the polygon
 *    0  if M lies on a polygon edge or vertex
 */
int point_in_poly(const int *X, const int *Y, int n, int xM, int yM) {
    int cross_count = 0;

    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        int x1 = X[i], y1 = Y[i];
        int x2 = X[next], y2 = Y[next];

        /* Handle horizontal edges */
        if (y1 == y2) {
            if (yM == y1 && (xM - x1) * (xM - x2) <= 0) {
                return 0; /* Point lies on horizontal edge */
            }
        } else {
            /* Order endpoints vertically so A is the lower vertex and B is the upper vertex */
            int xa, ya, xb, yb;
            if (y1 > y2) {
                xa = x2; ya = y2;
                xb = x1; yb = y1;
            } else {
                xa = x1; ya = y1;
                xb = x2; yb = y2;
            }

            /* Orientation determinant of triangle (M, A, B) */
            int det = xM * (ya - yb) + xa * (yb - yM) + xb * (yM - ya);

            /* Check if M lies exactly on the non-horizontal edge */
            if (det == 0 && (yM - ya) * (yM - yb) <= 0) {
                return 0;
            }

            /*
             * Ray cast to the right: det > 0 ensures M is to the left of directed edge AB;
             * half-open interval [ya, yb) prevents double-counting shared vertices.
             */
            if (det > 0 && yM >= ya && yM < yb) {
                cross_count++;
            }
        }
    }

    return (cross_count % 2 != 0) ? 1 : -1;
}

int main(void) {
    /* 14-vertex simple non-convex polygon (P1 -> P14) */
    int X[] = {10, 11, 12, 13, 14, 16, 20, 16,  4, 1, 3, 5,  6, 8};
    int Y[] = { 4,  6,  2,  9,  6,  8,  4, 14, 14, 2, 6, 6, 11, 6};
    int n = 14;

    assert(point_in_poly(X, Y, n,  4, 6) ==  0); /* On horizontal edge P11-P12 */
    assert(point_in_poly(X, Y, n,  9, 6) ==  1); /* Interior (5 crossings) */
    assert(point_in_poly(X, Y, n, 13, 6) == -1); /* Exterior concave pocket below P4 (4 crossings) */
    assert(point_in_poly(X, Y, n,  7, 6) == -1); /* Exterior concave pocket below P13 (6 crossings) */
    assert(point_in_poly(X, Y, n, 14, 6) ==  0); /* Boundary vertex P5 */
    assert(point_in_poly(X, Y, n, 15, 6) == -1); /* Exterior below P5-P6-P7 (2 crossings) */
    assert(point_in_poly(X, Y, n, 12, 6) ==  1); /* Interior above P3 (5 crossings) */
    assert(point_in_poly(X, Y, n, 12, 8) ==  1); /* Interior upper region (3 crossings) */
    assert(point_in_poly(X, Y, n, 15, 8) ==  1); /* Interior near P6 (1 crossing) */
    assert(point_in_poly(X, Y, n, 17, 6) == -1); /* Exterior below P6-P7 (2 crossings) */

    printf("All point-in-polygon ray casting tests passed.\n");
    return 0;
}
