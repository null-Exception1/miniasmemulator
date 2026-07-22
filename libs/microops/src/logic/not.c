#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void not_(char *dest_addr) {
  bool destreg = false;
  Register *dest_reg;
  if (get_register(dest_addr) != NULL) {
    dest_reg = get_register(dest_addr);
    destreg = true;
  }

  if (destreg) {
    int res = ~*(int *)dest_reg->value;
    memcpy(dest_reg->value, &res, 4); // direction addition
  } else if (!destreg) {

    int offset2;
    bool deref2;
    char name2[10];
    parser(dest_addr, &offset2, &deref2, name2);

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

    unsigned char *offset_addr2 = ptr->address;

    if (deref2) {
      offset_addr2 = offset_addr2 + offset2;
    } else {
      offset_addr2 = ptr->address + offset2;
    }

    printf("%p %s %d \n", ptr->address, ptr->name, ptr->size);

    int res = ~*(int *)offset_addr2;

    memcpy(offset_addr2, &res, ptr->size);
  } else {
    fprintf(stderr,
            "Asm Error: Invalid memory-to-memory operation or bad syntax! "
            "(e.g., not [var1] is not supported by x86 hardware)\n");
    exit(1);
  }
}
