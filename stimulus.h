// stimulus.h

// includes
#include "systemc.h"

SC_MODULE(stimulus) {
    sc_out<bool> enable;
    sc_in<bool> clk;

    void send_stim() {
        while(1) {
            enable = 1;
            wait(10);
        }
    }

    SC_CTOR(stimulus) {
        SC_THREAD(send_stim);
        sensitive << clk;
    }
};