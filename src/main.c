#include <compiler.h>
#include <globals.h>
#include <memory.h>
#include <microops.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void show(unsigned char *addr, int len) {
  for (int i = 0; i < len; i++) {
    unsigned char byte;
    memcpy(&byte, addr + i, 1);
    printf("%0X", byte);
  }
  printf("\n \n");
}

Register eax;
Register ebx;
Register ecx;
Register edx;
Register ebp;
Register eip;
Register esp;

Memory memory;
int var_ptr = 0;
Variable *vartoaddr = NULL;

int immediate_val;
int main() {
  unsigned char *global_start_addr;
  var_ptr = 0;
  init_memory(&global_start_addr, &vartoaddr);

  memory.data = global_start_addr;
  memory.data_ptr = global_start_addr;
  memory.data_end = global_start_addr + DATA_LEN;

  memory.code = memory.data_end;
  memory.code_ptr = global_start_addr;
  memory.code_end = global_start_addr + CODE_LEN;

  memory.stack = memory.code_end;
  memory.stack_ptr = global_start_addr;
  memory.stack_end = global_start_addr + STACK_LEN;

  int addr = (int)(memory.stack_end - memory.data);
  memcpy(esp.value, &addr, 4);

  show(memory.data, 100);

  float value = 0.5f;
  add_var("myvalue", &memory, 4, (unsigned char *)&value, &var_ptr, vartoaddr,
          FLOAT);

  int value2 = 1;
  add_var("myvalue2", &memory, 4, (unsigned char *)&value2, &var_ptr, vartoaddr,
          INT);

  mov_("eax", "myvalue2");

  mov_("ebx", "[myvalue]");

  mov_("[eax]", "ebx");

  Variable *ptr = get_var("myvalue", vartoaddr, &memory, var_ptr);

  show(ptr->address, 10);

  printf("eax value : ");
  show(eax.value, 4);

  printf("ebx value : ");
  show(ebx.value, 4);

  show(memory.data, 100);

  return 0;
}