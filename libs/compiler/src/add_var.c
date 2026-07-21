#include <globals.h>
#include <string.h>

void add_var(char *name, Memory *memory, int size, unsigned char *value,
             int *var_ptr, Variable *vartoaddr, Type type) {

  Variable variable;

  // add variable name
  strncpy(variable.name, name, 10);

  // add address of it in the malloc and size
  variable.address = memory->data_ptr;
  variable.size = size;
  variable.var_type = type;

  // implement into memeory
  switch (type) {
  case INT:
    memcpy((int *)memory->data_ptr, (int *)value, size);
    break;
  case CHAR:
    memcpy((char *)memory->data_ptr, (char *)value, size);
    break;
  case DOUBLE:
    memcpy((double *)memory->data_ptr, (double *)value, size);
    break;
  case LONG:
    memcpy((long *)memory->data_ptr, (long *)value, size);
    break;
  case LONG_LONG:
    memcpy((long long *)memory->data_ptr, (long long *)value, size);
    break;
  }

  // implement into malloc
  memcpy(vartoaddr + *var_ptr, &variable, sizeof(Variable));

  // increase the ptrs
  (*var_ptr)++;
  memory->data_ptr = memory->data_ptr + size;
}