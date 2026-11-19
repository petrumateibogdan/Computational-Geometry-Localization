#include <stdio.h>
#include <assert.h>

/*
 * Classifies query point M(xM, yM) into one of the 19 planar regions induced
 * by triangle ABC using exact integer orientation determinants.
 * Returns:
 *    1 .. 19  for counter-clockwise triangle orientation (d > 0)
 *   -1 .. -19 for clockwise triangle orientation (d < 0)
 *    0        for degenerate collinear triangle (d == 0)
 */
int get_region(int xA, int yA, int xB, int yB, int xC, int yC, int xM, int yM) {
    /* Main triangle orientation determinant */
    int d = xA * (yB - yC) + xB * (yC - yA) + xC * (yA - yB);

    /* Sub-determinants relative to query point M */
    int d1 = xM * (yA - yB) + xA * (yB - yM) + xB * (yM - yA);
    int d2 = xM * (yB - yC) + xB * (yC - yM) + xC * (yM - yB);
    int d3 = xM * (yC - yA) + xC * (yA - yM) + xA * (yM - yC);

    /* Case 1: Counter-clockwise orientation (d > 0) */
    if (d > 0) {
        if (d1 > 0 && d2 > 0 && d3 > 0) return 1;
        if (d1 == 0 && d2 > 0 && d3 > 0) return 2;
        if (d1 > 0 && d2 == 0 && d3 > 0) return 3;
        if (d1 > 0 && d2 > 0 && d3 == 0) return 4;
        if (d1 == 0 && d2 > 0 && d3 == 0) return 5;
        if (d1 == 0 && d2 == 0 && d3 > 0) return 6;
        if (d1 > 0 && d2 == 0 && d3 == 0) return 7;
        if (d1 == 0 && d2 > 0 && d3 < 0) return 8;
        if (d1 < 0 && d2 > 0 && d3 == 0) return 9;
        if (d1 < 0 && d2 == 0 && d3 > 0) return 10;
        if (d1 == 0 && d2 < 0 && d3 > 0) return 11;
        if (d1 > 0 && d2 < 0 && d3 == 0) return 12;
        if (d1 > 0 && d2 == 0 && d3 < 0) return 13;
        if (d1 < 0 && d2 > 0 && d3 < 0) return 14;
        if (d1 < 0 && d2 > 0 && d3 > 0) return 15;
        if (d1 < 0 && d2 < 0 && d3 > 0) return 16;
        if (d1 > 0 && d2 < 0 && d3 > 0) return 17;
        if (d1 > 0 && d2 < 0 && d3 < 0) return 18;
        if (d1 > 0 && d2 > 0 && d3 < 0) return 19;
    }
    /* Case 2: Clockwise orientation (d < 0) */
    else if (d < 0) {
        if (d1 < 0 && d2 < 0 && d3 < 0) return -1;
        if (d1 > 0 && d2 < 0 && d3 < 0) return -2;
        if (d1 > 0 && d2 < 0 && d3 > 0) return -3;
        if (d1 < 0 && d2 < 0 && d3 > 0) return -4;
        if (d1 < 0 && d2 > 0 && d3 > 0) return -5;
        if (d1 < 0 && d2 > 0 && d3 < 0) return -6;
        if (d1 > 0 && d2 > 0 && d3 < 0) return -7;
        if (d1 > 0 && d2 == 0 && d3 < 0) return -8;
        if (d1 > 0 && d2 < 0 && d3 == 0) return -9;
        if (d1 == 0 && d2 < 0 && d3 > 0) return -10;
        if (d1 < 0 && d2 == 0 && d3 > 0) return -11;
        if (d1 < 0 && d2 > 0 && d3 == 0) return -12;
        if (d1 == 0 && d2 > 0 && d3 < 0) return -13;
        if (d1 < 0 && d2 == 0 && d3 < 0) return -14;
        if (d1 == 0 && d2 < 0 && d3 < 0) return -15;
        if (d1 < 0 && d2 < 0 && d3 == 0) return -16;
        if (d1 < 0 && d2 == 0 && d3 == 0) return -17;
        if (d1 == 0 && d2 == 0 && d3 < 0) return -18;
        if (d1 == 0 && d2 < 0 && d3 == 0) return -19;
    }

    return 0; /* Degenerate triangle */
}

int main(void) {
    /* Case 1: d > 0 (all 19 regions) */
    int x1 = 1, y1 = 1, x2 = 11, y2 = 1, x3 = 15, y3 = 15;

    assert(get_region(x1, y1, x2, y2, x3, y3, 6, 4) == 1);     /* Interior */
    assert(get_region(x1, y1, x2, y2, x3, y3, 5, 1) == 2);     /* Edge AB */
    assert(get_region(x1, y1, x2, y2, x3, y3, 13, 8) == 3);    /* Edge BC */
    assert(get_region(x1, y1, x2, y2, x3, y3, 8, 8) == 4);     /* Edge CA */
    assert(get_region(x1, y1, x2, y2, x3, y3, 1, 1) == 5);     /* Vertex A */
    assert(get_region(x1, y1, x2, y2, x3, y3, 11, 1) == 6);    /* Vertex B */
    assert(get_region(x1, y1, x2, y2, x3, y3, 15, 15) == 7);   /* Vertex C */
    assert(get_region(x1, y1, x2, y2, x3, y3, -4, 1) == 8);    /* Extension AB left */
    assert(get_region(x1, y1, x2, y2, x3, y3, 0, 0) == 9);     /* Extension CA down */
    assert(get_region(x1, y1, x2, y2, x3, y3, 9, -6) == 10);   /* Extension BC down */
    assert(get_region(x1, y1, x2, y2, x3, y3, 12, 1) == 11);   /* Extension AB right */
    assert(get_region(x1, y1, x2, y2, x3, y3, 16, 16) == 12);  /* Extension CA up */
    assert(get_region(x1, y1, x2, y2, x3, y3, 17, 22) == 13);  /* Extension BC up */
    assert(get_region(x1, y1, x2, y2, x3, y3, -5, -1) == 14);  /* Exterior opposite BC */
    assert(get_region(x1, y1, x2, y2, x3, y3, 5, -1) == 15);   /* Exterior below AB */
    assert(get_region(x1, y1, x2, y2, x3, y3, 20, 0) == 16);   /* Exterior opposite CA */
    assert(get_region(x1, y1, x2, y2, x3, y3, 20, 5) == 17);   /* Exterior right of BC */
    assert(get_region(x1, y1, x2, y2, x3, y3, 20, 30) == 18);  /* Exterior opposite AB */
    assert(get_region(x1, y1, x2, y2, x3, y3, -2, 10) == 19);  /* Exterior left of CA */

    /* Case 2: d < 0 (swapping B and C) */
    int xa = 1, ya = 1, xb = 15, yb = 15, xc = 11, yc = 1;

    assert(get_region(xa, ya, xb, yb, xc, yc, 6, 4) == -1);
    assert(get_region(xa, ya, xb, yb, xc, yc, 5, 10) == -2);
    assert(get_region(xa, ya, xb, yb, xc, yc, -5, 0) == -3);
    assert(get_region(xa, ya, xb, yb, xc, yc, 5, -1) == -4);
    assert(get_region(xa, ya, xb, yb, xc, yc, 20, 0) == -5);
    assert(get_region(xa, ya, xb, yb, xc, yc, 20, 5) == -6);
    assert(get_region(xa, ya, xb, yb, xc, yc, 20, 30) == -7);
    assert(get_region(xa, ya, xb, yb, xc, yc, 17, 22) == -8);
    assert(get_region(xa, ya, xb, yb, xc, yc, -4, 1) == -9);
    assert(get_region(xa, ya, xb, yb, xc, yc, 0, 0) == -10);
    assert(get_region(xa, ya, xb, yb, xc, yc, 9, -6) == -11);
    assert(get_region(xa, ya, xb, yb, xc, yc, 12, 1) == -12);
    assert(get_region(xa, ya, xb, yb, xc, yc, 16, 16) == -13);
    assert(get_region(xa, ya, xb, yb, xc, yc, 13, 8) == -14);
    assert(get_region(xa, ya, xb, yb, xc, yc, 8, 8) == -15);
    assert(get_region(xa, ya, xb, yb, xc, yc, 5, 1) == -16);
    assert(get_region(xa, ya, xb, yb, xc, yc, 11, 1) == -17);
    assert(get_region(xa, ya, xb, yb, xc, yc, 15, 15) == -18);
    assert(get_region(xa, ya, xb, yb, xc, yc, 1, 1) == -19);

    /* Case 3: Degenerate triangle (d == 0) */
    assert(get_region(0, 0, 5, 5, 10, 10, 2, 2) == 0);

    printf("All 39 triangle region location tests passed.\n");
    return 0;
}
