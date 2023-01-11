// BRANCHPC.h

// includes
#include "systemc.h"

SC_MODULE(BRANCHPC) {
    sc_in<bool> clk;
    sc_in<int> pc, offset;
    sc_out<int> adjusted_pc;

    void adjust_pc() {
        while (1) {
            adjusted_pc = (pc - 1) + offset;
            //cout << "pc: " << pc << endl;
            //cout << "offset: " << offset << endl;
            //cout << "adj pc: " << adjusted_pc << endl;
        wait();
        }
    }

    SC_CTOR(BRANCHPC) {
        SC_CTHREAD(adjust_pc, clk.pos());
    }
};