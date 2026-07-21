#include <globals.h>
#include <stdbool.h>
#include <string.h>
Variable *get_var(char *name, Variable *vartoaddr, Memory *memory,
                  int var_ptr) {
  for (int i = 0; i < var_ptr; i++) {
    Variable *curr_var = vartoaddr + i;
    if (strcmp(curr_var->name, name) == 0) {
      return curr_var;
    }
  }
  return NULL;
}