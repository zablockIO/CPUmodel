// WBSTAGING.h

// includes
#include "systemc.h"

SC_MODULE(WBSTG) {
    sc_in<bool> clk, IRin, WrX_in;
    sc_in<int> dst_in;
    sc_out<bool> WrX_o;
    sc_out<int> dst_o;

    void wbstage() {
        while (1) {
            if (IRin){ 
                WrX_o = WrX_in;
                dst_o = dst_in;
            }
            //else {
            //    WrX_o = 0;
            //}
        wait();
        }
    }

    SC_CTOR(WBSTG) {
        SC_CTHREAD(wbstage, clk.pos());
    }
};