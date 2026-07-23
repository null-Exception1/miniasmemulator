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
Flags flags;
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

  // 1. Clear out your register states cleanly
  *(int *)eax.value = 0;
  *(int *)ebx.value = 0;

  // 2. Initialize two trackable dummy variables in your virtual RAM
  int initial_val = 15;
  add_var("vA", &memory, 4, (unsigned char *)&initial_val, &var_ptr, vartoaddr,
          INT);

  int factor_val = 5;
  add_var("vB", &memory, 4, (unsigned char *)&factor_val, &var_ptr, vartoaddr,
          INT);

  printf("--- BOOTING EMULATOR EXECUTION ENGINE ---\n");

  // Test Case 1: Data Movement & Generic ALU Integration
  mov_("eax", "vA"); // eax should become 15
  add_("eax", "vB"); // eax = 15 + 5 = 20
  printf("[ALU TEST] Expected EAX: 20 | Actual Hex: ");
  show(eax.value, 4);

  // Test Case 2: The Downward Stack Pipeline
  push_("eax");     // Push 20 onto the stack frame
  mov_("eax", "0"); // Wipe out eax to prove the stack works
  pop_("ebx");      // Pop the top 4 bytes out into ebx
  printf("[STACK TEST] Expected EBX: 20 | Actual Hex: ");
  show(ebx.value, 4);

  // Test Case 3: Refactored Subtraction Logic Bounds
  sub_("ebx", "vB"); // ebx = 20 - 5 = 15
  printf("[SUB TEST] Expected EBX: 15 | Actual Hex: ");
  show(ebx.value, 4);

  return 0;
}