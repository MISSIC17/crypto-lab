#include <stdio.h>
#include <string.h>
#define SIZE 3
int modInverse(int a, int m) {
  a = a % m;
  if (a < 0)
    a += m;
  for (int x = 1; x < m; x++) {
    if ((a * x) % m == 1) {
      return x;
    }
  }
  return -1;
}
int determinant(int matrix[SIZE][SIZE]) {
  return (matrix[0][0] *
              (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
          matrix[0][1] *
              (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
          matrix[0][2] *
              (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]));
}
int inverseMatrix(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
  int det = determinant(matrix) % 26;
  if (det < 0)
    det += 26;
  int detInverse = modInverse(det, 26);
  if (detInverse == -1) {
    printf("Inverse does not exist. Please enter a different key matrix.\n");
    return 0;
  }
  int adj[SIZE][SIZE];
  adj[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
  adj[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
  adj[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
  adj[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
  adj[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
  adj[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
  adj[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
  adj[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
  adj[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      inverse[i][j] = (adj[i][j] * detInverse) % 26;
      if (inverse[i][j] < 0)
        inverse[i][j] += 26;
    }
  }
  return 1;
}
void encrypt(char text[], int key[SIZE][SIZE], char encrypted[]) {
  int len = strlen(text);
  int k = 0;
  for (int i = 0; i < len; i += SIZE) {
    int block[SIZE] = {0, 0, 0};
    for (int j = 0; j < SIZE && i + j < len; j++) {
      block[j] = text[i + j] - 'A';
    }
    for (int j = 0; j < SIZE; j++) {
      encrypted[k++] =
          (key[j][0] * block[0] + key[j][1] * block[1] + key[j][2] * block[2]) %
              26 +
          'A';
    }
  }
  encrypted[k] = '\0';
}
void decrypt(char encrypted[], int key[SIZE][SIZE], char decrypted[],
             int original_length) {
  int len = strlen(encrypted);
  int k = 0;
  int inverse[SIZE][SIZE];
  if (!inverseMatrix(key, inverse))
    return;
  for (int i = 0; i < len; i += SIZE) {
    int block[SIZE] = {0, 0, 0};
    for (int j = 0; j < SIZE && i + j < len; j++) {
      block[j] = encrypted[i + j] - 'A';
    }
    for (int j = 0; j < SIZE; j++) {
      decrypted[k++] = (inverse[j][0] * block[0] + inverse[j][1] * block[1] +
                        inverse[j][2] * block[2]) %
                           26 +
                       'A';
    }
  }
  decrypted[original_length] = '\0';
}
int main() {

  char text[100], encrypted[100], decrypted[100];
  int key[SIZE][SIZE];
  printf("Enter key matrix (3x3 of integers)::\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("(%d,%d)::>", i + 1, j + 1);
      scanf("%d", &key[i][j]);
    }
  }
  getchar();
  printf("Enter the text to encrypt in uppercase :::> ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';
  int original_length = strlen(text);
  encrypt(text, key, encrypted);
  printf("Encrypted text: %s\n", encrypted);
  decrypt(encrypted, key, decrypted, original_length);
  printf("Decrypted text: %s\n", decrypted);
  return 0;
}
