# **SystemC MIPS-like CPU**

Basic 4-stage MIPS-like processor model written in C++ using SystemC library. Processor is pipelined and handles both forwarding and load-use hazards. Branching and jumping instructions currently not fully supported. 

```main.cpp``` contains the SystemC test bench with main program, wiring, and ```#include``` statements for each component. It also contains code for waveform generation. Waveforms are of ```.vcd``` file type and can be opened with any waveform viewer supporting the file type (ex: GTKWave).  

Processor stages:  
1. Instruction Fetch and Decode
2. Execution
3. Memory Access
4. Writeback

Instruction set:  
| Opcode | Instruction | Description                 | Implemented |
| ------ | ----------- | --------------------------- | ----------- |
| 0      | load        | load from data memory       | Yes         |
| 1      | store       | store to data memory        | Yes         |
| 2      | add         | add two register values     | Yes         |
| 3      | sub         | sub two register values     | Yes         |
| 4      | addi        | add immediate               | Yes         |
| 5      | subi        | sub immediate               | Yes         |
| 6      | blt         | branch if less than         | No          |
| 7      | halt        | halt processing             | Yes         |
| 8      | bz          | branch if equal to zero     | No          |
| 9      | bnz         | branch if not equal to zero | No          |
| a      | jmp         | jump                        | No          |
| b      | spc         | save processor count        | Yes         |
| c      | nop         | nop                         | Yes         |
| d      | beq         | branch if equal             | No          |
| e      | bneq        | branch if not equal         | No          |
| f      | bgt         | branch if greater than      | No          |

## Basic Pipeline
![image](.assets/cpuPipeline.PNG)

## Todo
- Branch and jump instructions
- Improved instruction memory (IMEM)
- Clean up dev code that is no longer required