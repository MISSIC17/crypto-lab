#include <stdio.h>
int extendedEuclidean(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  int x1, y1;
  int gcd = extendedEuclidean(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}
int main() {

  int a, b, x, y, gcd;
  printf("Enter two numbers: ");
  scanf("%d %d", &a, &b);
  gcd = extendedEuclidean(a, b, &x, &y);
  printf("GCD of %d and %d is: %d\n", a, b, gcd);
  printf("Coefficients x and y are: %d, %d\n", x, y);
  return 0;
}
