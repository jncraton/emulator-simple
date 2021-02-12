Simple Processor
================

This project requires the implementation of a very simple processor to execute instructions. The instruction format used is intended to be very simple (while not being space efficient).

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

1. Halt - Stop the processor
2. LoadImmedate - Store the value in `immediate` to register `dst`.
3. Add - Add the value from register `src` to the value in register `dst` and store the result in `dst`.

It has no ability to alter the flow of program execution and no access to external memory or I/O.

Running
-------

Once the `execute` function has been implemented, the processor can be compiled and tested by invoking:

```
make
```
