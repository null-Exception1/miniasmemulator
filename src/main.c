#include <compiler.h>
#include <globals.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
static Memory memory;
static int var_ptr = 0;
void show(unsigned char *addr, int len) {
  for (int i = 0; i < len; i++) {
    unsigned char byte;
    memcpy(&byte, addr + i, 1);
    printf("%0X", byte);
  }
  printf("\n \n");
}
int main() {
  unsigned char *global_start_addr;
  Variable *vartoaddr;

  init_memory(&global_start_addr, &vartoaddr);
  memory.data = global_start_addr;
  memory.data_ptr = global_start_addr;
  memory.data_end = global_start_addr + DATA_LEN;

  memory.code = memory.data;
  memory.code_ptr = global_start_addr;
  memory.code_end = global_start_addr + CODE_LEN;

  memory.stack = memory.code;
  memory.stack_ptr = global_start_addr;
  memory.stack_end = global_start_addr + STACK_LEN;

  show(memory.data, 100);

  // char name[10] = "myvar";
  // int value = 10;
  int value[4] = {1, 2, 3, 4};
  add_var("myvar", &memory, 4 * 4, (unsigned char *)value, &var_ptr, vartoaddr,
          INT);

  char value2[10] = "Teri mkc";
  add_var("myvar2", &memory, strlen(value2) + 1, (unsigned char *)&value2,
          &var_ptr, vartoaddr, CHAR);

  show(memory.data, 100);

  show((unsigned char *)vartoaddr, 100);
  printf("%p %s %d \n", vartoaddr[0].address, vartoaddr[0].name,
         vartoaddr[0].size);
  printf("%p %s %d \n", vartoaddr[1].address, vartoaddr[1].name,
         vartoaddr[1].size);

  Variable *ptr = get_var("myvar", vartoaddr, &memory, var_ptr);

  printf("get var %p %s %d\n", ptr->address, ptr->name, ptr->size);

  int getval[4];

  memcpy(getval, (int *)ptr->address, ptr->size);

  printf("%d %d %d %d\n", getval[0], getval[1], getval[2], getval[3]);

  return 0;
}