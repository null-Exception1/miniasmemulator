#include <compiler.h>
#include <globals.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operand_parse(char *dest_addr, char *src_addr,
                   write_reg offset_and_write_reg,
                   write_addr offset_and_write_addr,
                   write_reg_from_reg offset_and_write_reg_from_reg) {

  int offset1 = 0;
  bool deref1 = false;
  char name1[10];
  parser(src_addr, &offset1, &deref1, name1);

  int offset2 = 0;
  bool deref2 = false;
  char name2[10];
  parser(dest_addr, &offset2, &deref2, name2);

  bool destreg = false;

  Register *dest_reg;
  if (get_register(name2) != NULL) {
    dest_reg = get_register(name2);
    destreg = true;
  }

  bool srcreg = false;
  Register *src_reg;
  if (get_register(name1) != NULL) {
    src_reg = get_register(name1);
    srcreg = true;
  }

  if (srcreg && destreg) {
    offset_and_write_reg_from_reg(dest_reg, src_reg, offset2, deref2);

  } else if (destreg && !srcreg) {
    // need this
    Variable *ptr = get_var(name1, vartoaddr, &memory, var_ptr);

    if (!ptr) {
      fprintf(stderr, "Asm Error: Label/Value '%s' not found!\n", name1);
      exit(1);
    }

    unsigned char *offset_addr1 = ptr->address;
    unsigned char *offset_addr2 = dest_reg->value;

    offset_and_write_reg(offset_addr1, offset_addr2, offset1, offset2, deref1,
                         deref2, ptr, dest_reg);

  } else if (!destreg && srcreg) {

    if (!deref2) {
      fprintf(
          stderr,
          "Asm Error: Destination must be dereferenced! Did you mean [%s]?\n",
          dest_addr);
      exit(1);
    }

    Variable *ptr = get_var(name2, vartoaddr, &memory, var_ptr);

    if (!ptr) {
      fprintf(stderr, "Asm Error: Label/Value '%s' not found!\n", name2);
      exit(1);
    }
    unsigned char *offset_addr1 = src_reg->value;
    unsigned char *offset_addr2 = ptr->address;

    offset_and_write_addr(offset_addr1, offset_addr2, offset1, offset2, deref1,
                          deref2, ptr);
  } else {
    fprintf(stderr,
            "Asm Error: Invalid memory-to-memory operation or bad syntax! "
            "(e.g., mov [var1], [var2] is not supported by x86 hardware)\n");
    exit(1);
  }
}