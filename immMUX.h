// immMUX.h

// includes
#include "systemc.h"

SC_MODULE(IMMMUX) {
    sc_in<int> rf_out_1, src2;
    sc_in<bool> imm;
    sc_out<int> B_in;

    void sel_val() {
            if (imm == 0) {
                B_in = rf_out_1;
            }
            else {
                B_in = src2;
            }
    }

    SC_CTOR(IMMMUX) {
        SC_METHOD(sel_val);
        sensitive << rf_out_1 << src2 << imm;
    }
};