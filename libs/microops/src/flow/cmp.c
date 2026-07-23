#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline void op(int a, int b) {
  // simulating alu subtraction here cuz im too lazy to recreate the fking
  // alu right now
  int res = a - b;

  uint32_t ua = (uint32_t)a;
  uint32_t ub = (uint32_t)b;

  flags.zero_flag = (res == 0) ? 1 : 0;
  flags.sign_flag = (res < 0) ? 1 : 0;
  flags.carry_flag = (ua < ub) ? 1 : 0;
  if ((a > 0 && b < 0 && res < 0) || (a < 0 && b > 0 && res > 0)) {
    flags.overflow_flag = 1;
  } else {
    flags.overflow_flag = 0;
  }
}

static void offset_and_write_reg(unsigned char *offset_addr1,
                                 unsigned char *offset_addr2, int offset1,
                                 int offset2, bool deref1, bool deref2,
                                 Variable *ptr, Register *dest_reg) {

  if (ptr->is_immediate == true) {
    op(*(int *)dest_reg->value, immediate_val);
  } else {
    int addr_as_int = (int)(ptr->address - memory.data);

    if (deref1) {
      offset_addr1 = offset_addr1 + offset1;
    } else {
      op(*(int *)offset_addr2, addr_as_int);
      return;
    }

    if (deref2 && deref1) {
      fprintf(stderr, "Asm Error: mem to mem not allowed!");
      exit(1);
    }

    op(*(int *)offset_addr2, *(int *)offset_addr1);
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

  op(*(int *)offset_addr2, *(int *)offset_addr1);
}
static void offset_and_write_reg_from_reg(Register *dest_reg, Register *src_reg,
                                          int offset2, bool deref2) {
  if (deref2) { // has dest been dereferenced
    int calc = *(int *)(memory.data + *(int *)dest_reg->value + offset2);
    op(calc, *src_reg->value);
  } else {
    op(*dest_reg->value, *src_reg->value);
  }
}

void cmp_(char *dest_addr, char *src_addr) {
  operand_parse(dest_addr, src_addr, offset_and_write_reg,
                offset_and_write_addr, offset_and_write_reg_from_reg);
}