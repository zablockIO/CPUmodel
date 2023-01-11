// SIMREG.h

// includes
#include "systemc.h"

SC_MODULE(SIMREG) {
    sc_in<int> input;
    sc_in<bool> enable, clk;
    sc_out<int> output;

    void reg() {
        while (1) {
            if (enable) {
                output = input;
            }
            wait();
        }
    }

    SC_CTOR(SIMREG) {
        SC_CTHREAD(reg, clk.pos());
    }
};