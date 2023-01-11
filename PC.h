// PC.h

// includes
#include "systemc.h"

SC_MODULE(PC) {
    sc_in<bool> clk, hazard, branch;
    sc_in<int> new_pc;
    sc_out<int> pc_out;
    
    sc_int<32> counter = 0;

    void get_pc() {
        while (1) {
            if (hazard) {
                if (counter > 3) {
                    pc_out = counter - 2;
                    counter = counter - 1;
                }
                //cout << "PC npc: " << pc_out << endl;
            }
            else if (branch) {
                pc_out = new_pc;
                counter = new_pc + 1;
                //cout << "branch pc " << new_pc << endl;
            }
            else {
                pc_out = counter;
                counter = counter + 1;
            }
            //cout << "address: " << pc_out << endl;
            wait();
        }
    }

    SC_CTOR(PC) {
        SC_CTHREAD(get_pc, clk.pos());
    }
};