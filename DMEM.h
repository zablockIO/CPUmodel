// DMEM.h

// includes
#include "systemc.h"

SC_MODULE(DMEM) {
    sc_in<bool> clk, MemRd, MemWr;
    sc_in<int> address, dataIn;
    sc_out<int> dataOut;

    sc_int<32> data[256];

    void write_mem() {
        while (1) {
            if (MemWr) {
                data[address] = dataIn;
            }
            wait();
        }
    }

    void read_mem() {
        while (1) {
            if (MemRd) {
                dataOut = data[address];
                //cout << "mem address " << address << " data " << dataOut << endl;
            }
            wait();
        }
    }

    SC_CTOR(DMEM) {
        SC_CTHREAD(write_mem, clk.pos());
        SC_THREAD(read_mem);
        sensitive << MemRd << clk << address << dataIn;
        data[48] = 10;
        data[49] = 11;
        data[50] = 12;
    }
};