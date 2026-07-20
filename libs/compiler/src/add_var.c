#include <globals.h>
#include <string.h>

void add_var(char *name, Memory *memory, int size, unsigned char *value,
             int *var_ptr, Variable *vartoaddr) {

  Variable variable;

  // add variable name
  strncpy(variable.name, name, 10);

  // add address of it in the malloc and size
  variable.address = var_ptr + *var_ptr;
  variable.size = size;

  // implement into memeory
  memcpy(memory->data_ptr, value, size);

  // implement into malloc
  memcpy(vartoaddr + *var_ptr, &variable, sizeof(Variable));

  // increase the ptrs
  (*var_ptr)++;
  memory->data_ptr = memory->data_ptr + size;
}