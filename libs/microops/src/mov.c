#include <compiler.h>
#include <globals.h>
#include <stdbool.h>
#include <string.h>

int mov(char *dest_addr, char *src_addr, int size) {
  // identify register to register or register to mem or mem to register
  bool destreg = false;
  Register *dest_reg;
  if (strcmp(dest_addr, "eax") == 0) {
    dest_reg = &eax;
    destreg = true;
  }
  if (strcmp(dest_addr, "ebx") == 0) {
    dest_reg = &ebx;
    destreg = true;
  }
  if (strcmp(dest_addr, "ecx") == 0) {
    dest_reg = &ecx;
    destreg = true;
  }
  if (strcmp(dest_addr, "edx") == 0) {
    dest_reg = &edx;
    destreg = true;
  }

  bool srcreg = false;
  Register *src_reg;
  if (strcmp(dest_addr, "eax") == 0) {
    src_reg = &eax;
    srcreg = true;
  }
  if (strcmp(dest_addr, "ebx") == 0) {
    src_reg = &ebx;
    srcreg = true;
  }
  if (strcmp(dest_addr, "ecx") == 0) {
    src_reg = &ecx;
    srcreg = true;
  }
  if (strcmp(dest_addr, "edx") == 0) {
    src_reg = &edx;
    srcreg = true;
  }

  if (srcreg && destreg) {
    memcpy(dest_reg->value, src_reg->value, 4);
  } else if (destreg && !srcreg) {
    Variable *ptr = get_var(src_addr, vartoaddr, &memory, var_ptr);
    memcpy(dest_reg, ptr->address, 4);
  } else if (!destreg && srcreg) {
    Variable *ptr = get_var(dest_addr, vartoaddr, &memory, var_ptr);
    memcpy(ptr->address, src_reg, 4);
  }
}