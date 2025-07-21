# 🔧 C Compiler for RISC-V

This project is a complete implementation of a **C-to-RISC-V compiler backend**, developed as Homework 3 for the course **Compiler Design (CS340400)** at National Chiao Tung University (NCTU). The compiler transforms a subset of the C language into RISC-V assembly code, following the course's custom specification and targeting both **Andes Corvette-F1 board** and **QEMU simulator**.

---

## ✅ Features

This compiler fully supports:

### 🎯 Compiler Architecture
- **Lex**: Tokenizes C source code
- **Yacc**: Parses syntax and generates RISC-V assembly
- **Symbol Table**: Tracks variable/function metadata
- **Stack Management**: Local variables & temporaries
- **Code Generation**: Outputs `.S` files ready for QEMU or F1 board

### 🔨 Code Generation Support
- **Function definition** and symbol scoping
- **Arithmetic expressions**: `+`, `-`, `*`, `/`, `()`
- **Pointer** operations (Level C)
- **Control flow**: `if`, `while`, `for`, `break`, `continue`
- **1D Array support**
- **Function invocation** (Level A)
  - Including special functions: `digitalWrite(pin, value)` and `delay(ms)`
- **RISC-V Calling Convention** implemented

---

## 🧠 Demo Levels (All Supported ✅)

| Level     | Feature                                | Supported |
|-----------|-----------------------------------------|-----------|
| E         | `codegen()` structure, `delay()`, `digitalWrite()` | ✅ |
| D         | Arithmetic Expressions                 | ✅ |
| C         | Single-level Pointer                   | ✅ |
| B         | Branching & 1D Arrays                  | ✅ |
| A         | Full Function Calling Convention       | ✅ |

---


---

## 🚀 How to Use

### 1. Build the compiler

```bash
make
./codegen < testcases/test.c > output.S
riscv32-unknown-elf-gcc main.c output.S -o a.out
qemu-riscv32 a.out
```

## Some special features
- Stack frame management for each function

- Caller-saved register saving & restoration

- Custom parser actions for inline codegen:
```
expr: expr '+' expr {
  fprintf(f_asm, "  lw t0, %d(sp)\n", $1->offset);
  fprintf(f_asm, "  lw t1, %d(sp)\n", $3->offset);
  fprintf(f_asm, "  add t0, t0, t1\n");
  fprintf(f_asm, "  sw t0, %d(sp)\n", offset);
};
```
- handle special instructions (jump)
```
li a0, 1000
jal ra, delay
```
