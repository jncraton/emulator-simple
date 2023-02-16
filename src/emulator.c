#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "emulator.h"

#define TEST_CLOCK 1000000 // May be lowered for easier debugging

// Helper function to print register contents for debugging
void print_registers(int *registers) {
  printf("IP: %d ", registers[IP]);
  for (int i = 0; i < 5; i++) {
    printf("R%d: %d ", i, registers[i]);
  }
  printf("\n");
}

// Helper function to print instruction information for debugging
void print_instruction(Instruction inst) {
  printf("%s src=%d dst=%d imm=%d\n", instruction_names[inst.op], inst.src, inst.dst, inst.immediate);
}

void fetch_instruction(int32_t * memory, int *registers) {
  // TODO: Load instruction pointed to by IP into the IR register
}

Instruction decode_instruction(int32_t reg) {
  // Return the decoded form of the IR register
  return *(Instruction *) & reg;
}

int tick(int32_t * memory, int32_t * registers) {
  // Emulates one CPU clock tick
  //
  // Returns the number of instructions executed.
  // (Simple version always returns 1 unless halted)
  // 
  // 1. Load the next intruction into the `IR` register
  // 2. Decode the instruction for local use
  // 3. Execute the instruction
  // - Perform any needed ALU operations
  // - Perform any needed memory operations
  // - Write back register values as needed
  // 
  // The system `memory` and `registers` are provided
  // 
  // Both memory and registers may be accessed as arrays of 32-bit words. For
  // example: 
  // register[R0] // Access register 0
  // register[R3] = 12 // Store 12 to register 3
  // memory[7] // Access memory location 7
  // memory[3] = 4 // Store 4 to memory location 3
  // 
  // Operation names are provided in a global `enum` so they can be checked
  // easily
  // e.g: inst.op == LoadImmediate
  // 
  // Other definitions can be found in emulator.h

  fetch_instruction(memory, registers);
  Instruction inst = decode_instruction(registers[IR]);

  print_registers(registers);

  // TODO: Handle Halt, LoadImmediate, AddImmediate, and Add operations

  return 0;
}

/*
 * It is not recommended to modify any code below this point
 */

void update_display(int32_t * memory) {
  // 16x3 character mode display
  // Update output based on memory values
  char lines[3][17];
  char c;

  // Check the display mode
  if (memory[64] == 1) {
    memory[64] = 0;
    // Prebuffer text to minimize flicker
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 16; x++) {
        c = (char) memory[80 + y * 16 + x];
        if (c == 0) {
          c = ' ';
        }
        lines[y][x] = c;
      }
      lines[y][16] = 0;
    }
    printf("\033[2J"
           "\033[H"
           "##################\n" "#%s#\n" "#%s#\n" "#%s#\n" "##################\n\n", lines[0], lines[1], lines[2]);
  }
}

void emulate_system(int32_t * memory, int *registers, int clock_rate) {
  int clock_interval_us = 1000000 / clock_rate;

  // Loop until the next instruction is halt (0x00000000)
  while (tick(memory, registers)) {
    update_display(memory);
    usleep(clock_interval_us);
  }
}

void load_rom(char *filename, int32_t * memory) {
  FILE *rom = fopen(filename, "rb");
  if (!rom) {
    printf("Error loading %s\n", filename);
    exit(1);
  }
  fread(memory, 4, 256, rom);
  fclose(rom);
}

/* 
Test code 
*/

int _test_int_equal_result;

#define test_int_equal(exp, result) \
printf("Testing %s == %d\n", #exp, result); \
_test_int_equal_result = exp; \
if ((_test_int_equal_result) != result) { \
  printf("Test for %s == %d FAILED (got %d)\n", #exp, result, _test_int_equal_result); \
  exit(1); \
}

int main() {
  // Part 1 (Addition and LoadImmediate)

  int32_t registers[7] = { 0, 0, 0, 0, 0, 0 };
  printf("Instruction Fetch Tests\n");

  int32_t fetch_instructions[256] = {0,1,42};

  registers[IP] = 0;
  fetch_instruction(fetch_instructions, registers);
  test_int_equal(registers[IP], 0);
  test_int_equal(registers[IR], 0);
  registers[IP] = 1;
  fetch_instruction(fetch_instructions, registers);
  test_int_equal(registers[IP], 1);
  test_int_equal(registers[IR], 1);
  registers[IP] = 2;
  fetch_instruction(fetch_instructions, registers);
  test_int_equal(registers[IP], 2);
  test_int_equal(registers[IR], 42);

  printf("Halt Tests\n");
  Instruction halt_instructions[256] = {
    {Halt, 0, 0, 0}
  };
  memset(registers, 0, sizeof(registers));
  emulate_system((void *) halt_instructions, registers, TEST_CLOCK);
  test_int_equal(registers[IP], 0);
  test_int_equal(registers[R0], 0);
  test_int_equal(registers[R1], 0);
  test_int_equal(registers[R2], 0);

  printf("Load Immediate Tests\n");
  Instruction load_imm_instructions[256] = {
    {LoadImmediate, R0, 0, 1},
    {LoadImmediate, R1, 0, 80},
    {LoadImmediate, R2, 0, 13}
  };
  memset(registers, 0, sizeof(registers));
  emulate_system((void *) load_imm_instructions, registers, TEST_CLOCK);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 1);
  test_int_equal(registers[R1], 80);
  test_int_equal(registers[R2], 13);

  printf("Add Tests\n");
  Instruction add_instructions[256] = {
    {LoadImmediate, R0, 0, 42},
    {LoadImmediate, R1, 0, 100},
    {Add, R1, R0, 0}
  };
  memset(registers, 0, sizeof(registers));
  emulate_system((void *) add_instructions, registers, TEST_CLOCK);
  test_int_equal(registers[IP], 3);
  test_int_equal(registers[R0], 42);
  test_int_equal(registers[R1], 142);
  test_int_equal(registers[R2], 0);

  printf("Add Immediate Tests\n");
  Instruction addi_instructions[256] = {
    {AddImmediate, R0, R0, 1},
    {AddImmediate, R0, R0, 2},
    {AddImmediate, R1, R1, 21},
    {AddImmediate, R1, R1, 30},
    {AddImmediate, R2, R1, 1}
  };
  memset(registers, 0, sizeof(registers));
  emulate_system((void *) addi_instructions, registers, TEST_CLOCK);
  test_int_equal(registers[IP], 5);
  test_int_equal(registers[R0], 3);
  test_int_equal(registers[R1], 51);
  test_int_equal(registers[R2], 52);

  printf("All tests passed\n");
}
