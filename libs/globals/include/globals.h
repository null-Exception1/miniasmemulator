#ifndef GLOBALS
#define GLOBALS

#define DATA_LEN 1024
#define CODE_LEN 1024
#define STACK_LEN 1024
#define VARIABLE_LIMIT 100

#include <stdbool.h>

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

typedef enum {
  CHAR,
  INT,
  DOUBLE,
  LONG,
  LONG_LONG,
  FLOAT,
} Type;

typedef struct {
  char name[10];
  unsigned char *address;
  int size;
  Type var_type;
  bool is_immediate;
  int immediate_val;
} Variable;

typedef struct {
  Type var_type;
  int var_value_int;
  char var_value_char;
  double var_value_double;
  long var_value_long;
  long long var_value_long_long;
  bool found;
} ReturnVal;

typedef struct {
  unsigned char value[4];
} Register;

extern Register eax;
extern Register ebx;
extern Register ecx;
extern Register edx;
extern Register ebp;
extern Register eip;
extern Register esp;

typedef struct {
  int zero_flag;
  int carry_flag;
  int sign_flag;
  int overflow_flag;
} Flags;

extern Flags flags;
extern Memory memory;
extern int var_ptr;
extern Variable *vartoaddr;

extern int immediate_val;

typedef void (*write_reg)(unsigned char *, unsigned char *, int, int, bool,
                          bool, Variable *, Register *);
typedef void (*write_addr)(unsigned char *, unsigned char *, int, int, bool,
                           bool, Variable *);
typedef void (*write_reg_from_reg)(Register *dest_reg, Register *src_reg,
                                   int offset2, bool deref2);

#endif