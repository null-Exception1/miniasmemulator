
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
/*
Memory segmentation

Data - 0 - 1024 bytes
Code - 1024 - 2048 bytes
Stack - 3072 - 4096 bytes

*/
void init_memory(unsigned char **mem, Variable **nametoaddr) {
  *mem = (unsigned char *)mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mem == NULL) {
    printf("Failed to alloc some memory");
  }
  *nametoaddr = (Variable *)malloc(VARIABLE_LIMIT * sizeof(Variable));
  if (*nametoaddr == NULL) {
    printf("Failed to alloc dereferencing memory");
  }
}