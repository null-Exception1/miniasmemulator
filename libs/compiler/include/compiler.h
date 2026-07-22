#ifndef COMPILER_H
#define COMPILER_H
#include "globals.h"
void add_var(char *name, Memory *memory, int size, unsigned char *value,
             int *var_ptr, Variable *vartoaddr, Type type);
Variable *get_var(char *name, Variable *vartoaddr, Memory *memory, int var_ptr);
Register *get_register(const char *reg_name);
void parser(char *string, int *offset, bool *deref, char *var_name);
void operand_parse(char *dest_addr, char *src_addr,
                   write_reg offset_and_write_reg,
                   write_addr offset_and_write_addr,
                   write_reg_from_reg offset_and_write_reg_from_reg);
#endif