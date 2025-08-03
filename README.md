# RISC-V Assembler & 5-Stage Pipeline Simulator

A C++ project that provides a simplified RISC-V toolchain by assembling assembly code into machine-readable binary and simulating its execution on a 5-stage pipelined processor.

---

## 📌 Overview

This project consists of two main components:

1.  **Assembler (`assembler.cpp`)** Parses a file of RISC-V assembly instructions (`Input.txt`) and converts each instruction into its corresponding 32-bit binary machine code, which is then written to `output.txt`.

2.  **Processor Simulator (`Processor.cpp`)** Emulates a 5-stage pipelined RISC-V processor that executes the binary instructions. It simulates the following pipeline stages and includes basic hazard detection:
    - **IF**: Instruction Fetch
    - **ID**: Instruction Decode & Register Fetch
    - **EX**: Execute
    - **MEM**: Memory Access
    - **WB**: Register Write Back

---

## 🧠 Supported Features

-   **Instruction Set**: Core **RISC-V RV32I** instructions, including:
    -   **R-Type**: `add`, `sub`, `sll`, `slt`, `sltu`, `xor`, `srl`, `sra`, `or`, `and`
    -   **I-Type**: `addi`, `slti`, `sltiu`, `xori`, `ori`, `andi`, `slli`, `srli`, `srai`
    -   **Load-Type**: `lb`, `lh`, `lw`, `lbu`, `lhu`
    -   **S-Type**: `sb`, `sh`, `sw`
    -   **B-Type**: `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`
    -   **U-Type**: `auipc`, `lui`
    -   **J-Type**: `jal`, `jalr`
-   **Pipelining**: A 5-stage pipeline with registers (`IF/ID`, `ID/EX`, `EX/MEM`, `MEM/WB`) to pass data between stages.
-   **Hazard Detection**: Basic data hazard detection that stalls the pipeline to ensure register read/write correctness.
-   **Simulation Output**: Reports final register and memory states, total cycle count, instructions executed, and Instructions Per Cycle (IPC).

---

## 🔧 Installation & Usage

### 🛠 Build

Ensure you have a C++17-compatible compiler (`g++` is recommended).

```bash
# Compile the assembler
g++ -std=c++17 assembler.cpp -o assembler

# Compile the simulator
g++ -std=c++17 Processor.cpp -o simulator
```

### 🚀 Run

The process is a two-step toolchain:

1.  **Assemble your code:**
    Create an `Input.txt` file with your assembly code. Then, run the assembler to generate the binary.
    ```bash
    ./assembler
    ```
    This reads `Input.txt` and creates `output.txt` containing the binary instructions.

2.  **Simulate binary execution:**
    The simulator is hardcoded to read the binary instructions from its internal `Instructions` vector. To use the output from the assembler, you must copy the contents of `output.txt` into this vector inside `simulator.cpp` and recompile.
    ```bash
    ./simulator
    ```

---

## 📂 Project Structure

```
.
├── assembler.cpp       # Converts assembly to binary
├── Processor.cpp       # Executes binary on a pipelined processor
├── Input.txt           # Sample RISC-V assembly file
├── Output.txt          # Generated binary from assembler
└── README.md           # You're reading this
```

---

## 💡 Example

**`Input.txt`**
```assembly
addi x1, x0, 5
addi x2, x0, 10
add x3, x1, x2
```

**Assembler output (`output.txt`):**
```
"00000000010100000000000010010011",
"00000000101000000000000100010011",
"00000000001000001000000110110011",
```

**Simulator output:**
```
Cycle Count = 8
Instructions Count = 3
IPC = 0.375
Registers Values:
x0 -> 0
x1 -> 5
x2 -> 10
x3 -> 15
... (other registers)

Memory Values:
... (memory contents)
```

---

## 🛠 Technologies Used

-   C++17
-   Standard Template Library (STL)
-   Object-Oriented Programming (OOP) for structuring pipeline stages, memory, and registers.

---

## 📚 Learning Outcomes

-   Deep understanding of RISC-V instruction encoding (R, I, S, B, U, J types).
-   Implementation of a two-pass assembler.
-   Simulation of a 5-stage processor pipeline with hazard detection.
-   Advanced C++ usage, including bitwise operations, file I/O, and OOP design.

---

## 🧑‍💻 Author

Made by **Ayush Agrawal**
