#include <globals.h>
#include <microops.h>
#include <stdio.h>
#include <string.h>
void read_ins(Instruction *ins) {

  printf("Instruction : %s %s, %s", ins->op, ins->operand1, ins->operand2);

  if (strcmp(ins->op, "add") == 0) {
    add_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "mul") == 0) {
    mul_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "sub") == 0) {
    sub_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "cmp") == 0) {
    cmp_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "and") == 0) {
    and_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "not") == 0) {
    not_(ins->operand1);
  }
  if (strcmp(ins->op, "or") == 0) {
    or_(ins->operand1, ins->operand2);
  }
  if (strcmp(ins->op, "xor") == 0) {
    xor_(ins->operand1, ins->operand2);
  }

  if (strcmp(ins->op, "pop") == 0) {
    pop_(ins->operand1);
  }
  if (strcmp(ins->op, "push") == 0) {
    push_(ins->operand1);
  }
  if (strcmp(ins->op, "mov") == 0) {
    mov_(ins->operand1, ins->operand2);
  }

  if (strcmp(ins->op, "cmp") == 0) {
    cmp_(ins->operand1, ins->operand2);
  }

  if (strcmp(ins->op, "jmp") == 0) {
    jmp_(ins->operand1);
  }
  if (strcmp(ins->op, "je") == 0) {
    je_(ins->operand1);
  }
  if (strcmp(ins->op, "jne") == 0) {
    jne_(ins->operand1);
  }
  if (strcmp(ins->op, "jl") == 0) {
    jl_(ins->operand1);
  }
  if (strcmp(ins->op, "jg") == 0) {
    jg_(ins->operand1);
  }
  if (strcmp(ins->op, "ja") == 0) {
    ja_(ins->operand1);
  }
  if (strcmp(ins->op, "jb") == 0) {
    jb_(ins->operand1);
  }
}