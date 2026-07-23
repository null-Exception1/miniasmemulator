#include <globals.h>
#include <stdio.h>
#include <string.h>
void add_ins(char *op, char *operand1, char *operand2) {
  Instruction ins;

  memset(&ins, 0, sizeof(Instruction));

  strncpy(ins.op, op, 4);
  strncpy(ins.operand1, operand1, 15);
  strncpy(ins.operand2, operand2, 15);

  memcpy(memory.code_ptr, &ins, sizeof(ins));

  printf("code ptr %p \n", memory.code_ptr);

  memory.code_ptr += sizeof(ins);
}