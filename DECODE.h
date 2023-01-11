// DECODE.h

// includes
#include "systemc.h"

SC_MODULE(DECODE) {
    sc_in<int> opcode;
    sc_out<bool> WrX, MemWr, MemRd, sub, imm, bz, bnz, beq, bneq, bgt, blt, jmp, spc, halt;

    void decode() {
        while (1) {
            if ( opcode == 0) {
                WrX = 1;
                MemWr = 0;
                MemRd = 1;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 1) {
                WrX = 0;
                MemWr = 1;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 2) {
                WrX = 1;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 3) {
                WrX = 1;
                MemWr = 0;
                MemRd = 0;
                sub = 1;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 4) {
                WrX = 1;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 1;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 5) {
                WrX = 1;
                MemWr = 0;
                MemRd = 0;
                sub = 1;
                imm = 1;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 6) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 1;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 7) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 1;
            }
            if ( opcode == 8) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 1;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 9) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 1;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 10) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 1;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 11) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 1;
                halt = 0;
            }
            if ( opcode == 12) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 13) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 1;
                bneq = 0;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 14) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 1;
                bgt = 0;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            if ( opcode == 15) {
                WrX = 0;
                MemWr = 0;
                MemRd = 0;
                sub = 0;
                imm = 0;
                bz = 0;
                bnz = 0;
                beq = 0;
                bneq = 0;
                bgt = 1;
                blt = 0;
                jmp = 0;
                spc = 0;
                halt = 0;
            }
            //cout << "DECODE opcode: " << opcode << endl;
            //cout << "DECODE memRd: " << MemRd << endl;
            wait();
        }    
    }

    SC_CTOR(DECODE) {
        SC_THREAD(decode);
        sensitive << opcode;
    }
};