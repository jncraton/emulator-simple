#include <stdio.h>
#include <string.h>

// Define operations
typedef enum {Halt, LoadImmediate, Add}  __attribute__ ((__packed__)) Operation;

// Define registers
typedef enum {IP, R0, R1, R2}  __attribute__ ((__packed__)) Register;

// Define instruction format
typedef struct {
  Operation op;
  Register src;
  Register dst;
  signed char immediate;
} Instruction;

void print_registers(int * registers) {
  // Helper function to print register contents for debugging
  printf("IP: %d ", registers[IP]);
  for (int i = 0; i<3; i++) {
    printf("R%d: %d ", i, registers[i+1]);
  }
  printf("\n");
}

void print_instruction(Instruction inst) {
  // Helper function to print instruction information for debugging
  static char* instruction_names[3] = {"Halt", "LoadImmediate", "Add"};

  printf("%s src=%d dst=%d imm=%d\n", instruction_names[inst.op], inst.src, inst.dst, inst.immediate);
}

void execute(Instruction * instructions, int * registers) {
  /* Execute the supplied instructions and update registers appropriately

  This should support the following instructions:

  1. Halt
  2. LoadImmediate
  3. Add

  See readme.md for more information.

  Hints
  
  // Get an instruction
  Instuction inst = instructions[0];

  // Get register value
  int value = registers[R0];

  // Get instruction pointed to by register value
  Instruction inst = instructions[registers[R2]];

  // Get instruction properties
  inst.op;
  inst.src;
  inst.dst;
  inst.immediate;

  // Access src register value
  registers[inst.src];
  */
  
  /* Rough psuedocode
  while(1) {
    load instruction
    if op is halt then return
    if op is load then store imm in dst
    if op is add then store src+dst in dst
  }
  */
}

/* 
Test code 

It is not recommended to modify any code below this point
*/

#define test_int_equal(exp, result) \
printf("Test %s == %d ", #exp, result); \
if ((exp) != result) { \
  printf("FAILED as %d.\n", exp); \
} else { \
  printf("succeeded.\n"); \
}

#define test_float_equal(exp, result) \
printf("Test %s == %f ", #exp, result); \
if ((exp) != result) { \
  printf("FAILED as %f.\n", exp); \
} else { \
  printf("succeeded.\n"); \
}

int main() {
  printf("Halt Tests\n");
  Instruction halt_instructions[4]={
    {Halt, 0, 0, 0}
  };
  int registers[4] = {0,0,0,0};
  execute(halt_instructions, registers);
  test_int_equal(registers[IP], 0);
  test_int_equal(registers[R0], 0);
  test_int_equal(registers[R1], 0);
  test_int_equal(registers[R2], 0);

  printf("Load Immediate Tests\n");
  Instruction load_imm_instructions[4]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 80},
    {LoadImmediate, 0, R2, 13},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(load_imm_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 80);
  test_int_equal(registers[R2], 13);

  printf("Add Tests\n");
  Instruction add_instructions[4]={
    {LoadImmediate, 0, R0, 42},
    {LoadImmediate, 0, R1, 100},
    {Add, R0, R1, 0},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(add_instructions, registers);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 42);
  test_int_equal(registers[R1], 142);
  test_int_equal(registers[R2], 0);

  printf("Extended Tests\n");
  Instruction ext_instructions[11]={
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R1, 12},
    {LoadImmediate, 0, R2, 100},
    {Add, R0, R1, 0},
    {Add, R2, R1, 0},
    {Add, R2, R1, 0},
    {LoadImmediate, 0, R0, -12},
    {Add, R0, R1, 0},
    {LoadImmediate, 0, R0, 1},
    {LoadImmediate, 0, R2, 3},
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  execute(ext_instructions, registers);
  test_int_equal(registers[IP], 10);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 201);
  test_int_equal(registers[R2], 3);
}