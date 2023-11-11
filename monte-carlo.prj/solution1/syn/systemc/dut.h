// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _dut_HH_
#define _dut_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "monte_carlo_both_pri.h"

namespace ap_rtl {

struct dut : public sc_module {
    // Port declarations 9
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_lv<32> > strm_out_V_V_din;
    sc_in< sc_logic > strm_out_V_V_full_n;
    sc_out< sc_logic > strm_out_V_V_write;


    // Module declarations
    dut(sc_module_name name);
    SC_HAS_PROCESS(dut);

    ~dut();

    sc_trace_file* mVcdFile;

    ofstream mHdltvinHandle;
    ofstream mHdltvoutHandle;
    monte_carlo_both_pri* grp_monte_carlo_both_pri_fu_87;
    sc_signal< sc_lv<8> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_logic > strm_out_V_V_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_logic > ap_CS_fsm_state5;
    sc_signal< sc_logic > ap_CS_fsm_state6;
    sc_signal< sc_logic > ap_CS_fsm_state7;
    sc_signal< sc_logic > ap_CS_fsm_state8;
    sc_signal< sc_lv<64> > result_call_reg_552;
    sc_signal< sc_logic > grp_monte_carlo_both_pri_fu_87_ap_ready;
    sc_signal< sc_logic > grp_monte_carlo_both_pri_fu_87_ap_done;
    sc_signal< sc_lv<64> > result_put_reg_557;
    sc_signal< sc_lv<1> > p_Result_s_reg_562;
    sc_signal< sc_lv<32> > trunc_ln331_fu_134_p1;
    sc_signal< sc_lv<32> > trunc_ln331_reg_567;
    sc_signal< sc_lv<1> > icmp_ln326_fu_146_p2;
    sc_signal< sc_lv<1> > icmp_ln326_reg_573;
    sc_signal< sc_lv<12> > sh_amt_fu_152_p2;
    sc_signal< sc_lv<12> > sh_amt_reg_579;
    sc_signal< sc_lv<1> > icmp_ln330_fu_162_p2;
    sc_signal< sc_lv<1> > icmp_ln330_reg_584;
    sc_signal< sc_lv<1> > icmp_ln332_fu_168_p2;
    sc_signal< sc_lv<1> > icmp_ln332_reg_589;
    sc_signal< sc_lv<1> > or_ln330_fu_210_p2;
    sc_signal< sc_lv<1> > or_ln330_reg_594;
    sc_signal< sc_lv<32> > select_ln333_fu_234_p3;
    sc_signal< sc_lv<32> > select_ln333_reg_599;
    sc_signal< sc_lv<1> > p_Result_1_reg_604;
    sc_signal< sc_lv<32> > trunc_ln331_1_fu_275_p1;
    sc_signal< sc_lv<32> > trunc_ln331_1_reg_609;
    sc_signal< sc_lv<1> > icmp_ln326_1_fu_287_p2;
    sc_signal< sc_lv<1> > icmp_ln326_1_reg_615;
    sc_signal< sc_lv<12> > sh_amt_2_fu_293_p2;
    sc_signal< sc_lv<12> > sh_amt_2_reg_621;
    sc_signal< sc_lv<1> > icmp_ln330_1_fu_303_p2;
    sc_signal< sc_lv<1> > icmp_ln330_1_reg_626;
    sc_signal< sc_lv<1> > icmp_ln332_1_fu_309_p2;
    sc_signal< sc_lv<1> > icmp_ln332_1_reg_631;
    sc_signal< sc_lv<1> > or_ln330_1_fu_351_p2;
    sc_signal< sc_lv<1> > or_ln330_1_reg_636;
    sc_signal< sc_lv<32> > select_ln333_1_fu_375_p3;
    sc_signal< sc_lv<32> > select_ln333_1_reg_641;
    sc_signal< sc_lv<32> > select_ln332_fu_448_p3;
    sc_signal< sc_lv<32> > select_ln332_reg_646;
    sc_signal< sc_lv<32> > select_ln332_1_fu_521_p3;
    sc_signal< sc_lv<32> > select_ln332_1_reg_652;
    sc_signal< sc_lv<32> > tmp_V_1_fu_546_p3;
    sc_signal< sc_lv<32> > tmp_V_1_reg_658;
    sc_signal< sc_logic > grp_monte_carlo_both_pri_fu_87_ap_start;
    sc_signal< sc_logic > grp_monte_carlo_both_pri_fu_87_ap_idle;
    sc_signal< sc_lv<64> > grp_monte_carlo_both_pri_fu_87_ap_return_0;
    sc_signal< sc_lv<64> > grp_monte_carlo_both_pri_fu_87_ap_return_1;
    sc_signal< sc_logic > grp_monte_carlo_both_pri_fu_87_ap_start_reg;
    sc_signal< bool > ap_block_state1;
    sc_signal< sc_lv<32> > tmp_V_fu_534_p3;
    sc_signal< sc_lv<64> > reg_V_fu_101_p1;
    sc_signal< sc_lv<11> > p_Result_s_9_fu_116_p4;
    sc_signal< sc_lv<52> > trunc_ln318_fu_130_p1;
    sc_signal< sc_lv<63> > trunc_ln310_fu_104_p1;
    sc_signal< sc_lv<12> > exp_V_fu_126_p1;
    sc_signal< sc_lv<32> > sext_ln329_fu_158_p1;
    sc_signal< sc_lv<53> > tmp_fu_138_p3;
    sc_signal< sc_lv<53> > zext_ln334_fu_180_p1;
    sc_signal< sc_lv<53> > lshr_ln334_fu_184_p2;
    sc_signal< sc_lv<1> > tmp_4_fu_194_p3;
    sc_signal< sc_lv<1> > icmp_ln333_fu_174_p2;
    sc_signal< sc_lv<1> > xor_ln330_fu_216_p2;
    sc_signal< sc_lv<1> > and_ln333_fu_222_p2;
    sc_signal< sc_lv<1> > and_ln333_1_fu_228_p2;
    sc_signal< sc_lv<32> > trunc_ln334_fu_190_p1;
    sc_signal< sc_lv<32> > select_ln336_fu_202_p3;
    sc_signal< sc_lv<64> > reg_V_1_fu_242_p1;
    sc_signal< sc_lv<11> > p_Result_2_fu_257_p4;
    sc_signal< sc_lv<52> > trunc_ln318_1_fu_271_p1;
    sc_signal< sc_lv<63> > trunc_ln310_1_fu_245_p1;
    sc_signal< sc_lv<12> > exp_V_1_fu_267_p1;
    sc_signal< sc_lv<32> > sext_ln329_1_fu_299_p1;
    sc_signal< sc_lv<53> > tmp_1_fu_279_p3;
    sc_signal< sc_lv<53> > zext_ln334_1_fu_321_p1;
    sc_signal< sc_lv<53> > lshr_ln334_1_fu_325_p2;
    sc_signal< sc_lv<1> > tmp_7_fu_335_p3;
    sc_signal< sc_lv<1> > icmp_ln333_1_fu_315_p2;
    sc_signal< sc_lv<1> > xor_ln330_1_fu_357_p2;
    sc_signal< sc_lv<1> > and_ln333_2_fu_363_p2;
    sc_signal< sc_lv<1> > and_ln333_3_fu_369_p2;
    sc_signal< sc_lv<32> > trunc_ln334_1_fu_331_p1;
    sc_signal< sc_lv<32> > select_ln336_1_fu_343_p3;
    sc_signal< sc_lv<12> > sh_amt_1_fu_383_p2;
    sc_signal< sc_lv<7> > tmp_3_fu_392_p4;
    sc_signal< sc_lv<32> > sext_ln342_fu_388_p1;
    sc_signal< sc_lv<1> > icmp_ln343_fu_402_p2;
    sc_signal< sc_lv<32> > shl_ln345_fu_408_p2;
    sc_signal< sc_lv<1> > xor_ln326_fu_427_p2;
    sc_signal< sc_lv<1> > and_ln330_fu_432_p2;
    sc_signal< sc_lv<32> > select_ln326_fu_421_p3;
    sc_signal< sc_lv<1> > or_ln332_fu_444_p2;
    sc_signal< sc_lv<32> > select_ln330_fu_437_p3;
    sc_signal< sc_lv<32> > select_ln343_fu_413_p3;
    sc_signal< sc_lv<12> > sh_amt_3_fu_456_p2;
    sc_signal< sc_lv<7> > tmp_6_fu_465_p4;
    sc_signal< sc_lv<32> > sext_ln342_1_fu_461_p1;
    sc_signal< sc_lv<1> > icmp_ln343_1_fu_475_p2;
    sc_signal< sc_lv<32> > shl_ln345_1_fu_481_p2;
    sc_signal< sc_lv<1> > xor_ln326_1_fu_500_p2;
    sc_signal< sc_lv<1> > and_ln330_1_fu_505_p2;
    sc_signal< sc_lv<32> > select_ln326_1_fu_494_p3;
    sc_signal< sc_lv<1> > or_ln332_1_fu_517_p2;
    sc_signal< sc_lv<32> > select_ln330_1_fu_510_p3;
    sc_signal< sc_lv<32> > select_ln343_1_fu_486_p3;
    sc_signal< sc_lv<32> > sub_ln461_fu_529_p2;
    sc_signal< sc_lv<32> > sub_ln461_1_fu_541_p2;
    sc_signal< sc_lv<8> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<8> ap_ST_fsm_state1;
    static const sc_lv<8> ap_ST_fsm_state2;
    static const sc_lv<8> ap_ST_fsm_state3;
    static const sc_lv<8> ap_ST_fsm_state4;
    static const sc_lv<8> ap_ST_fsm_state5;
    static const sc_lv<8> ap_ST_fsm_state6;
    static const sc_lv<8> ap_ST_fsm_state7;
    static const sc_lv<8> ap_ST_fsm_state8;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<32> ap_const_lv32_4;
    static const sc_lv<32> ap_const_lv32_5;
    static const sc_lv<32> ap_const_lv32_6;
    static const sc_lv<32> ap_const_lv32_7;
    static const sc_lv<32> ap_const_lv32_989680;
    static const sc_lv<32> ap_const_lv32_64;
    static const sc_lv<32> ap_const_lv32_3F;
    static const sc_lv<32> ap_const_lv32_34;
    static const sc_lv<32> ap_const_lv32_3E;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<63> ap_const_lv63_0;
    static const sc_lv<12> ap_const_lv12_433;
    static const sc_lv<11> ap_const_lv11_433;
    static const sc_lv<12> ap_const_lv12_0;
    static const sc_lv<12> ap_const_lv12_36;
    static const sc_lv<32> ap_const_lv32_FFFFFFFF;
    static const sc_lv<32> ap_const_lv32_B;
    static const sc_lv<7> ap_const_lv7_1;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_and_ln330_1_fu_505_p2();
    void thread_and_ln330_fu_432_p2();
    void thread_and_ln333_1_fu_228_p2();
    void thread_and_ln333_2_fu_363_p2();
    void thread_and_ln333_3_fu_369_p2();
    void thread_and_ln333_fu_222_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_CS_fsm_state5();
    void thread_ap_CS_fsm_state6();
    void thread_ap_CS_fsm_state7();
    void thread_ap_CS_fsm_state8();
    void thread_ap_block_state1();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_exp_V_1_fu_267_p1();
    void thread_exp_V_fu_126_p1();
    void thread_grp_monte_carlo_both_pri_fu_87_ap_start();
    void thread_icmp_ln326_1_fu_287_p2();
    void thread_icmp_ln326_fu_146_p2();
    void thread_icmp_ln330_1_fu_303_p2();
    void thread_icmp_ln330_fu_162_p2();
    void thread_icmp_ln332_1_fu_309_p2();
    void thread_icmp_ln332_fu_168_p2();
    void thread_icmp_ln333_1_fu_315_p2();
    void thread_icmp_ln333_fu_174_p2();
    void thread_icmp_ln343_1_fu_475_p2();
    void thread_icmp_ln343_fu_402_p2();
    void thread_lshr_ln334_1_fu_325_p2();
    void thread_lshr_ln334_fu_184_p2();
    void thread_or_ln330_1_fu_351_p2();
    void thread_or_ln330_fu_210_p2();
    void thread_or_ln332_1_fu_517_p2();
    void thread_or_ln332_fu_444_p2();
    void thread_p_Result_2_fu_257_p4();
    void thread_p_Result_s_9_fu_116_p4();
    void thread_reg_V_1_fu_242_p1();
    void thread_reg_V_fu_101_p1();
    void thread_select_ln326_1_fu_494_p3();
    void thread_select_ln326_fu_421_p3();
    void thread_select_ln330_1_fu_510_p3();
    void thread_select_ln330_fu_437_p3();
    void thread_select_ln332_1_fu_521_p3();
    void thread_select_ln332_fu_448_p3();
    void thread_select_ln333_1_fu_375_p3();
    void thread_select_ln333_fu_234_p3();
    void thread_select_ln336_1_fu_343_p3();
    void thread_select_ln336_fu_202_p3();
    void thread_select_ln343_1_fu_486_p3();
    void thread_select_ln343_fu_413_p3();
    void thread_sext_ln329_1_fu_299_p1();
    void thread_sext_ln329_fu_158_p1();
    void thread_sext_ln342_1_fu_461_p1();
    void thread_sext_ln342_fu_388_p1();
    void thread_sh_amt_1_fu_383_p2();
    void thread_sh_amt_2_fu_293_p2();
    void thread_sh_amt_3_fu_456_p2();
    void thread_sh_amt_fu_152_p2();
    void thread_shl_ln345_1_fu_481_p2();
    void thread_shl_ln345_fu_408_p2();
    void thread_strm_out_V_V_blk_n();
    void thread_strm_out_V_V_din();
    void thread_strm_out_V_V_write();
    void thread_sub_ln461_1_fu_541_p2();
    void thread_sub_ln461_fu_529_p2();
    void thread_tmp_1_fu_279_p3();
    void thread_tmp_3_fu_392_p4();
    void thread_tmp_4_fu_194_p3();
    void thread_tmp_6_fu_465_p4();
    void thread_tmp_7_fu_335_p3();
    void thread_tmp_V_1_fu_546_p3();
    void thread_tmp_V_fu_534_p3();
    void thread_tmp_fu_138_p3();
    void thread_trunc_ln310_1_fu_245_p1();
    void thread_trunc_ln310_fu_104_p1();
    void thread_trunc_ln318_1_fu_271_p1();
    void thread_trunc_ln318_fu_130_p1();
    void thread_trunc_ln331_1_fu_275_p1();
    void thread_trunc_ln331_fu_134_p1();
    void thread_trunc_ln334_1_fu_331_p1();
    void thread_trunc_ln334_fu_190_p1();
    void thread_xor_ln326_1_fu_500_p2();
    void thread_xor_ln326_fu_427_p2();
    void thread_xor_ln330_1_fu_357_p2();
    void thread_xor_ln330_fu_216_p2();
    void thread_zext_ln334_1_fu_321_p1();
    void thread_zext_ln334_fu_180_p1();
    void thread_ap_NS_fsm();
    void thread_hdltv_gen();
};

}

using namespace ap_rtl;

#endif
