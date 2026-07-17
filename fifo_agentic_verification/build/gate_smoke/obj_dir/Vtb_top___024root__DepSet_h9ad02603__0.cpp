// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VL_ATTR_COLD void Vtb_top___024root___eval_initial__TOP(Vtb_top___024root* vlSelf);
VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__0(Vtb_top___024root* vlSelf);
VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1(Vtb_top___024root* vlSelf);
VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__2(Vtb_top___024root* vlSelf);

void Vtb_top___024root___eval_initial(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial\n"); );
    // Body
    Vtb_top___024root___eval_initial__TOP(vlSelf);
    Vtb_top___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_top___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_top___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__tb_top__DOT__clk__0 
        = vlSelf->tb_top__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__tb_top__DOT__rst_n__0 
        = vlSelf->tb_top__DOT__rst_n;
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Init
    IData/*31:0*/ tb_top__DOT____Vrepeat0;
    tb_top__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_top__DOT____Vrepeat1;
    tb_top__DOT____Vrepeat1 = 0;
    IData/*31:0*/ tb_top__DOT____Vrepeat2;
    tb_top__DOT____Vrepeat2 = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__1__cycles;
    __Vtask_tb_top__DOT__idle__1__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__2__cycles;
    __Vtask_tb_top__DOT__do_reset__2__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_word__3__data;
    __Vtask_tb_top__DOT__write_word__3__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__4__cycles;
    __Vtask_tb_top__DOT__idle__4__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__5__n;
    __Vtask_tb_top__DOT__read_burst__5__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__6__cycles;
    __Vtask_tb_top__DOT__idle__6__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__7__cycles;
    __Vtask_tb_top__DOT__do_reset__7__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__8__n;
    __Vtask_tb_top__DOT__write_burst__8__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__8__base;
    __Vtask_tb_top__DOT__write_burst__8__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__9__cycles;
    __Vtask_tb_top__DOT__idle__9__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__10__cycles;
    __Vtask_tb_top__DOT__do_reset__10__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__11__n;
    __Vtask_tb_top__DOT__write_burst__11__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__11__base;
    __Vtask_tb_top__DOT__write_burst__11__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__12__cycles;
    __Vtask_tb_top__DOT__idle__12__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_word__13__data;
    __Vtask_tb_top__DOT__write_word__13__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__14__cycles;
    __Vtask_tb_top__DOT__idle__14__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__15__n;
    __Vtask_tb_top__DOT__read_burst__15__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__16__cycles;
    __Vtask_tb_top__DOT__idle__16__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__17__cycles;
    __Vtask_tb_top__DOT__do_reset__17__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__18__n;
    __Vtask_tb_top__DOT__write_burst__18__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__18__base;
    __Vtask_tb_top__DOT__write_burst__18__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__19__cycles;
    __Vtask_tb_top__DOT__idle__19__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__20__n;
    __Vtask_tb_top__DOT__read_burst__20__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__21__cycles;
    __Vtask_tb_top__DOT__idle__21__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__22__cycles;
    __Vtask_tb_top__DOT__do_reset__22__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__23__cycles;
    __Vtask_tb_top__DOT__idle__23__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_word__24__data;
    __Vtask_tb_top__DOT__write_word__24__data = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__25__cycles;
    __Vtask_tb_top__DOT__idle__25__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__26__n;
    __Vtask_tb_top__DOT__read_burst__26__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__27__cycles;
    __Vtask_tb_top__DOT__idle__27__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__28__cycles;
    __Vtask_tb_top__DOT__do_reset__28__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__29__n;
    __Vtask_tb_top__DOT__write_burst__29__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__29__base;
    __Vtask_tb_top__DOT__write_burst__29__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__30__cycles;
    __Vtask_tb_top__DOT__idle__30__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__31__n;
    __Vtask_tb_top__DOT__read_burst__31__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__32__cycles;
    __Vtask_tb_top__DOT__idle__32__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__33__n;
    __Vtask_tb_top__DOT__write_burst__33__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__33__base;
    __Vtask_tb_top__DOT__write_burst__33__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__34__cycles;
    __Vtask_tb_top__DOT__idle__34__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__35__n;
    __Vtask_tb_top__DOT__read_burst__35__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__36__cycles;
    __Vtask_tb_top__DOT__idle__36__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__37__cycles;
    __Vtask_tb_top__DOT__do_reset__37__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__38__n;
    __Vtask_tb_top__DOT__write_burst__38__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__38__base;
    __Vtask_tb_top__DOT__write_burst__38__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__39__cycles;
    __Vtask_tb_top__DOT__idle__39__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__simultaneous_wr_rd__40__n;
    __Vtask_tb_top__DOT__simultaneous_wr_rd__40__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__simultaneous_wr_rd__40__base;
    __Vtask_tb_top__DOT__simultaneous_wr_rd__40__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i;
    __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__41__cycles;
    __Vtask_tb_top__DOT__idle__41__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__42__n;
    __Vtask_tb_top__DOT__read_burst__42__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__43__cycles;
    __Vtask_tb_top__DOT__idle__43__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__do_reset__44__cycles;
    __Vtask_tb_top__DOT__do_reset__44__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__45__n;
    __Vtask_tb_top__DOT__write_burst__45__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__45__base;
    __Vtask_tb_top__DOT__write_burst__45__base = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i;
    __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__46__cycles;
    __Vtask_tb_top__DOT__idle__46__cycles = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__read_burst__47__n;
    __Vtask_tb_top__DOT__read_burst__47__n = 0;
    IData/*31:0*/ __Vtask_tb_top__DOT__idle__48__cycles;
    __Vtask_tb_top__DOT__idle__48__cycles = 0;
    // Body
    if ((! VL_VALUEPLUSARGS_INN(64, std::string{"TEST=%s"}, 
                                vlSelf->tb_top__DOT__testname))) {
        vlSelf->tb_top__DOT__testname = std::string{"T1_cold_start"};
    }
    VL_WRITEF("[TST] test=%@ dut=snix_sync_fifo data_width=32 fifo_depth=16\n",
              -1,&(vlSelf->tb_top__DOT__testname));
    if (((((((((std::string{"T1_cold_start"} == vlSelf->tb_top__DOT__testname) 
               | (std::string{"T2_one_in_one_out"} 
                  == vlSelf->tb_top__DOT__testname)) 
              | (std::string{"T3_fill_sixteen"} == vlSelf->tb_top__DOT__testname)) 
             | (std::string{"T4_seventeenth_write"} 
                == vlSelf->tb_top__DOT__testname)) 
            | (std::string{"T5_full_drain"} == vlSelf->tb_top__DOT__testname)) 
           | (std::string{"T6_read_on_dry"} == vlSelf->tb_top__DOT__testname)) 
          | (std::string{"T7_lap_the_buffer"} == vlSelf->tb_top__DOT__testname)) 
         | (std::string{"T8_push_pull_together"} == vlSelf->tb_top__DOT__testname))) {
        if ((std::string{"T1_cold_start"} == vlSelf->tb_top__DOT__testname)) {
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = 3U;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__idle__1__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__1__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T2_one_in_one_out"} 
                    == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__2__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__2__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_word__3__data = 0xa5a50001U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            vlSelf->tb_top__DOT__wr_data = __Vtask_tb_top__DOT__write_word__3__data;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               46);
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__4__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__4__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__5__n = 1U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__5__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__6__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__6__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T3_fill_sixteen"} 
                    == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__7__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__7__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_burst__8__base = 0U;
            __Vtask_tb_top__DOT__write_burst__8__n = 0x10U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__8__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__8__base 
                                                + __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__8__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__9__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__9__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T4_seventeenth_write"} 
                    == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__10__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__10__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_burst__11__base = 0U;
            __Vtask_tb_top__DOT__write_burst__11__n = 0x10U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__11__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__11__base 
                                                + __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__11__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__12__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__12__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__write_word__13__data = 0xdeadbeefU;
            vlSelf->tb_top__DOT__wr_en = 1U;
            vlSelf->tb_top__DOT__wr_data = __Vtask_tb_top__DOT__write_word__13__data;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               46);
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__14__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__14__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__15__n = 0x10U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__15__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__16__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__16__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T5_full_drain"} == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__17__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__17__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_burst__18__base = 0U;
            __Vtask_tb_top__DOT__write_burst__18__n = 0x10U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__18__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__18__base 
                                                + __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__18__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__19__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__19__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__20__n = 0x10U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__20__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__21__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__21__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T6_read_on_dry"} == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__22__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__22__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            vlSelf->tb_top__DOT__rd_en = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               142);
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               142);
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               142);
            vlSelf->tb_top__DOT__rd_en = 0U;
            __Vtask_tb_top__DOT__idle__23__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__23__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__write_word__24__data = 0x77U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            vlSelf->tb_top__DOT__wr_data = __Vtask_tb_top__DOT__write_word__24__data;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               46);
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__25__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__25__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__26__n = 1U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__26__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__27__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__27__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else if ((std::string{"T7_lap_the_buffer"} 
                    == vlSelf->tb_top__DOT__testname)) {
            __Vtask_tb_top__DOT__do_reset__28__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__28__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_burst__29__base = 0U;
            __Vtask_tb_top__DOT__write_burst__29__n = 0x10U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__29__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__29__base 
                                                + __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__29__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__30__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__30__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__31__n = 0x10U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__31__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__32__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__32__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__write_burst__33__base = 0x1000U;
            __Vtask_tb_top__DOT__write_burst__33__n = 8U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__33__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__33__base 
                                                + __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__33__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__34__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__34__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__35__n = 8U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__35__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__36__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__36__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        } else {
            __Vtask_tb_top__DOT__do_reset__37__cycles = 3U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            vlSelf->tb_top__DOT__wr_data = 0U;
            vlSelf->tb_top__DOT__rst_n = 0U;
            tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__37__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   39);
                tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rst_n = 1U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               41);
            __Vtask_tb_top__DOT__write_burst__38__base = 0U;
            __Vtask_tb_top__DOT__write_burst__38__n = 8U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__38__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__38__base 
                                                + __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   54);
                __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__38__unnamedblk1__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            __Vtask_tb_top__DOT__idle__39__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__39__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__simultaneous_wr_rd__40__base = 0x2000U;
            __Vtask_tb_top__DOT__simultaneous_wr_rd__40__n = 4U;
            vlSelf->tb_top__DOT__wr_en = 1U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i = 0U;
            while (VL_LTS_III(32, __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i, __Vtask_tb_top__DOT__simultaneous_wr_rd__40__n)) {
                vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__simultaneous_wr_rd__40__base 
                                                + __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i);
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   70);
                __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i 
                    = ((IData)(1U) + __Vtask_tb_top__DOT__simultaneous_wr_rd__40__unnamedblk2__DOT__i);
            }
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               73);
            __Vtask_tb_top__DOT__idle__41__cycles = 1U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__41__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vtask_tb_top__DOT__read_burst__42__n = 8U;
            vlSelf->tb_top__DOT__rd_en = 1U;
            tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__42__n;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   61);
                tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                           - (IData)(1U));
            }
            vlSelf->tb_top__DOT__rd_en = 0U;
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               63);
            __Vtask_tb_top__DOT__idle__43__cycles = 2U;
            vlSelf->tb_top__DOT__wr_en = 0U;
            vlSelf->tb_top__DOT__rd_en = 0U;
            tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__43__cycles;
            while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge tb_top.clk)", 
                                                                   "tb_top.sv", 
                                                                   78);
                tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
        }
    } else if (VL_LIKELY((std::string{"T9_four_beat_burst"} 
                          == vlSelf->tb_top__DOT__testname))) {
        __Vtask_tb_top__DOT__do_reset__44__cycles = 3U;
        vlSelf->tb_top__DOT__wr_en = 0U;
        vlSelf->tb_top__DOT__rd_en = 0U;
        vlSelf->tb_top__DOT__wr_data = 0U;
        vlSelf->tb_top__DOT__rst_n = 0U;
        tb_top__DOT____Vrepeat0 = __Vtask_tb_top__DOT__do_reset__44__cycles;
        while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat0)) {
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               39);
            tb_top__DOT____Vrepeat0 = (tb_top__DOT____Vrepeat0 
                                       - (IData)(1U));
        }
        vlSelf->tb_top__DOT__rst_n = 1U;
        co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_top.clk)", 
                                                           "tb_top.sv", 
                                                           41);
        __Vtask_tb_top__DOT__write_burst__45__base = 0xb0U;
        __Vtask_tb_top__DOT__write_burst__45__n = 4U;
        vlSelf->tb_top__DOT__wr_en = 1U;
        __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i, __Vtask_tb_top__DOT__write_burst__45__n)) {
            vlSelf->tb_top__DOT__wr_data = (__Vtask_tb_top__DOT__write_burst__45__base 
                                            + __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i);
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               54);
            __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__write_burst__45__unnamedblk1__DOT__i);
        }
        vlSelf->tb_top__DOT__wr_en = 0U;
        __Vtask_tb_top__DOT__idle__46__cycles = 2U;
        vlSelf->tb_top__DOT__wr_en = 0U;
        vlSelf->tb_top__DOT__rd_en = 0U;
        tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__46__cycles;
        while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               78);
            tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                       - (IData)(1U));
        }
        __Vtask_tb_top__DOT__read_burst__47__n = 4U;
        vlSelf->tb_top__DOT__rd_en = 1U;
        tb_top__DOT____Vrepeat1 = __Vtask_tb_top__DOT__read_burst__47__n;
        while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat1)) {
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               61);
            tb_top__DOT____Vrepeat1 = (tb_top__DOT____Vrepeat1 
                                       - (IData)(1U));
        }
        vlSelf->tb_top__DOT__rd_en = 0U;
        co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge tb_top.clk)", 
                                                           "tb_top.sv", 
                                                           63);
        __Vtask_tb_top__DOT__idle__48__cycles = 2U;
        vlSelf->tb_top__DOT__wr_en = 0U;
        vlSelf->tb_top__DOT__rd_en = 0U;
        tb_top__DOT____Vrepeat2 = __Vtask_tb_top__DOT__idle__48__cycles;
        while (VL_LTS_III(32, 0U, tb_top__DOT____Vrepeat2)) {
            co_await vlSelf->__VtrigSched_he3ce3317__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge tb_top.clk)", 
                                                               "tb_top.sv", 
                                                               78);
            tb_top__DOT____Vrepeat2 = (tb_top__DOT____Vrepeat2 
                                       - (IData)(1U));
        }
    } else {
        VL_WRITEF("[TST] test=%@ status=unknown_test\n",
                  -1,&(vlSelf->tb_top__DOT__testname));
        VL_FINISH_MT("tb_top.sv", 183, "");
    }
    VL_WRITEF("[TST] test=%@ status=completed\n",-1,
              &(vlSelf->tb_top__DOT__testname));
    VL_FINISH_MT("tb_top.sv", 188, "");
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__1(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Body
    co_await vlSelf->__VdlySched.delay(0x1312d00ULL, 
                                       nullptr, "tb_top.sv", 
                                       193);
    VL_WRITEF("[TST] test=%@ status=timeout\n",-1,&(vlSelf->tb_top__DOT__testname));
    VL_FINISH_MT("tb_top.sv", 195, "");
}

VL_INLINE_OPT VlCoroutine Vtb_top___024root___eval_initial__TOP__Vtiming__2(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial__TOP__Vtiming__2\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "tb_top.sv", 
                                           32);
        vlSelf->tb_top__DOT__clk = (1U & (~ (IData)(vlSelf->tb_top__DOT__clk)));
    }
}

void Vtb_top___024root___eval_act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->__Vdly__tb_top__DOT__dut__DOT__rd_ptr = vlSelf->tb_top__DOT__dut__DOT__rd_ptr;
    vlSelf->__Vdlyvset__tb_top__DOT__dut__DOT__mem__v0 = 0U;
    if (vlSelf->tb_top__DOT__rst_n) {
        if (((IData)(vlSelf->tb_top__DOT__wr_en) & 
             (~ (IData)(vlSelf->tb_top__DOT__full)))) {
            vlSelf->__Vdlyvval__tb_top__DOT__dut__DOT__mem__v0 
                = vlSelf->tb_top__DOT__wr_data;
            vlSelf->__Vdlyvset__tb_top__DOT__dut__DOT__mem__v0 = 1U;
            vlSelf->__Vdlyvdim0__tb_top__DOT__dut__DOT__mem__v0 
                = (0xfU & (IData)(vlSelf->tb_top__DOT__dut__DOT__wr_ptr));
            vlSelf->tb_top__DOT__dut__DOT__wr_ptr = 
                (0x1fU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__dut__DOT__wr_ptr)));
        }
    } else {
        vlSelf->tb_top__DOT__dut__DOT__wr_ptr = 0U;
    }
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__1(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__1\n"); );
    // Init
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__49__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__50__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__51__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__52__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__53__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__54__s;
    std::string __Vtask_tb_top__DOT__mon__DOT__ev__55__s;
    IData/*31:0*/ __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i;
    __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i = 0;
    std::string __Vtemp_1;
    // Body
    if (vlSelf->tb_top__DOT__mon__DOT__primed) {
        if (((IData)(vlSelf->tb_top__DOT__rst_n) != (IData)(vlSelf->tb_top__DOT__mon__DOT__p_rst_n))) {
            __Vtask_tb_top__DOT__mon__DOT__ev__49__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# pin=rst_n   %0# -> %0#",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 1,(IData)(vlSelf->tb_top__DOT__mon__DOT__p_rst_n),
                                 1,vlSelf->tb_top__DOT__rst_n) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__49__s);
        }
        if (((IData)(vlSelf->tb_top__DOT__wr_en) != (IData)(vlSelf->tb_top__DOT__mon__DOT__p_wr_en))) {
            __Vtask_tb_top__DOT__mon__DOT__ev__50__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# pin=wr_en   %0# -> %0#",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 1,(IData)(vlSelf->tb_top__DOT__mon__DOT__p_wr_en),
                                 1,vlSelf->tb_top__DOT__wr_en) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__50__s);
        }
        if ((vlSelf->tb_top__DOT__wr_data != vlSelf->tb_top__DOT__mon__DOT__p_wr_data)) {
            __Vtask_tb_top__DOT__mon__DOT__ev__51__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# pin=wr_data 0x%08x -> 0x%08x",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 32,vlSelf->tb_top__DOT__mon__DOT__p_wr_data,
                                 32,vlSelf->tb_top__DOT__wr_data) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__51__s);
        }
        if (((IData)(vlSelf->tb_top__DOT__rd_en) != (IData)(vlSelf->tb_top__DOT__mon__DOT__p_rd_en))) {
            __Vtask_tb_top__DOT__mon__DOT__ev__52__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# pin=rd_en   %0# -> %0#",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 1,(IData)(vlSelf->tb_top__DOT__mon__DOT__p_rd_en),
                                 1,vlSelf->tb_top__DOT__rd_en) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__52__s);
        }
        if ((vlSelf->tb_top__DOT__rd_data != vlSelf->tb_top__DOT__mon__DOT__p_rd_data)) {
            __Vtask_tb_top__DOT__mon__DOT__ev__53__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# pin=rd_data 0x%08x -> 0x%08x",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 32,vlSelf->tb_top__DOT__mon__DOT__p_rd_data,
                                 32,vlSelf->tb_top__DOT__rd_data) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__53__s);
        }
        if (((IData)(vlSelf->tb_top__DOT__full) != (IData)(vlSelf->tb_top__DOT__mon__DOT__p_full))) {
            __Vtask_tb_top__DOT__mon__DOT__ev__54__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# flag=full  %0# -> %0#",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 1,(IData)(vlSelf->tb_top__DOT__mon__DOT__p_full),
                                 1,vlSelf->tb_top__DOT__full) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__54__s);
        }
        if (((IData)(vlSelf->tb_top__DOT__empty) != (IData)(vlSelf->tb_top__DOT__mon__DOT__p_empty))) {
            __Vtask_tb_top__DOT__mon__DOT__ev__55__s 
                = VL_SFORMATF_NX("[EVT] t=%0t cycle=%0# flag=empty %0# -> %0#",
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                                 1,(IData)(vlSelf->tb_top__DOT__mon__DOT__p_empty),
                                 1,vlSelf->tb_top__DOT__empty) ;
            vlSelf->tb_top__DOT__mon__DOT__evq.push_back(__Vtask_tb_top__DOT__mon__DOT__ev__55__s);
        }
    }
    if (VL_UNLIKELY(((IData)(vlSelf->tb_top__DOT__mon__DOT__primed) 
                     & (0U == VL_MODDIV_III(32, ((IData)(1U) 
                                                 + vlSelf->tb_top__DOT__mon__DOT__cycle), (IData)(0x14U)))))) {
        VL_WRITEF("[WIN] cycles=%0#..%0# events=%0d\n",
                  32,vlSelf->tb_top__DOT__mon__DOT__win_start,
                  32,vlSelf->tb_top__DOT__mon__DOT__cycle,
                  32,vlSelf->tb_top__DOT__mon__DOT__evq.size());
        __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i = 0U;
        while (VL_LTS_III(32, __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i, vlSelf->tb_top__DOT__mon__DOT__evq.size())) {
            __Vtemp_1 = vlSelf->tb_top__DOT__mon__DOT__evq.at(__Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i);
            VL_WRITEF("%@\n",-1,&(__Vtemp_1));
            __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i 
                = ((IData)(1U) + __Vtask_tb_top__DOT__mon__DOT__flush_window__56__unnamedblk2_1__DOT__i);
        }
        vlSelf->tb_top__DOT__mon__DOT__evq.clear();
        vlSelf->tb_top__DOT__mon__DOT__win_start = 
            ((IData)(1U) + vlSelf->tb_top__DOT__mon__DOT__cycle);
    }
    vlSelf->tb_top__DOT__mon__DOT__cycle = ((IData)(1U) 
                                            + vlSelf->tb_top__DOT__mon__DOT__cycle);
    vlSelf->tb_top__DOT__mon__DOT__primed = 1U;
    vlSelf->tb_top__DOT__mon__DOT__p_wr_en = vlSelf->tb_top__DOT__wr_en;
    vlSelf->tb_top__DOT__mon__DOT__p_wr_data = vlSelf->tb_top__DOT__wr_data;
    vlSelf->tb_top__DOT__mon__DOT__p_rd_en = vlSelf->tb_top__DOT__rd_en;
    vlSelf->tb_top__DOT__mon__DOT__p_rst_n = vlSelf->tb_top__DOT__rst_n;
    vlSelf->tb_top__DOT__mon__DOT__p_full = vlSelf->tb_top__DOT__full;
    vlSelf->tb_top__DOT__mon__DOT__p_empty = vlSelf->tb_top__DOT__empty;
    vlSelf->tb_top__DOT__mon__DOT__p_rd_data = vlSelf->tb_top__DOT__rd_data;
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__2(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__2\n"); );
    // Body
    if (vlSelf->tb_top__DOT__rst_n) {
        if (((IData)(vlSelf->tb_top__DOT__rd_en) & 
             (~ (IData)(vlSelf->tb_top__DOT__empty)))) {
            vlSelf->__Vdly__tb_top__DOT__dut__DOT__rd_ptr 
                = (0x1fU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__dut__DOT__rd_ptr)));
            vlSelf->tb_top__DOT__rd_data = vlSelf->tb_top__DOT__dut__DOT__mem
                [(0xfU & (IData)(vlSelf->tb_top__DOT__dut__DOT__rd_ptr))];
        }
    } else {
        vlSelf->__Vdly__tb_top__DOT__dut__DOT__rd_ptr = 0U;
        vlSelf->tb_top__DOT__rd_data = 0U;
    }
    if (vlSelf->__Vdlyvset__tb_top__DOT__dut__DOT__mem__v0) {
        vlSelf->tb_top__DOT__dut__DOT__mem[vlSelf->__Vdlyvdim0__tb_top__DOT__dut__DOT__mem__v0] 
            = vlSelf->__Vdlyvval__tb_top__DOT__dut__DOT__mem__v0;
    }
    vlSelf->tb_top__DOT__dut__DOT__rd_ptr = vlSelf->__Vdly__tb_top__DOT__dut__DOT__rd_ptr;
    vlSelf->tb_top__DOT__full = (((1U & ((IData)(vlSelf->tb_top__DOT__dut__DOT__wr_ptr) 
                                         >> 4U)) != 
                                  (1U & ((IData)(vlSelf->tb_top__DOT__dut__DOT__rd_ptr) 
                                         >> 4U))) & 
                                 ((0xfU & (IData)(vlSelf->tb_top__DOT__dut__DOT__wr_ptr)) 
                                  == (0xfU & (IData)(vlSelf->tb_top__DOT__dut__DOT__rd_ptr))));
    vlSelf->tb_top__DOT__empty = ((IData)(vlSelf->tb_top__DOT__dut__DOT__rd_ptr) 
                                  == (IData)(vlSelf->tb_top__DOT__dut__DOT__wr_ptr));
}

void Vtb_top___024root___eval_nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__2(vlSelf);
    }
}

void Vtb_top___024root___timing_resume(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___timing_resume\n"); );
    // Body
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_he3ce3317__0.resume("@(posedge tb_top.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vtb_top___024root___timing_commit(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___timing_commit\n"); );
    // Body
    if ((! (2ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_he3ce3317__0.commit("@(posedge tb_top.clk)");
    }
}

void Vtb_top___024root___eval_triggers__act(Vtb_top___024root* vlSelf);

bool Vtb_top___024root___eval_phase__act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_top___024root___eval_triggers__act(vlSelf);
    Vtb_top___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_top___024root___timing_resume(vlSelf);
        Vtb_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_top___024root___eval_phase__nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb_top.sv", 13, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb_top.sv", 13, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb_top___024root___eval_debug_assertions(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
