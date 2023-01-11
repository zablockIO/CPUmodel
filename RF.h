// RF.h

// includes
#include "systemc.h"

SC_MODULE(RF) {
    sc_in<bool> clk, WrX;
    sc_in<int> rAddr_1, rAddr_2, wrData, wrAddr;
    sc_out<int> rf_1, rf_2;
    
    sc_int<32> regData[16] = {0};

    void write_reg() {
        while (1) {
            if (WrX) {
                regData[wrAddr] = wrData;
                cout << "reg " << wrAddr << " written with value: " << wrData << endl;
                //cout << "wrAddr " << wrAddr << " data " << wrData << endl; 
            }
            wait();
        }
    }

    void read_reg() {
        while (1) {
            rf_1 = regData[rAddr_1];
            rf_2 = regData[rAddr_2];
            //cout << "rf_1 " << rf_1 << endl;
            //cout << "rf_2 " << rf_2 << endl;
            wait();
        }
    }

    SC_CTOR(RF) {
        SC_CTHREAD(write_reg, clk.pos());
        SC_THREAD(read_reg);
        sensitive << clk << rAddr_1 << rAddr_2;
    }
};