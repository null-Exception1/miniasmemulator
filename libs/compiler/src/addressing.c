#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parser(char *string, int *offset, bool *deref, char *var_name) {
  int j = 0;
  bool numeric = true;
  while (string[j] != '\0') {
    if (!isdigit((unsigned char)string[j])) {
      numeric = false;
    }
    j++;
  }
  // printf("var name %s \n", string);
  if (!numeric) {
    int len = strlen(string);
    int start_idx = 0;

    if (string[0] == '[' && string[len - 1] == ']') {
      *deref = true;
      start_idx = 1;
    } else {
      *deref = false;
      start_idx = 0;
    }

    char name[10] = {0};
    int i;
    int name_ptr = 0;

    for (i = start_idx;
         i < len && string[i] != '+' && string[i] != '-' && string[i] != ']';
         i++) {
      if (name_ptr < 9) {
        name[name_ptr++] = string[i];
      }
    }
    name[name_ptr] = '\0';
    strcpy(var_name, name);

    if (i < len && (string[i] == '+' || string[i] == '-')) {
      int multiplier = (string[i] == '-') ? -1 : 1;
      i++;

      char offset_str[10] = {0};
      int offset_ptr = 0;

      for (; i < len && string[i] != ']'; i++) {
        if (offset_ptr < 9) {
          offset_str[offset_ptr++] = string[i];
        }
      }
      offset_str[offset_ptr] = '\0';

      *offset = atoi(offset_str) * multiplier;
    } else {
      *offset = 0;
    }
  } else {
    strcpy(var_name, string);
  }
}