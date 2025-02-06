Emulator
========

This project implementats of a very simple processor to execute instructions.

Learning Objectives
-------------------

After completing this project, students will be able to:

- Simulate the fetch-execute cycle
- Describe simple operations such as `loadi` and `add`.

CPU Overview
------------

The CPU being emulated uses a custom 32-bit architecture. Instructions are all 32 bits in length. Data words in registers are also 32 bits in length.

The following registers are available:

- R0 - General data register
- R1 - General data register
- R2 - General data register
- R3 - General data register
- R4 - General data register
- IP - Instruction pointer (Points to the next instruction to execute)
- IR - Instruction register (holds the current instruction)

Instruction Format
------------------

Instructions are all 4 bytes. Each byte represents the following:

| Byte 0      | Byte 1    | Byte 2    | Byte 3    |
|-------------|-----------|-----------|-----------|
| op          | dst       | src       | immediate |

- op - Operation to execute
- dst - Destination register
- src - Source register
- immediate - Immediate Value (signed)

Specifically, instructions can be represented using the following `struct`:

```c
typedef struct {
  Operation op;
  Register dst;
  Register src;
  signed char immediate;
} Instruction;
```

Operations
----------

This simple processor supports the following operations:

1. Halt - Stop the processor
2. LoadImmedate - Store the value in `immediate` to register `dst`.
3. Add - Add the value from register `src` to the value in register `dst` and store the result in `dst`.
4. AddImmediate - Add the value in `immediate` to register `src` and store the result in register `dst`.

Note that these instruction still need to be implemented (in `tick`) along with the body of `instruction_fetch`.

Running
-------

The emulator can be compiled and tested by invoking:

```
make
```

Debugging Tips
--------------

A couple of tools are provided to make debugging easier.

1. `print_instruction` can be used to pretty print an instruction. For example:

```c
// Print the instruction stored in `inst`
print_instruction(inst);
```

2. `print_registers` can pretty print register values. For example:

```c
// Print the current register values stored in `registers`:
print_registers(registers);
```

3. `TEST_CLOCK` can be modified to adjust the clock speed of the CPU during testing. The emulator defaults to a 1 MHz CPU, but it may be helpful to run it much, much slower whole observing instruction and register values.

4. `printf` can be used to print any values of interest.
