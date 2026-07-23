# mini x86 emulator in c

more details on my blog (will release soon)

a lightweight, memory-sandboxed, turing-complete 32-bit CPU emulator built entirely from scratch in pure C.

the emulator simulates a physical hardware processor layout within a single host memory allocation blocks:

```text
+---------------------------------+---------------------------------+---------------------------------+

|      memory.data (0x0000)       |      memory.code (0x0400)       |      memory.stack (0x0C00)      |
|  Variables & Literal Constants  |    Instruction Struct Cache     |   Downward-Growing Stack Frame  |
+---------------------------------+---------------------------------+---------------------------------+
                                                                                      ^
                                                                                      | 
                                                                                  esp.value
```

### Core Component Specifications
- layout partitions separating data (`memory.data`), code (`memory.code`), and stack (`memory.stack`)
- features a centralized string-tokenization functional router (`operand_parse`) that utilizes file-private `static` pointer callbacks to decouple raw string processing from mathematical execution.
- standardized operations `add`, `sub`, `and`, `or`, `not`, and `xor` 
- implements an exact `Flags` register mapping state transitions for `zero_flag`, `sign_flag`, and `carry_flag` by utilizing native `uint32_t` type casting to catch unsigned underflows (borrows).
- implements conditional and unconditional indirect/direct branching (`jmp`, `je`, `jne`,`jl`,`jg`, `ja`, `jb`). 
---

### Sample test
```c
add_var("my_countdown", &memory, sizeof(Instruction), memory.code_ptr, &var_ptr, vartoaddr, INT);
add_ins("add", "eax", "10");
add_ins("sub", "ecx", "1");
add_ins("cmp", "ecx", "0");
add_ins("jne", "my_countdown", "");
add_ins("hlt", "", ""); // halt signature
```

### Core Termination Metrics
```text

=======================================================
   EMULATOR INITIALISED: BOOTING CONTROL UNIT            
=======================================================
Starting Counter (ECX): 3
Starting Value   (EAX): 0
Virtual EIP Base Offset: 1024
=======================================================

╔══ [CYCLE 1] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1024
║ DECODE -> Instruction : add eax, 10║ EXECUTE STATUS:
║   Registers -> EAX: 10    | ECX: 3    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 2] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1058
║ DECODE -> Instruction : sub ecx, 1║ EXECUTE STATUS:
║   Registers -> EAX: 10    | ECX: 2    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 3] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1092
║ DECODE -> Instruction : cmp ecx, 0║ EXECUTE STATUS:
║   Registers -> EAX: 10    | ECX: 2    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 4] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1126
║ DECODE -> Instruction : jne my_count,  ptr addr -> 1024 
║ EXECUTE STATUS:
║   Registers -> EAX: 10    | ECX: 2    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 5] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1024
║ DECODE -> Instruction : add eax, 10║ EXECUTE STATUS:
║   Registers -> EAX: 20    | ECX: 2    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 6] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1058
║ DECODE -> Instruction : sub ecx, 1║ EXECUTE STATUS:
║   Registers -> EAX: 20    | ECX: 1    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 7] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1092
║ DECODE -> Instruction : cmp ecx, 0║ EXECUTE STATUS:
║   Registers -> EAX: 20    | ECX: 1    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 8] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1126
║ DECODE -> Instruction : jne my_count,  ptr addr -> 1024 
║ EXECUTE STATUS:
║   Registers -> EAX: 20    | ECX: 1    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 9] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1024
║ DECODE -> Instruction : add eax, 10║ EXECUTE STATUS:
║   Registers -> EAX: 30    | ECX: 1    
║   EFLAGS    -> ZF:  0     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 10] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1058
║ DECODE -> Instruction : sub ecx, 1║ EXECUTE STATUS:
║   Registers -> EAX: 30    | ECX: 0    
║   EFLAGS    -> ZF:  1     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 11] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1092
║ DECODE -> Instruction : cmp ecx, 0║ EXECUTE STATUS:
║   Registers -> EAX: 30    | ECX: 0    
║   EFLAGS    -> ZF:  1     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 12] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1126
║ DECODE -> Instruction : jne my_count, ║ EXECUTE STATUS:
║   Registers -> EAX: 30    | ECX: 0    
║   EFLAGS    -> ZF:  1     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════

╔══ [CYCLE 13] ════════════════════════════════════════
║ FETCH  -> EIP Virtual Address: 1160
║ DECODE -> Instruction : hlt , ║ EXECUTE STATUS:
║   Registers -> EAX: 30    | ECX: 0    
║   EFLAGS    -> ZF:  1     | SF:  0     | CF:  0    
╚═══════════════════════════════════════════════════════
=======================================================
   🛑 CPU HALTED GRACEFULLY: EXECUTION TERMINATED 🛑   
=======================================================
Final Register Verification Summary:
  EAX (Accumulator Total): 30 (Expected: 30)
  ECX (Loop Counter state): 0 (Expected: 0)
=======================================================
```

---

