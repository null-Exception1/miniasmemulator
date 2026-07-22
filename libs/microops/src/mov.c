#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int immediate_val;

void mov_(char *dest_addr, char *src_addr) {

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

  if (srcreg && destreg) {
    memcpy(dest_reg->value, src_reg->value, 4);
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

    // printf("%p %s %d \n", ptr->address, ptr->name, ptr->size);
    // printf("%d \n", ptr->is_immediate);
    // printf("%d %d \n", deref1, deref2);
    if (ptr->is_immediate == true) {
      // printf("immediate_val %d", immediate_val);
      memcpy(dest_reg->value, &immediate_val, 4);
    } else {

      if (deref1) {
        offset_addr1 = offset_addr1 + offset1;

      } else {
        offset_addr1 = ptr->address + offset1;
      }
      if (deref2 && deref1) {
        fprintf(stderr, "Asm Error: mem to mem not allowed! %s %s \n", name1,
                name2);
        exit(1);
      }
      // printf("%p %p %d \n", offset_addr1, dest_reg->value, ptr->size);
      memcpy(offset_addr2, offset_addr1, ptr->size);
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
    memcpy(offset_addr2, offset_addr1, ptr->size);
  } else {
    fprintf(stderr,
            "Asm Error: Invalid memory-to-memory operation or bad syntax! "
            "(e.g., mov [var1], [var2] is not supported by x86 hardware)\n");
    exit(1);
  }
}