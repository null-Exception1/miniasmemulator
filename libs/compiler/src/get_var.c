#include <globals.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Variable *get_var(char *name, Variable *vartoaddr, Memory *memory,
                  int var_ptr) {
  if (name[0] >= '0' && name[0] <= '9' || name[0] == '-') {
    static Variable imm_var;
    int raw_val = atoi(name);

    memcpy(&imm_var.address, &raw_val, 4);
    imm_var.size = 4;
    imm_var.is_immediate = true;
    return &imm_var;
  }
  for (int i = 0; i < var_ptr; i++) {
    Variable *curr_var = vartoaddr + i;
    if (strcmp(curr_var->name, name) == 0) {
      return curr_var;
    }
  }
  return NULL;
}