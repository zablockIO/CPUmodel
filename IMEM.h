// IMEM.h

// includes
#include "systemc.h"

SC_MODULE(IMEM) {
    sc_in<bool> clk, IRin;
    sc_in<int> address;
    sc_out<int> imem_out0, imem_out1, imem_out2, imem_out3;

    // fwd test
    /*sc_int<32> instructions[10][4] = {  {4, 0, 0, 0},    // zero register0 [val = 0]
                                        {4, 0, 0, 6},    // addi 6 to register0 [val = 6]
                                        {4, 0, 0, 6},    // addi 6 register0 [val = 12]
                                        {2, 0, 0, 0},    // add register0 to register0 [val = 24]
                                        {2, 0, 0, 0},    // add register0 to register0 [val = 48]
                                        {4, 1, 0, 1},    // addi 1 to register1 [val = 49]
                                        {4, 2, 0, 2},    // addi 2 to register2 [val = 50]
                                        {0, 5, 0, 0},    // load 0 to register5 [val = 10] 
                                        {7, 0, 0, 0} };  // halt 
*/

    // load use test
    sc_int<32> instructions[12][4] = {  {3, 0, 0, 0},    // zero register0 [val = 0]
                                        {4, 0, 0, 6},    // addi 6 to register0 [val = 6]
                                        {4, 0, 0, 6},    // addi 6 register0 [val = 12]
                                        {2, 0, 0, 0},    // add register0 to register0 [val = 24]
                                        {2, 0, 0, 0},    // add register0 to register0 [val = 48]
                                        {0, 6, 0, 0},    // load 0 to register6 [val = 10]
                                        {4, 6, 6, 1},    // addi 1 to register6 [val = 11]
                                        {4, 1, 0, 1},    // addi 1 registor0 store in register1 [val = 49]
                                        {0, 7, 1, 1},    // load 1 to register7 [val = 11]
                                        {4, 7, 7, 1},    // addi 1 to register7 [val = 12]
                                        {7, 0, 0, 0} };  // halt
    

    /* basic test
    sc_int<32> instructions[12][4] = {  {3, 0, 0, 0},    // zero register0 [val = 0]
                                        {3, 1, 1, 1},    // zero register1 [val = 0]
                                        {3, 2, 2, 2},    // zero register2 [val = 0]
                                        {4, 1, 1, 6},    // addi 6 to register1 [val = 6]
                                        {8, 0, 1, 3},    // branch if register1 val == 0
                                        {5, 1, 1, 1},    // subi 1 from register1
                                        {8, 0, 2, -3},   // branch if register2 == 0
                                        {7, 0, 0, 0} };  // halt
    */

    void send_instr() {
        if (IRin) {
            imem_out0 = instructions[address][0];
            imem_out1 = instructions[address][1];
            imem_out2 = instructions[address][2];
            imem_out3 = instructions[address][3];
            
            //cout << "imem opcode: " << imem_out0 << endl;
            //cout << "imem1 " << imem_out1 << endl;
            //cout << "imem2 " << imem_out2 << endl;
            //cout << "imem3 " << imem_out3 << endl;
        }
    }

    SC_CTOR(IMEM) {
        SC_METHOD(send_instr);
        sensitive << clk << IRin << address;
    }
};