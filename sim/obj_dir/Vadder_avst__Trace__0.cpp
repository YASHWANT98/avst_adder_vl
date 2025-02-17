// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vadder_avst__Syms.h"


void Vadder_avst___024root__trace_chg_0_sub_0(Vadder_avst___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vadder_avst___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root__trace_chg_0\n"); );
    // Init
    Vadder_avst___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vadder_avst___024root*>(voidSelf);
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vadder_avst___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vadder_avst___024root__trace_chg_0_sub_0(Vadder_avst___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root__trace_chg_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.reset));
    bufp->chgCData(oldp+2,(vlSelfRef.data_in),8);
    bufp->chgBit(oldp+3,(vlSelfRef.end_in));
    bufp->chgBit(oldp+4,(vlSelfRef.valid_in));
    bufp->chgBit(oldp+5,(vlSelfRef.ready_in));
    bufp->chgCData(oldp+6,(vlSelfRef.data_out),8);
    bufp->chgBit(oldp+7,(vlSelfRef.end_out));
    bufp->chgBit(oldp+8,(vlSelfRef.valid_out));
    bufp->chgBit(oldp+9,(vlSelfRef.ready_out));
    bufp->chgCData(oldp+10,(vlSelfRef.adder_avst__DOT__count_out),3);
    bufp->chgIData(oldp+11,(vlSelfRef.adder_avst__DOT__sum),32);
}

void Vadder_avst___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root__trace_cleanup\n"); );
    // Init
    Vadder_avst___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vadder_avst___024root*>(voidSelf);
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
