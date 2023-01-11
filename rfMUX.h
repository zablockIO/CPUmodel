// rfMUX.h

// includes
#include "systemc.h"

SC_MODULE(rfMUX) {
    sc_in<bool> beq, bneq, bgt, blt;
    sc_in<int> src2_reg, dst_reg;
    sc_out<int> mux_out;

    void sel_data() {
        while (1) {
            if (beq || bneq || bgt || blt) {
                mux_out = dst_reg;
            }
            else
                mux_out = src2_reg;
            wait();
        }
    }

    SC_CTOR(rfMUX) {
        SC_THREAD(sel_data);
        sensitive << beq << bneq << bgt << blt << src2_reg << dst_reg;
    }
};