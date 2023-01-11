// STAGING.h

// includes
#include "systemc.h"

SC_MODULE(STG) {
    sc_in<bool> clk, hazard, branch;
    sc_in<bool> IRin, WrX_in, sub_in, MemRd_in, MemWr_in, spc_in;
    sc_in<int> op_in, dst_in, rf_1_in, rf_2_in;
    sc_out<bool> WrX_o, sub_o, MemRd_o, MemWr_o, spc_o;
    sc_out<int> op_o, dst_o, rf_1_o, rf_2_o;

    void stage() {
        while (1) {
            if (IRin) {
                if (hazard || branch) {
                    op_o = 12;
                    MemRd_o = 0;
                    WrX_o = 0;
                }
                else {
                    WrX_o = WrX_in;
                    sub_o = sub_in;
                    MemRd_o = MemRd_in;
                    MemWr_o = MemWr_in;
                    op_o = op_in;
                    spc_o = spc_in;
                    dst_o = dst_in;
                    rf_1_o = rf_1_in;
                    rf_2_o = rf_2_in;
                    //cout << "rf_1_o " << rf_1_o << endl;
                    //cout << "rf_2_o " << rf_2_o << endl;
                }   
            }
            else {
                WrX_o = 0;
                //MemRd_o = 0;
            }
            wait();
        }

    }

    SC_CTOR(STG) {
        SC_CTHREAD(stage, clk.pos());
    }
};