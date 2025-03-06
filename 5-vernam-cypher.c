#include <stdio.h>
#include <string.h>
void printInBinary(unsigned char num) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
}
void vernamCipher(char text[], char key[], char result[]) {
  int len = strlen(text);
  for (int i = 0; i < len; i++) {
    result[i] = text[i] ^ key[i];
  }
  result[len] = '\0';
}
int main() {

  char text[100], key[100], encryptedText[100], decryptedText[100];
  printf("Enter text:::> ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';
  printf("Enter key (same length as text):::> ");
  fgets(key, sizeof(key), stdin);
  key[strcspn(key, "\n")] = '\0';
  if (strlen(text) != strlen(key)) {
    printf("Error! Key length must be equal to text length.\n");
    return 1;
  }
  vernamCipher(text, key, encryptedText);
  printf("Encrypted text (in binary): ");
  for (int i = 0; i < strlen(encryptedText); i++) {
    printInBinary(encryptedText[i]);
    printf(" ");
  }
  printf("\n");
  vernamCipher(encryptedText, key, decryptedText);
  printf("Decrypted text: %s\n", decryptedText);
  return 0;
}
