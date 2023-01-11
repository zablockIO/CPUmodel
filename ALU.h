// ALU.h

// includes
#include "systemc.h"

SC_MODULE(ALU) {
    sc_in<int> A, B;
    sc_in<bool> add_sub;
    sc_out<int> C;

    void add() {
            if (add_sub == 0) {
                C = A + B;
                //cout << "op: add" << endl;
                //cout << "C = " << C << endl;
            }
            else {
                C = A - B;
                //cout << "op: sub" << endl;
                //cout << "C = " << C << endl;
            }
    }

    SC_CTOR(ALU) {
        SC_METHOD(add);
        sensitive << A << B << add_sub;
    }
};