#ifndef GLOBALS
#define GLOBALS

#define DATA_LEN 1024
#define CODE_LEN 1024
#define STACK_LEN 1024
#define VARIABLE_LIMIT 100
typedef struct {
  unsigned char *data;
  unsigned char *data_ptr;
  unsigned char *data_end;
  unsigned char *code;
  unsigned char *code_ptr;
  unsigned char *code_end;
  unsigned char *stack;
  unsigned char *stack_ptr;
  unsigned char *stack_end;
} Memory;

typedef struct {
  char name[10];
  int *address;
  int size;
} Variable;

#endif