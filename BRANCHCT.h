// BRANCHCT.h

// includes
#include "systemc.h"

SC_MODULE(BNCHCT) {
    sc_in<bool> bz, bnz, beq, bneq, bgt, blt, jmp;
    sc_in<int> src1_reg, src2_reg;
    sc_out<bool> load_new_pc;

    void bnch_detect() {
        while (1) {
            if ( bz && (src1_reg == 0) ) load_new_pc = 1;
            else if ( bnz && (src1_reg != 0) ) load_new_pc = 1;
            else if ( beq && (src1_reg == src2_reg) ) load_new_pc = 1;
            else if ( bneq && (src1_reg != src2_reg) ) load_new_pc = 1;
            else if ( bgt && (src1_reg > src2_reg) ) load_new_pc = 1;
            else if ( blt && (src1_reg < src2_reg) ) load_new_pc = 1;
            else load_new_pc = 0;
        wait();
        }
    }

    SC_CTOR(BNCHCT) {
        SC_THREAD(bnch_detect);
        sensitive << bz << bnz << beq << bneq << bgt << blt << jmp << src1_reg << src2_reg;
    }
};