#include <compiler.h>
#include <globals.h>
#include <microops.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
void push_(char *data) {

  int address;
  memcpy(&address, esp.value, 4); // put esp.value into address
  // do -4 on it
  address -= 4;

  unsigned char *actual_ptr =
      (unsigned char *)(address + memory.data); // actual ptr
  memcpy(esp.value, &address, 4); // put updated esp value back into it

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

  // if register
  if (reg_mention) {
    memcpy(actual_ptr, reg->value, 4);
  } else {
    // if variable
    Variable *ptr = get_var(name, vartoaddr, &memory, var_ptr);
    if (deref) {
      // read from the variable with offset
      memcpy(actual_ptr, ptr->address + offset, 4);
    } else {
      // read the address of the variable put in memory
      int addr = (int)(ptr->address + offset - memory.data);
      memcpy(actual_ptr, &addr, 4);
    }
  }
}