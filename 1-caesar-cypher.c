#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
char *encrypt(char *, int);
char *decrypt(char *, int);

int main() {
  int shift_value;
  char user_input[MAX];
  printf("Enter shift value:::>");
  scanf("%d", &shift_value);
  printf("Enter the value to be encrypted(only alpbhanum)::>");
  scanf("%s", user_input);
  int i = 0;
  while (*(user_input + i)) {
    int ascii = (int)(*(user_input + i));

    if (!isalnum(ascii)) {
      printf("\nIncorrect character value in %s\n. Must be alpbhabet and "
             "numbers only\n",
             user_input);
      return 0;
    }
    i++;
  }

  char result[100];
  char *encrypted = encrypt(user_input, shift_value);
  char *decrypted = decrypt(encrypted, shift_value);
  printf("\nThe message is %s\n", user_input);
  printf("\nThe encrypted message is %s\n", encrypted);
  printf("\nThe decrypted message is %s\n", decrypted);
  free(encrypted);
  free(decrypted);
  return 0;
}
char *encrypt(char *c, int shift_value) {

  char *result = (char *)malloc(sizeof(char) * MAX);
  int i = 0;
  while (*(c + i)) {
    int ascii = (int)(*(c + i));
    if (isdigit(ascii)) {
      result[i] = (char)(ascii - '0' + shift_value) % 10 + '0';
    } else if (isupper(ascii)) {

      result[i] = (char)((ascii - 'A' + shift_value)) % 26 + 'A';
    } else {

      result[i] = (char)(((ascii - 'a') + shift_value)) % 26 + 'a';
    }
    i++;
  }
  return result;
}

char *decrypt(char *c, int shift_value) {
  char *result = (char *)malloc(sizeof(char) * MAX);
  int i = 0;
  while (*(c + i)) {
    int ascii = (int)(*(c + i));
    if (isdigit(ascii)) {
      result[i] = (char)(ascii - '0' - shift_value + 10) % 10 + '0';

    } else if (isupper(ascii)) {
      result[i] = (char)(ascii - 'A' - shift_value + 26) % 26 + 'A';

    } else {
      result[i] = (char)(ascii - 'a' - shift_value + 26) % 26 + 'a';
    }
    i++;
  }
  return result;
}
