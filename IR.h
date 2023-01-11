// IR.h

// includes
#include "systemc.h"

SC_MODULE(IR) {
    sc_in<int> imem_in0, imem_in1, imem_in2, imem_in3;
    sc_in<bool> clk, IRin, hazard, branch;
    sc_out<int> opcode, dest_reg, src_reg1, src_reg2;

    void split() {
        while (1) {
            if (IRin) {
                if (hazard || branch) {
                    src_reg2 = imem_in3;
                    src_reg1 = imem_in2;
                    dest_reg = imem_in1;
                    opcode = 12;
                    //cout << "IR hzd opcode: " << opcode << endl;
                }
                else {
                    src_reg2 = imem_in3;
                    src_reg1 = imem_in2;
                    dest_reg = imem_in1;
                    opcode = imem_in0;
                    //cout << "IR opcode: " << opcode << endl;
                }
            }
            wait();
        }
    }

    SC_CTOR(IR) {
        SC_CTHREAD(split, clk.pos());
    }
};