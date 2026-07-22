#ifndef MICROOPS
#define MICROOPS

void mov_(char *dest_addr, char *src_addr);
void add_(char *dest_addr, char *src_addr);
void sub_(char *dest_addr, char *src_addr);
void mul_(char *dest_addr, char *src_addr);
void div_(char *dest_addr, char *src_addr);

void and_(char *dest_addr, char *src_addr);
void not_(char *dest_addr);
void or_(char *dest_addr, char *src_addr);
void xor_(char *dest_addr, char *src_addr);
#endif