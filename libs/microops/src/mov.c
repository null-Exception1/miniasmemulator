#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void offset_and_write_reg(unsigned char *offset_addr1,
                          unsigned char *offset_addr2, int offset1, int offset2,
                          bool deref1, bool deref2, Variable *ptr,
                          Register *dest_reg) {

  if (ptr->is_immediate == true) {
    memcpy(dest_reg->value, &immediate_val, 4);
  } else {

    int addr_as_int = (int)(ptr->address - memory.data);

    if (deref1) {
      offset_addr1 = offset_addr1 + offset1;
    } else {
      offset_addr1 = (unsigned char *)&addr_as_int;

      memcpy(offset_addr2, offset_addr1, ptr->size);
      return;
    }

    if (deref2 && deref1) {
      fprintf(stderr, "Asm Error: mem to mem not allowed!");
      exit(1);
    }

    // final write
    memcpy(offset_addr2, offset_addr1, ptr->size);
  }
}

void offset_and_write_addr(unsigned char *offset_addr1,
                           unsigned char *offset_addr2, int offset1,
                           int offset2, bool deref1, bool deref2,
                           Variable *ptr) {
  if (deref2) {
    offset_addr2 = offset_addr2 + offset2;
  } else {
    offset_addr2 = ptr->address + offset2;
  }
  memcpy(offset_addr2, offset_addr1, ptr->size);
}

void offset_and_write_reg_from_reg(Register *dest_reg, Register *src_reg,
                                   int offset2, bool deref2) {

  if (deref2) {
    memcpy(memory.data + *(int *)dest_reg->value + offset2, src_reg->value, 4);
  } else {
    memcpy(dest_reg->value, src_reg->value, 4);
  }
}

void mov_(char *dest_addr, char *src_addr) {
  operand_parse(dest_addr, src_addr, offset_and_write_reg,
                offset_and_write_addr, offset_and_write_reg_from_reg);
}
