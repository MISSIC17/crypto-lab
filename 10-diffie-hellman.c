#include <stdio.h>
long long modularExponentiation(long long base, long long exp, long long mod) {
  long long result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}
int main() {

  long long prime, primitiveRoot, privateKeyA, privateKeyB, publicKeyA,
      publicKeyB, sharedKeyA, sharedKeyB;
  printf("Enter a prime number (p):::> ");
  scanf("%lld", &prime);
  printf("Enter a primitive root (g) of %lld:::> ", prime);
  scanf("%lld", &primitiveRoot);
  printf("Enter private key for User A:::> ");
  scanf("%lld", &privateKeyA);
  printf("Enter private key for User B:::> ");
  scanf("%lld", &privateKeyB);
  publicKeyA = modularExponentiation(primitiveRoot, privateKeyA, prime);
  publicKeyB = modularExponentiation(primitiveRoot, privateKeyB, prime);
  printf("User A's public key: %lld\n", publicKeyA);
  printf("User B's public key: %lld\n", publicKeyB);
  sharedKeyA = modularExponentiation(publicKeyB, privateKeyA, prime);
  sharedKeyB = modularExponentiation(publicKeyA, privateKeyB, prime);
  printf("Shared secret key computed by User A: %lld\n", sharedKeyA);
  printf("Shared secret key computed by User B: %lld\n", sharedKeyB);
  if (sharedKeyA == sharedKeyB) {
    printf("Key Exchange Successful! Shared Secret Key: %lld\n", sharedKeyA);
  } else {
    printf("Error in Key Exchange!\n");
  }
  return 0;
}
