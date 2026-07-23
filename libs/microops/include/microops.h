#ifndef MICROOPS
#define MICROOPS

// alu
void mov_(char *dest_addr, char *src_addr);
void add_(char *dest_addr, char *src_addr);
void sub_(char *dest_addr, char *src_addr);
void mul_(char *dest_addr, char *src_addr);
void div_(char *dest_addr, char *src_addr);

// lu
void and_(char *dest_addr, char *src_addr);
void not_(char *dest_addr);
void or_(char *dest_addr, char *src_addr);
void xor_(char *dest_addr, char *src_addr);

// cmp
void cmp_(char *dest_addr, char *src_addr);

// jmps
void jmp_(char *dest_addr);
void je_(char *target);
void jne_(char *target);
void jl_(char *target);
void jg_(char *target);
void jb_(char *target);
void ja_(char *target);

// stack
void pop_(char *data);
void push_(char *data);

#endif