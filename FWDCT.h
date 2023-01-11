// FWDCT.h

// includes
#include "systemc.h"

SC_MODULE(FWDCT) {
    sc_in<bool> WrX_s, WrX_s2, MemRd_s, imm;
    sc_in<int> dst_s, src1_reg, src2_reg, dst_s2;
    sc_out<int> forward_a, forward_b;
    sc_out<bool> forward_mem;

    void fwd_detect() {
        while (1) {
            forward_a = 0;
            forward_b = 0;
            forward_mem = 0;
            if ( WrX_s && (dst_s == src1_reg) ) forward_a = 1;
            if ( WrX_s && (dst_s == src2_reg) ) forward_b = 1;
            if ( WrX_s2 && (dst_s2 == src1_reg) && !(dst_s == src1_reg) ) forward_a = 2;
            if ( WrX_s2 && (dst_s2 == src2_reg) && !(dst_s == src2_reg) && !imm) forward_b = 2;
            if ( MemRd_s && (dst_s == src1_reg) ) forward_mem = 1;
            //cout << "fwd_a: " << forward_a << " fwd_b: " << forward_b << endl;
        wait();
        }
    }

    SC_CTOR(FWDCT) {
        SC_THREAD(fwd_detect);
        sensitive << WrX_s << WrX_s2 << MemRd_s << imm << dst_s << src1_reg << src2_reg << dst_s2;
    }
};