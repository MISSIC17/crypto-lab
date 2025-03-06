#include <stdio.h>
int modularExponentiation(int base, int exp, int mod) {
  int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}
int isPrimitiveRoot(int g, int prime) {
  int powers[prime - 1];
  for (int i = 0; i < prime - 1; i++) {
    powers[i] = modularExponentiation(g, i + 1, prime);
  }
  int visited[prime];
  for (int i = 0; i < prime; i++)
    visited[i] = 0;
  for (int i = 0; i < prime - 1; i++) {
    if (visited[powers[i]] == 1) {
      return 0;
    }
    visited[powers[i]] = 1;
  }
  return 1;
}
int findPrimitiveRoot(int prime) {
  for (int g = 2; g < prime; g++) {
    if (isPrimitiveRoot(g, prime)) {
      return g;
    }
  }
  return -1;
}
int main() {

  int prime;
  printf("Enter a prime number:::>");
  scanf("%d", &prime);
  int primitiveRoot = findPrimitiveRoot(prime);
  if (primitiveRoot != -1) {
    printf("The smallest primitive root of %d is:::> %d\n", prime,
           primitiveRoot);
  } else {
    printf("No primitive root found (ensure input is prime).\n");
  }
  return 0;
}
