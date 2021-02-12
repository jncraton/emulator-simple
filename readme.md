Instruction Processor
=====================

This project requires the implemenation of a very simple processor to execute instructions. The instruction format used is intended to be very simple (while not being space efficient).

Instruction Format
------------------

Instructions are all 4 bytes. Each byte represents the following:

- Byte 0: Operation to execute
- Byte 1: Source register
- Byte 2: Destination register
- Byte 3: Immediate Value (signed)

Specifically, instructions are defined as:

```c
typedef struct {
  Operation op;
  Register src;
  Register dst;
  signed char immediate;
} Instruction;
```

Operations
----------

This simple processor supports only 3 operations:

0. Halt - Stop the processor
1. LoadImmedate - Store the value in `immediate` to register `dst`.
2. Add - Add the value from register `src` to the value in register `dst` and store the result in `dst`.
