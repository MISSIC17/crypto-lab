#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char *encrypt(char *, int);
char *decrypt(char *, int);

int main() {
  char text[MAX];
  int rail;
  printf("Enter the depth of rail fence::>");
  scanf("%d", &rail);
  printf("Enter the text to be encrypted:::> ");
  scanf("%s", text);
  char *encrypted = encrypt(text, rail);
  char *decrypted = decrypt(encrypted, rail);
  printf("\nThe encrypted text is %s\n", encrypted);
  printf("\nThe decrypted text is %s\n", decrypted);
  free(encrypted);
  free(decrypted);

  return 0;
}
char *encrypt(char *text, int rail) {
  int len = (int)strlen(text);
  char diagonal_matrix[rail][len];

  for (int i = 0; i < rail; i++) {
    for (int j = 0; j < len; j++) {
      diagonal_matrix[i][j] = '0';
    }
  }

  int dir = 1, row = 0;
  for (int i = 0; i < len; i++) {
    diagonal_matrix[row][i] = text[i];
    if (row == 0) {
      dir = 1;
    } else if (row == rail - 1) {
      dir = -1;
    }
    row += dir;
  }
  printf("\n");
  for (int i = 0; i < rail; i++) {
    printf("|\t");
    for (int j = 0; j < len; j++) {
      printf("%c\t", diagonal_matrix[i][j]);
    }
    printf("|\n");
  }
  char *result = (char *)malloc(sizeof(char) * MAX);

  int result_index = 0;
  //  row = 0, dir = 1;

  for (int i = 0; i < rail; i++) {
    for (int j = 0; j < len; j++) {

      if (diagonal_matrix[i][j] != '0') {
        result[result_index] = diagonal_matrix[i][j];
        result_index++;
      }
    }
  }
  result[result_index] = '\0';
  return result;
}

char *decrypt(char *text, int rail) {
  int len = (int)strlen(text);

  char diagonal_matrix[rail][len];

  for (int i = 0; i < rail; i++) {
    for (int j = 0; j < len; j++) {
      diagonal_matrix[i][j] = '0';
    }
  }
  int index = 0;

  int dir = 1, row = 0;
  for (int i = 0; i < len; i++) {
    diagonal_matrix[row][i] = '*';
    index++;
    if (row == 0) {
      dir = 1;
    } else if (row == rail - 1) {
      dir = -1;
    }
    row += dir;
  }
  char *result = (char *)malloc(sizeof(char) * MAX);
  int result_index = 0;
  for (int i = 0; i < rail; i++) {
    for (int j = 0; j < len; j++) {
      if (diagonal_matrix[i][j] == '*') {
        diagonal_matrix[i][j] = text[result_index];
        result_index++;
      }
    }
  }
  row = 0, dir = 1;
  for (int i = 0; i < len; i++) {
    result[i] = diagonal_matrix[row][i];
    if (row == 0) {
      dir = 1;
    } else if (row == rail - 1) {
      dir = -1;
    }
    row += dir;
  }

  result[result_index] = '\0';
  return result;
}
