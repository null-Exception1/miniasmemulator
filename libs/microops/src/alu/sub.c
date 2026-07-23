#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int op(int a, int b) {
  if (a - b < 0) {
    flags.sign_flag = 1;
    flags.carry_flag = 0;
    flags.zero_flag = 0;
  } else if (a - b > 0) {
    flags.sign_flag = 0;
    flags.carry_flag = 1;
    flags.zero_flag = 0;
  } else if (a - b == 0) {
    flags.sign_flag = 0;
    flags.carry_flag = 0;
    flags.zero_flag = 1;
  }
  return a - b;
}

static void offset_and_write_reg(unsigned char *offset_addr1,
                                 unsigned char *offset_addr2, int offset1,
                                 int offset2, bool deref1, bool deref2,
                                 Variable *ptr, Register *dest_reg) {

  if (ptr->is_immediate == true) {
    int res = op(*(int *)dest_reg->value, immediate_val);
    memcpy(dest_reg->value, &res, 4);
  } else {
    int addr_as_int = (int)(ptr->address - memory.data);

    if (deref1) {
      offset_addr1 = offset_addr1 + offset1;
    } else {
      int res = op(*(int *)offset_addr2, addr_as_int);
      memcpy(offset_addr2, &res, ptr->size);
      return;
    }

    if (deref2 && deref1) {
      fprintf(stderr, "Asm Error: mem to mem not allowed!");
      exit(1);
    }

    int res = op(*(int *)offset_addr2, *(int *)offset_addr1);
    memcpy(offset_addr2, &res, ptr->size);
  }
}
static void offset_and_write_addr(unsigned char *offset_addr1,
                                  unsigned char *offset_addr2, int offset1,
                                  int offset2, bool deref1, bool deref2,
                                  Variable *ptr) {

  if (deref2) {
    offset_addr2 = offset_addr2 + offset2;
  } else {
    offset_addr2 = ptr->address + offset2;
  }

  int res = op(*(int *)offset_addr2, *(int *)offset_addr1);
  memcpy(offset_addr2, &res, ptr->size);
}
static void offset_and_write_reg_from_reg(Register *dest_reg, Register *src_reg,
                                          int offset2, bool deref2) {
  if (deref2) { // has dest been dereferenced
    int calc = *(int *)(memory.data + *(int *)dest_reg->value + offset2);
    int res = op(calc, *src_reg->value);
    memcpy(memory.data + *(int *)dest_reg->value + offset2, &res, 4);
  } else {
    int res = op(*dest_reg->value, *src_reg->value);
    memcpy(dest_reg->value, &res, 4);
  }
}

void sub_(char *dest_addr, char *src_addr) {
  operand_parse(dest_addr, src_addr, offset_and_write_reg,
                offset_and_write_addr, offset_and_write_reg_from_reg);
}
