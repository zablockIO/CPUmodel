// branchMUX.h

// includes
#include "systemc.h"

SC_MODULE(branchMUX) {
    sc_in<int> forward_a, forward_b, rf_1, rf_2, adder_data, wbmux_data;
    sc_out<int> mux_out_a, mux_out_b;

    void sel_data() {
            if (forward_a == 1) {
                mux_out_a = adder_data;
            }
            if (forward_a == 2) {
                mux_out_a = wbmux_data;
            }
            if (forward_a == 0) {
                mux_out_a = rf_1;
            }
            if (forward_b == 1) {
                mux_out_b = adder_data;
            }
            if (forward_b == 2) {
                mux_out_b = wbmux_data;
            }
            if (forward_b == 0) {
                mux_out_b = rf_2;
            }
    }

    SC_CTOR(branchMUX) {
        SC_METHOD(sel_data);
        sensitive << forward_a << forward_b;
    }
};