#include <globals.h>
#include <string.h>

Register *get_register(const char *reg_name) {
  if (strncmp(reg_name, "eax", 3) == 0)
    return &eax;
  if (strncmp(reg_name, "ebx", 3) == 0)
    return &ebx;
  if (strncmp(reg_name, "ecx", 3) == 0)
    return &ecx;
  if (strncmp(reg_name, "edx", 3) == 0)
    return &edx;
  if (strncmp(reg_name, "ebp", 3) == 0)
    return &ebp;
  if (strncmp(reg_name, "esp", 3) == 0)
    return &esp;
  if (strncmp(reg_name, "eip", 3) == 0)
    return &eip;
  return NULL; // Not a register (must be an emulated variable name!)
}