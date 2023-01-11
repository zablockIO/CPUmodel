// fwdMUX.h

// includes
#include "systemc.h"

SC_MODULE(fwdMUX) {
    sc_in<int> rf_out, adder_data, wbmux_data, fwd;
    sc_out<int> fwd_mux_out;

    void sel_data() {
            if (fwd == 1 )
                fwd_mux_out = adder_data;
            else if (fwd == 2 ) 
                fwd_mux_out = wbmux_data;
            else
                fwd_mux_out = rf_out;
    }

    SC_CTOR(fwdMUX) {
        SC_METHOD(sel_data);
        sensitive << fwd << rf_out << adder_data << wbmux_data;
    }
};