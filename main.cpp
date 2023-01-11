// tb

// includes
#include "PC.h"
#include "BRANCHPC.h"
#include "BRANCHCT.h"
#include "branchMUX.h"
#include "FWDCT.h"
#include "HZDCT.h"
#include "fwdMUX.h"
#include "IMEM.h"
#include "IR.h"
#include "HALT.h"
#include "DECODE.h"
#include "rfMUX.h"
#include "RF.h"
#include "STAGING.h"
#include "immMUX.h"
#include "BOOLREG.h"
#include "SIMREG.h"
#include "ALU.h"
#include "DMEM.h"
#include "memMUX.h"
#include "wbMUX.h"
#include "WBSTAGING.h"
#include "stimulus.h"

int sc_main(int argc, char *argv[]) {
    sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING );
    sc_set_time_resolution(1, SC_NS);
    sc_set_default_time_unit(1, SC_NS);
    sc_clock clock("clock", 20, SC_NS, 0.5, 15, SC_NS);


    // instruction fetch signals
    sc_signal<bool> branch, halt_s, IRenable, enable;
    sc_signal<bool> hzd;
    sc_signal<int> new_pc, npc, pc_out, pc_out_s, aluResult, rf_2;
    sc_signal<int> instr0, instr1, instr2, instr3;


    // module instantiations
    PC pc("PC");
    pc(clock, hzd, branch, new_pc, pc_out);

    // decode signals
    sc_signal<int> opcode, dst, dst_s, src1, src2;
    sc_signal<bool> WrX, MemWr, MemRd, MemRd_s2, sub, imm, bz, bnz, beq, bneq, bgt, blt, jmp, spc;

    BRANCHPC branchpc("BNCHPC");
    branchpc(clock, pc_out, src2, new_pc);

    HALT halt("HALT");
    halt(halt_s, IRenable);

    IMEM imem("IMEM");
    imem(clock, IRenable, pc_out, instr0, instr1, instr2, instr3);

    IR ir("IR");
    ir(instr0, instr1, instr2, instr3, clock, IRenable, hzd, branch, opcode, dst, src1, src2);

    SIMREG pcS1("PCS1");
    pcS1(pc_out, enable, clock, pc_out_s);

    DECODE decode("DECODE");
    decode(opcode, WrX, MemWr, MemRd, sub, imm, bz, bnz, beq, bneq, bgt, blt, jmp, spc, halt_s);

    // RF signals
    sc_signal<int> rf_1, rf_2_in, wbData, dst_s2, fwd_a, fwd_b, rf_1_branch, rf_2_branch;
    sc_signal<bool> WrX_s, WrX_s2, MemRd_s, fwd_mem;

    FWDCT fwdCt("FWD");
    fwdCt(WrX_s, WrX_s2, MemRd_s, imm, dst_s, src1, src2, dst_s2, fwd_a, fwd_b, fwd_mem);

    HZDCT hzdCt("HZD");
    hzdCt(MemRd_s, pc_out, src1, src2, dst_s, npc, hzd);

    BNCHCT bnchCt("BNCH");
    bnchCt(bz, bnz, beq, bneq, bgt, blt, jmp, rf_1_branch, rf_2_branch, branch);

    branchMUX bMux("BMUX");
    bMux(fwd_a, fwd_b, rf_1, rf_2, aluResult, wbData, rf_1_branch, rf_2_branch);

    rfMUX rfMux("RFMUX");
    rfMux(beq, bneq, bgt, blt, src2, dst, rf_2_in);

    RF rf("RF");
    rf(clock, WrX_s2, src1, rf_2_in, wbData, dst_s2, rf_1, rf_2);

    // ALU signals
    sc_signal<int> fwd_a_data, fwd_b_data, A_in, A_out, B_in, B_out, G_data, pc_out_s2;

    IMMMUX immMux("IMMMUX");
    immMux(rf_2, src2, imm, B_in);

    fwdMUX fwdMuxA("FWDMUXA");
    fwdMuxA(rf_1, aluResult, wbData, fwd_a, fwd_a_data);

    fwdMUX fwdMuxB("FWDMUXB");
    fwdMuxB(B_in, aluResult, wbData, fwd_b, fwd_b_data);

    SIMREG A("A_REG");
    A(fwd_a_data, enable, clock, A_out);

    SIMREG B("B_REG");
    B(fwd_b_data, enable, clock, B_out);

    // staging signals
    sc_signal<bool> sub_s, MemWr_s, spc_s, spc_s2;
    sc_signal<int> opcode_s, rf_1_s, rf_2_s;

    STG stg("STG");
    stg(clock, hzd, branch, enable, WrX, sub, MemRd, MemWr, spc, opcode, dst, rf_1, rf_2, WrX_s, sub_s, MemRd_s, MemWr_s, spc_s, opcode_s, dst_s, rf_1_s, rf_2_s);

    SIMREG pcS2("PCS2");
    pcS2(pc_out_s, enable, clock, pc_out_s2);

    ALU alu("ALU");
    alu(A_out, B_out, sub_s, aluResult);

    SIMREG G("G_REG");
    G(aluResult, enable, clock, G_data);

    // DMEM signals
    sc_signal<int> memMuxData, dmem_data, memData, pc_out_s3;

    memMUX memMux("MEMMUX");
    memMux(fwd_mem, rf_1_s, G_data, memMuxData);

    DMEM dmem("DMEM");
    dmem(clock, MemRd_s, MemWr_s, memMuxData, rf_1_s, dmem_data);

    BOOLREG spcSt("SPCST");
    spcSt(spc_s, enable, clock, spc_s2);

    BOOLREG memRdSt("MEMRDST");
    memRdSt(MemRd_s, enable, clock, MemRd_s2);

    SIMREG pcS3("PCS3");
    pcS3(pc_out_s2, enable, clock, pc_out_s3);

    SIMREG mdr("MDR");
    mdr(dmem_data, enable, clock, memData);

    WBSTG wbs("WBS");
    wbs(clock, enable, WrX_s, dst_s, WrX_s2, dst_s2);

    wbMUX wbm("WBMUX");
    wbm(memData, G_data, MemRd_s2, wbData);

    stimulus stim("STIM");
    stim(enable, clock);

    // trace file
    sc_trace_file *tf = sc_create_vcd_trace_file("wave");
    sc_trace(tf, clock, "clk");

    //control signals
    sc_trace(tf, imm, "imm");
    sc_trace(tf, hzd, "hzd");
    sc_trace(tf, branch, "branch");
    sc_trace(tf, bz, "bz");
    sc_trace(tf, fwd_mem, "fwd_mem");
    sc_trace(tf, sub, "sub");
    sc_trace(tf, dmem.data[48], "dmem[48]");
    sc_trace(tf, MemRd_s, "MemRd_s");
    sc_trace(tf, WrX_s2, "WrX_s2");
    sc_trace(tf, aluResult, "aluResult");
    sc_trace(tf, opcode, "opcode");
    sc_trace(tf, G.output, "G-data");
    sc_trace(tf, memMuxData, "address");
    sc_trace(tf, dst_s, "dest_s");
    sc_trace(tf, dst_s2, "dest_s2");
    sc_trace(tf, pc_out, "pc");
    sc_trace(tf, new_pc, "pc_new");
    sc_trace(tf, rf_1, "rf_1");
    sc_trace(tf, src2, "src2");
    sc_trace(tf, rf.regData[0], "register0");
    sc_trace(tf, rf.regData[1], "register1");
    sc_trace(tf, rf.regData[2], "register2");
    sc_trace(tf, rf.regData[3], "register3");
    sc_trace(tf, rf.regData[4], "register4");
    sc_trace(tf, rf.regData[5], "register5");
    sc_trace(tf, rf.regData[6], "register6");
    sc_trace(tf, rf.regData[7], "register7");
    sc_trace(tf, rf.regData[8], "register8");

    
    sc_start(1000, SC_NS);
    return(0);

}