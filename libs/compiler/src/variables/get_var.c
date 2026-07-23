#include <globals.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static Variable imm_var;
// int immediate_val;
Variable *get_var(char *name, Variable *vartoaddr, Memory *memory,
                  int var_ptr) {
  if (name[0] >= '0' && name[0] <= '9' || name[0] == '-') {
    int raw_val = atoi(name);
    memcpy(&immediate_val, &raw_val, 4);
    imm_var.is_immediate = true;
    imm_var.size = 4;
    return &imm_var;
  } else {

    for (int i = 0; i < var_ptr; i++) {
      Variable *curr_var = vartoaddr + i;
      if (strcmp(curr_var->name, name) == 0) {
        curr_var->is_immediate = false;
        return curr_var;
      }
    }
  }

  return NULL;
}