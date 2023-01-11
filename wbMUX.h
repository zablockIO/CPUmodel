// immMUX.h

// includes
#include "systemc.h"

SC_MODULE(wbMUX) {
    sc_in<int> mdrData, G_data;
    sc_in<bool> load;
    sc_out<int> wbOut;

    void sel_val() {
        while (1) {
            if (load) {
                wbOut = mdrData;
                cout << "Memory: " << wbOut << endl;
            }
            else {
                wbOut = G_data;
                //cout << "G_data: " << wbOut << endl;
            }
            wait();
        }
    }

    SC_CTOR(wbMUX) {
        SC_THREAD(sel_val);
        sensitive << load << mdrData << G_data;
    }
};