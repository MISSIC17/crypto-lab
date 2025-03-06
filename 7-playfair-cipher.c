#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define SIZE 5

char keyMatrix[SIZE][SIZE];
void generateKeyMatrix(char key[]) {
  int map[26] = {0};
  int row = 0, col = 0;
  for (int i = 0; i < strlen(key); i++) {
    char ch = toupper(key[i]);
    if (ch == 'J')
      ch = 'I';
    if (!map[ch - 'A']) {
      keyMatrix[row][col++] = ch;
      map[ch - 'A'] = 1;
      if (col == SIZE) {
        col = 0;
        row++;
      }
    }
  }
  for (char ch = 'A'; ch <= 'Z'; ch++) {
    if (ch == 'J')
      continue;
    if (!map[ch - 'A']) {
      keyMatrix[row][col++] = ch;
      map[ch - 'A'] = 1;
      if (col == SIZE) {
        col = 0;
        row++;
      }
    }
  }
}

void findPosition(char ch, int *row, int *col) {
  if (ch == 'J')
    ch = 'I';
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (keyMatrix[i][j] == ch) {
        *row = i;
        *col = j;
        return;
      }
    }
  }
}

void formatText(char text[]) {
  int len = strlen(text);
  int i, j = 0;
  char formattedText[100];
  for (i = 0; i < len; i++) {
    if (isalpha(text[i])) {
      formattedText[j++] = toupper(text[i]);
    }
  }
  formattedText[j] = '\0';
  char finalText[100];
  int k = 0;
  for (i = 0; i < j; i++) {
    finalText[k++] = formattedText[i];
    if (i < j - 1 && formattedText[i] == formattedText[i + 1]) {
      finalText[k++] = 'X';
    }
  }
  if (k % 2 != 0)
    finalText[k++] = 'X';
  finalText[k] = '\0';
  strcpy(text, finalText);
}

void playfairCipher(char text[], char result[], int encrypt) {
  int len = strlen(text);
  for (int i = 0; i < len; i += 2) {
    int r1, c1, r2, c2;
    findPosition(text[i], &r1, &c1);
    findPosition(text[i + 1], &r2, &c2);
    if (r1 == r2) {
      c1 = (c1 + encrypt + SIZE) % SIZE;
      c2 = (c2 + encrypt + SIZE) % SIZE;
    } else if (c1 == c2) {
      r1 = (r1 + encrypt + SIZE) % SIZE;
      r2 = (r2 + encrypt + SIZE) % SIZE;
    } else {
      int temp = c1;
      c1 = c2;
      c2 = temp;
    }
    result[i] = keyMatrix[r1][c1];
    result[i + 1] = keyMatrix[r2][c2];
  }
  result[len] = '\0';
}

int main() {

  char key[100], text[100], encryptedText[100], decryptedText[100];
  printf("Enter the key:::> ");
  fgets(key, sizeof(key), stdin);
  key[strcspn(key, "\n")] = '\0';
  printf("Enter text :::> ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';
  generateKeyMatrix(key);
  formatText(text);
  playfairCipher(text, encryptedText, 1);
  printf("Encrypted text:::> %s\n", encryptedText);
  playfairCipher(encryptedText, decryptedText, -1);
  printf("Decrypted text:::> %s\n", decryptedText);
  return 0;
}
