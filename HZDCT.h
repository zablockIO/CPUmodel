// HZDCT.h

// includes
#include "systemc.h"

SC_MODULE(HZDCT) {
    sc_in<bool> MemRd_s;
    sc_in<int> pc, src1_reg, src2_reg, dst_s;
    sc_out<int> new_pc;
    sc_out<bool> hazard;

    void hzd_detect() {
        while (1) {
            if ( MemRd_s && ((dst_s == src1_reg) || (dst_s == src2_reg)) ) {
                hazard = 1;
                new_pc = pc;
                cout << "hzd ctl pc: " << new_pc << endl;
            }
            else {
                hazard = 0;
            }
        wait();
        }
    }

    SC_CTOR(HZDCT) {
        SC_THREAD(hzd_detect);
        sensitive << MemRd_s << pc << src1_reg << src2_reg << dst_s;
    }
};