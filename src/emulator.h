// Define registers
typedef enum { R0, R1, R2, R3, R4, IP, IR } __attribute__((__packed__)) Register;

// Define operations
typedef enum { 
  Halt = 0,
  LoadImmediate,
  Add,
  AddImmediate,
  And,
  Or,
  Xor,
  Jump,
  BranchOnEqual,
  LoadDirect,
  StoreDirect,
  LoadIndirect,
  StoreIndirect,
  Invalid
} __attribute__((__packed__)) Operation;

// Define plain-text instruction names for use in assembler
char *instruction_names[14] = { 
  "Halt",
  "LoadImmediate",
  "Add",
  "AddImmediate",
  "And",
  "Or",
  "Xor",
  "Jump",
  "BranchOnEqual",
  "LoadDirect",
  "StoreDirect",
  "LoadIndirect",
  "StoreIndirect"
};

// Define instruction format
// Note that on a the little-endian systems we're targetting, op with be the least significant byte
typedef struct {
  Operation op;
  Register dst;
  Register src;
  signed char immediate;
} Instruction;
