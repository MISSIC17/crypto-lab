#include <stdio.h>
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}
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
int computeModularInverse(int e, int phi) {
  int t = 0, newT = 1;
  int r = phi, newR = e;
  while (newR != 0) {
    int quotient = r / newR;
    int temp = newT;
    newT = t - quotient * newT;
    t = temp;
    temp = newR;
    newR = r - quotient * newR;
    r = temp;
  }
  if (r > 1)
    return -1;
  if (t < 0)
    t += phi;
  return t;
}
int main() {
  int prime1, prime2, n, phi, publicKey, privateKey, message;
  long long encryptedText, decryptedText;
  printf("Enter two prime numbers:::> ");
  scanf("%d %d", &prime1, &prime2);
  n = prime1 * prime2;
  phi = (prime1 - 1) * (prime2 - 1);
  publicKey = 2;
  while (publicKey < phi && gcd(publicKey, phi) != 1) {
    publicKey++;
  }
  privateKey = computeModularInverse(publicKey, phi);
  if (privateKey == -1) {
    printf("Error! No modular inverse found for e. Choose different primes.\n");
    return 1;
  }
  printf("Public Key (e, n): (%d, %d)\n", publicKey, n);
  printf("Private Key (d, n): (%d, %d)\n", privateKey, n);
  printf("Enter a message (integer less than %d) to encrypt:::> ", n);
  scanf("%d", &message);
  if (message >= n) {
    printf("Error! Message should be smaller than n.\n");
    return 1;
  }
  encryptedText = modularExponentiation(message, publicKey, n);
  printf("Encrypted Text: %lld\n", encryptedText);
  decryptedText = modularExponentiation(encryptedText, privateKey, n);
  printf("Decrypted Text: %lld\n", decryptedText);
  return 0;
}
