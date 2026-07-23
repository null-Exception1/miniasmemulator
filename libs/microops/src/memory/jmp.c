#include <compiler.h>
#include <globals.h>
#include <stdio.h>
#include <string.h>
void pass() {
  int addr;
  memcpy(&addr, eip.value, 4);
  addr += sizeof(Instruction);
  memcpy(eip.value, &addr, 4);
}
void jmp_(char *dest_addr) {
  int offset = 0;
  bool deref = false;
  char name[10];
  parser(dest_addr, &offset, &deref, name);

  bool destreg = false;

  Register *dest_reg;
  if (get_register(name) != NULL) {
    dest_reg = get_register(name);
    destreg = true;
  }

  if (destreg) {
    memcpy(eip.value, dest_reg->value, 4);
  } else {
    Variable *ptr = get_var(name, vartoaddr, &memory, var_ptr);
    // int addr;
    printf(" ptr addr -> %d \n", *(int *)ptr->address);
    memcpy(eip.value, ptr->address, 4);
  }
}

void je_(char *target) {
  if (flags.zero_flag == 1) {
    jmp_(target);
    return;
  }
  pass();
}
void jne_(char *target) {

  if (flags.zero_flag == 0) {
    jmp_(target);
    return;
  }
  pass();
}

void jl_(char *target) {
  if (flags.sign_flag != flags.overflow_flag) {
    jmp_(target);
    return;
  }
  pass();
}
void jg_(char *target) {
  if (flags.zero_flag == 0 && flags.sign_flag == flags.overflow_flag) {
    jmp_(target);
    return;
  }
  pass();
}

void jb_(char *target) {
  if (flags.carry_flag == 1) {
    jmp_(target);
    return;
  }
  pass();
}
void ja_(char *target) {
  if (flags.carry_flag == 0 && flags.zero_flag == 0) {
    jmp_(target);
    return;
  }
  pass();
}
