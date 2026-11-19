# Computational-Geometry-Localization
Projects from Computational Geometrry

# Computational Geometry – Spatial Localization Algorithms

Pure C implementations of fundamental planar localization algorithms using exact integer orientation determinants (avoiding floating-point precision issues) and comprehensive `assert`-based unit tests.

## Implemented Algorithms

### 1. Collinear Triplets Detection (`collinear_triplets_3sum.c`)
- **Problem:** Given three sets $A, B, C$ of size $n$ representing points on three parallel lines, determine whether there exists a collinear triplet $(a, b, c)$ satisfying $a + c = 2b$.
- **Approach:** Reduces the problem to a sorted two-pointer intersection pass in $O(n^2)$ time and $O(n)$ auxiliary memory after $O(n \log n)$ sorting via `qsort`.

### 2. Triangle Planar Region Classification (`triangle_region_location.c`)
- **Problem:** Classify any query point $M(x, y)$ relative to a triangle $ABC$ into one of the **19 distinct planar regions** (interior, 3 edges, 3 vertices, 6 edge extensions, and 6 exterior regions).
- **Approach:** Evaluates 2D cross-product orientation determinants ($d, d_1, d_2, d_3$) in $O(1)$ time, handling both counter-clockwise ($d > 0$) and clockwise ($d < 0$) vertex orderings as well as degenerate collinear triangles ($d = 0$).

### 3. Point-in-Polygon Localization (`point_in_polygon_raycasting.c`)
- **Problem:** Determine whether a query point $M(x, y)$ lies strictly inside, strictly outside, or directly on the boundary of an arbitrary non-convex simple polygon.
- **Approach:** Implements horizontal ray casting ($O(n)$ time) paired with integer orientation determinants and half-open vertical intervals $[y_a, y_b)$ to handle horizontal edges, concave pockets, and vertex intersections without double counting.

## Build & Run

Compile any module with `gcc` and run its unit test suite:

```bash
gcc -Wall -Wextra -O2 collinear_triplets_3sum.c -o collinear && ./collinear
gcc -Wall -Wextra -O2 triangle_region_location.c -o triangle && ./triangle
gcc -Wall -Wextra -O2 point_in_polygon_raycasting.c -o polygon && ./polygon
