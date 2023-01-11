// BOOLREG.h

// includes
#include "systemc.h"

SC_MODULE(BOOLREG) {
    sc_in<bool> input, enable, clk;
    sc_out<bool> output;

    void reg() {
        while (1) {
            if (enable) {
                output = input;
            }
            wait();
        }
    }

    SC_CTOR(BOOLREG) {
        SC_CTHREAD(reg, clk.pos());
    }
};