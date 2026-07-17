// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_top.h for the primary calling header

#ifndef VERILATED_VTB_TOP___024ROOT_H_
#define VERILATED_VTB_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_top___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_top__DOT__clk;
    CData/*0:0*/ tb_top__DOT__rst_n;
    CData/*0:0*/ tb_top__DOT__wr_en;
    CData/*0:0*/ tb_top__DOT__full;
    CData/*0:0*/ tb_top__DOT__rd_en;
    CData/*0:0*/ tb_top__DOT__empty;
    CData/*4:0*/ tb_top__DOT__dut__DOT__wr_ptr;
    CData/*4:0*/ tb_top__DOT__dut__DOT__rd_ptr;
    CData/*0:0*/ tb_top__DOT__mon__DOT__primed;
    CData/*0:0*/ tb_top__DOT__mon__DOT__p_rst_n;
    CData/*0:0*/ tb_top__DOT__mon__DOT__p_wr_en;
    CData/*0:0*/ tb_top__DOT__mon__DOT__p_rd_en;
    CData/*0:0*/ tb_top__DOT__mon__DOT__p_full;
    CData/*0:0*/ tb_top__DOT__mon__DOT__p_empty;
    CData/*3:0*/ __Vdlyvdim0__tb_top__DOT__dut__DOT__mem__v0;
    CData/*0:0*/ __Vdlyvset__tb_top__DOT__dut__DOT__mem__v0;
    CData/*4:0*/ __Vdly__tb_top__DOT__dut__DOT__rd_ptr;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_top__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_top__DOT__rst_n__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ tb_top__DOT__wr_data;
    IData/*31:0*/ tb_top__DOT__rd_data;
    IData/*31:0*/ tb_top__DOT__mon__DOT__cycle;
    IData/*31:0*/ tb_top__DOT__mon__DOT__win_start;
    IData/*31:0*/ tb_top__DOT__mon__DOT__p_wr_data;
    IData/*31:0*/ tb_top__DOT__mon__DOT__p_rd_data;
    IData/*31:0*/ __Vdlyvval__tb_top__DOT__dut__DOT__mem__v0;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<IData/*31:0*/, 16> tb_top__DOT__dut__DOT__mem;
    VlQueue<std::string> tb_top__DOT__mon__DOT__evq;
    std::string tb_top__DOT__testname;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_he3ce3317__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<3> __VactTriggered;
    VlTriggerVec<3> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_top___024root(Vtb_top__Syms* symsp, const char* v__name);
    ~Vtb_top___024root();
    VL_UNCOPYABLE(Vtb_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
