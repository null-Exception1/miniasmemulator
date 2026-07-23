#include <compiler.h>
#include <globals.h>
#include <memory.h>
#include <microops.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
  memory.code_ptr = memory.data_end;
  memory.code_end = memory.data_end + CODE_LEN;

  memory.stack = memory.code_end;
  memory.stack_ptr = memory.code_end;
  memory.stack_end = memory.code_end + STACK_LEN;

  int addr = (int)(memory.stack_end - memory.data);
  memcpy(esp.value, &addr, 4);

  addr = (int)(memory.code - memory.data);
  memcpy(eip.value, &addr, 4);

  int initial_ecx = 3;
  memcpy(ecx.value, &initial_ecx, 4);

  int initial_eax = 0;
  memcpy(eax.value, &initial_eax, 4);

  int const_1 = 1;
  add_var("1", &memory, 4, (unsigned char *)&const_1, &var_ptr, vartoaddr, INT);

  int const_10 = 10;
  add_var("10", &memory, 4, (unsigned char *)&const_10, &var_ptr, vartoaddr,
          INT);

  int const_0 = 0;
  add_var("0", &memory, 4, (unsigned char *)&const_0, &var_ptr, vartoaddr, INT);

  int const_addr = (int)(memory.code_ptr - memory.data);
  printf("%d", const_addr);
  add_var("my_count", &memory, sizeof(Instruction),
          (unsigned char *)&const_addr, &var_ptr, vartoaddr, INT);

  add_ins("add", "eax", "10");
  add_ins("sub", "ecx", "1");
  add_ins("cmp", "ecx", "0");
  add_ins("jne", "my_count", "");
  add_ins("hlt", "", "");

  printf("\n=======================================================\n");
  printf("   🚀 EMULATOR INITIALISED: BOOTING CONTROL UNIT 🚀   \n");
  printf("=======================================================\n");
  printf("Starting Counter (ECX): %d\n", *(int *)ecx.value);
  printf("Starting Value   (EAX): %d\n", *(int *)eax.value);
  printf("Virtual EIP Base Offset: %d\n", addr);
  printf("=======================================================\n\n");

  int curr_ins_address;
  memcpy(&curr_ins_address, eip.value, 4);
  unsigned char *actual_ptr;
  int cycle_count = 1;

  for (int i = 0; i < 20; i++) {
    actual_ptr = (unsigned char *)(curr_ins_address + memory.data);
    Instruction *ptr = (Instruction *)actual_ptr;

    printf("╔══ [CYCLE %d] ════════════════════════════════════════\n",
           cycle_count++);

    printf("║ FETCH  -> EIP Virtual Address: %d\n", curr_ins_address);
    printf("║ DECODE -> ");

    read_ins(ptr);

    printf("║ EXECUTE STATUS:\n");
    printf("║   Registers -> EAX: %-5d | ECX: %-5d\n", *(int *)eax.value,
           *(int *)ecx.value);
    printf("║   EFLAGS    -> ZF:  %-5d | SF:  %-5d | CF:  %-5d\n",
           flags.zero_flag, flags.sign_flag, flags.carry_flag);
    printf("╚═══════════════════════════════════════════════════════\n\n");

    if (strcmp("hlt", ptr->op) == 0) {
      printf("=======================================================\n");
      printf("   🛑 CPU HALTED GRACEFULLY: EXECUTION TERMINATED 🛑   \n");
      printf("=======================================================\n");
      printf("Final Register Verification Summary:\n");
      printf("  EAX (Accumulator Total): %d (Expected: 30)\n",
             *(int *)eax.value);
      printf("  ECX (Loop Counter state): %d (Expected: 0)\n",
             *(int *)ecx.value);
      printf("=======================================================\n");
      exit(0);
    }

    if (ptr->op[0] != 'j') {
      curr_ins_address += sizeof(Instruction);
      memcpy(eip.value, &curr_ins_address, 4);
    } else {
      memcpy(&curr_ins_address, eip.value, 4);
    }
  }
}
