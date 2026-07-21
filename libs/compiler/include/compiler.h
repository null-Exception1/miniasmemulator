#ifndef COMPILER_H
#define COMPILER_H
#include "globals.h"
void add_var(char *name, Memory *memory, int size, unsigned char *value,
             int *var_ptr, Variable *vartoaddr, Type type);
Variable *get_var(char *name, Variable *vartoaddr, Memory *memory, int var_ptr);
#endif