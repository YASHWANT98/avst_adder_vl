// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vadder_avst.h for the primary calling header

#ifndef VERILATED_VADDER_AVST___024ROOT_H_
#define VERILATED_VADDER_AVST___024ROOT_H_  // guard

#include "verilated.h"


class Vadder_avst__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vadder_avst___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(data_in,7,0);
    VL_IN8(end_in,0,0);
    VL_IN8(valid_in,0,0);
    VL_OUT8(ready_in,0,0);
    VL_OUT8(data_out,7,0);
    VL_OUT8(end_out,0,0);
    VL_OUT8(valid_out,0,0);
    VL_IN8(ready_out,0,0);
    CData/*2:0*/ adder_avst__DOT__count_out;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ adder_avst__DOT__sum;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vadder_avst__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vadder_avst___024root(Vadder_avst__Syms* symsp, const char* v__name);
    ~Vadder_avst___024root();
    VL_UNCOPYABLE(Vadder_avst___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
