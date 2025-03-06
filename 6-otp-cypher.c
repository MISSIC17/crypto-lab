#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100

void generateKey(char text[], char key[]) {
  int len = strlen(text);
  srand(time(NULL));
  for (int i = 0; i < len; i++) {
    key[i] = 'A' + rand() % 26;
  }
  key[len] = '\0';
}

void otpCipher(char text[], char key[], char result[]) {
  int len = strlen(text);
  for (int i = 0; i < len; i++) {
    result[i] = text[i] ^ key[i];
  }
  result[len] = '\0';
}
int main() {

  char text[MAX], key[MAX], encryptedText[MAX], decryptedText[MAX];
  printf("Enter the text:::> ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';
  generateKey(text, key);
  printf("Generated key:::> %s\n", key);
  otpCipher(text, key, encryptedText);
  printf("Encrypted text (ASCII values):::> ");
  for (int i = 0; i < strlen(encryptedText); i++) {
    printf("%d ", encryptedText[i]);
  }
  printf("\n");
  otpCipher(encryptedText, key, decryptedText);
  printf("Decrypted text:::> %s\n", decryptedText);
  return 0;
}
