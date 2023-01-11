// memMUX.h

// includes
#include "systemc.h"

SC_MODULE(memMUX) {
    sc_in<bool> fwd;
    sc_in<int> rf_1_s, adder_data;
    sc_out<int> address;

    void sel_data() {
            if ( fwd ) {
                address = adder_data;
                //cout << "mem fwd address " << rf_1_s << endl;
            }
            else {
                address = rf_1_s;
                //cout << "address " << rf_1_s << endl;
            }

    }

    SC_CTOR(memMUX) {
        SC_METHOD(sel_data);
        sensitive << fwd << rf_1_s << adder_data;
    }
};