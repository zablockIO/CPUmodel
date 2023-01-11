// HALT.h

// includes
#include "systemc.h"

SC_MODULE(HALT) {
    sc_in<bool> halt;
    sc_out<bool> IRenable;
    
    void stall() {
            if (halt) {
                IRenable = 0;
                cout << "HALT" << endl;
            } 
            else {
                IRenable = 1;
            }
    }

    SC_CTOR(HALT) {
        SC_METHOD(stall)
        sensitive << halt;
    }

};