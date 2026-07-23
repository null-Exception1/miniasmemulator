#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void pop_(char *data) {
  int address;
  memcpy(&address, esp.value, 4); // put esp.value into address

  int offset = 0;
  bool deref = false;
  char name[10];
  parser(data, &offset, &deref, name);

  bool reg_mention = false;
  Register *reg;
  if (get_register(name) != NULL) {
    reg = get_register(name);
    reg_mention = true;
  }

  // popping
  unsigned char *actual_ptr = (unsigned char *)(address + memory.data);
  if (reg_mention) {
    memcpy(reg->value, actual_ptr, 4);
  } else {
    if (deref) {
      Variable *ptr_to_var = get_var(name, vartoaddr, &memory, var_ptr);
      memcpy(ptr_to_var->address, actual_ptr, 4);
    }
  }

  // do +4 on it and replace with 0's
  memset(actual_ptr, 0, 4);
  address += 4;
  memcpy(esp.value, &address, 4); // put updated esp value back into it
}