#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void div_(char *dest_addr, char *src_addr) {
  bool destreg = false;
  Register *dest_reg;
  if (get_register(dest_addr) != NULL) {
    dest_reg = get_register(dest_addr);
    destreg = true;
  }

  bool srcreg = false;
  Register *src_reg;
  if (get_register(src_addr) != NULL) {
    src_reg = get_register(src_addr);
    srcreg = true;
  }

  if (destreg && srcreg) {
    float res = *(float *)dest_reg->value / *(float *)src_reg->value;
    memcpy(dest_reg->value, &res, 4); // direction addition
  } else if (destreg && !srcreg) {

    int offset1;
    bool deref1;
    char name1[10];
    parser(src_addr, &offset1, &deref1, name1);

    int offset2;
    bool deref2;
    char name2[10];
    parser(dest_addr, &offset2, &deref2, name2);

    Variable *ptr = get_var(name1, vartoaddr, &memory, var_ptr);
    if (!ptr) {
      fprintf(stderr, "Asm Error: Label/Value '%s' not found!\n", name1);
      exit(1);
    }
    unsigned char *offset_addr1 = ptr->address;
    unsigned char *offset_addr2 = dest_reg->value;
    unsigned char *final_dest_ptr = NULL;

    if (ptr->is_immediate == true) {

      float res = *(float *)dest_reg->value + *(float *)ptr->address;
      memcpy(dest_reg->value, &res, ptr->size);

    } else {

      if (deref1) {
        offset_addr1 = offset_addr1 + offset1;

      } else {
        offset_addr1 = ptr->address + offset1;
      }

      if (deref2) {
        offset_addr2 = offset_addr2 + offset2;
      } else {
        int reg_addr;
        memcpy(&reg_addr, dest_reg->value, ptr->size);
        int addr = (int)(reg_addr + offset2);
        unsigned char *real_host_pointer = memory.data + addr;
        offset_addr2 = real_host_pointer;
      }

      printf("%p %s %d \n", ptr->address, ptr->name, ptr->size);

      int res = *(int *)offset_addr1 + *(int *)offset_addr2;

      memcpy(offset_addr2, &res, ptr->size);
    }
  } else if (!destreg && srcreg) {
    int offset1;
    bool deref1;
    char name1[10];
    parser(src_addr, &offset1, &deref1, name1);

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
    unsigned char *offset_addr1 = src_reg->value;
    unsigned char *offset_addr2 = ptr->address;

    if (deref2) {
      offset_addr2 = offset_addr2 + offset2;
    } else {
      offset_addr2 = ptr->address + offset2;
    }

    printf("%p %s %d \n", ptr->address, ptr->name, ptr->size);

    float res = *(float *)offset_addr1 + *(float *)offset_addr2;

    memcpy(offset_addr2, &res, ptr->size);
  } else {
    fprintf(stderr,
            "Asm Error: Invalid memory-to-memory operation or bad syntax! "
            "(e.g., add [var1], [var2] is not supported by x86 hardware)\n");
    exit(1);
  }
}
