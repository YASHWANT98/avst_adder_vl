// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder_avst.h for the primary calling header

#include "Vadder_avst__pch.h"
#include "Vadder_avst___024root.h"

void Vadder_avst___024root___eval_act(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vadder_avst___024root___nba_sequent__TOP__0(Vadder_avst___024root* vlSelf);

void Vadder_avst___024root___eval_nba(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadder_avst___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vadder_avst___024root___nba_sequent__TOP__0(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __Vdly__ready_in;
    __Vdly__ready_in = 0;
    IData/*31:0*/ __Vdly__adder_avst__DOT__sum;
    __Vdly__adder_avst__DOT__sum = 0;
    CData/*2:0*/ __Vdly__adder_avst__DOT__count_out;
    __Vdly__adder_avst__DOT__count_out = 0;
    // Body
    __Vdly__adder_avst__DOT__count_out = vlSelfRef.adder_avst__DOT__count_out;
    __Vdly__ready_in = vlSelfRef.ready_in;
    __Vdly__adder_avst__DOT__sum = vlSelfRef.adder_avst__DOT__sum;
    if ((1U & (~ (IData)(vlSelfRef.reset)))) {
        if ((4U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            __Vdly__ready_in = 0U;
        } else if ((3U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            __Vdly__ready_in = 0U;
        } else if ((2U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            __Vdly__ready_in = 0U;
        } else if ((1U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            __Vdly__ready_in = 0U;
        } else if ((0U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            __Vdly__ready_in = 1U;
        }
        if ((4U != (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            if ((3U != (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
                if ((2U != (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
                    if ((1U != (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
                        if ((0U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
                            __Vdly__adder_avst__DOT__sum = 0U;
                        }
                    }
                }
            }
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__adder_avst__DOT__count_out = 7U;
        __Vdly__ready_in = 1U;
        __Vdly__adder_avst__DOT__sum = 0U;
        vlSelfRef.data_out = 0U;
        vlSelfRef.end_out = 0U;
        vlSelfRef.valid_out = 0U;
    } else {
        if (((IData)(vlSelfRef.valid_in) & (IData)(vlSelfRef.ready_in))) {
            __Vdly__adder_avst__DOT__sum = (vlSelfRef.adder_avst__DOT__sum 
                                            + (IData)(vlSelfRef.data_in));
            if (vlSelfRef.end_in) {
                __Vdly__ready_in = 0U;
                __Vdly__adder_avst__DOT__count_out = 4U;
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.ready_in)))) {
            if (vlSelfRef.ready_out) {
                __Vdly__adder_avst__DOT__count_out 
                    = (7U & ((IData)(vlSelfRef.adder_avst__DOT__count_out) 
                             - (IData)(1U)));
            }
        }
        if ((4U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.data_out = (vlSelfRef.adder_avst__DOT__sum 
                                  >> 0x18U);
        } else if ((3U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.data_out = (0xffU & (vlSelfRef.adder_avst__DOT__sum 
                                           >> 0x10U));
        } else if ((2U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.data_out = (0xffU & (vlSelfRef.adder_avst__DOT__sum 
                                           >> 8U));
        } else if ((1U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.data_out = (0xffU & vlSelfRef.adder_avst__DOT__sum);
        } else if ((0U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.data_out = 0U;
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.reset)))) {
        if ((4U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.end_out = 0U;
            vlSelfRef.valid_out = 1U;
        } else if ((3U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.end_out = 0U;
            vlSelfRef.valid_out = 1U;
        } else if ((2U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.end_out = 0U;
            vlSelfRef.valid_out = 1U;
        } else if ((1U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.end_out = 1U;
            vlSelfRef.valid_out = 1U;
        } else if ((0U == (IData)(vlSelfRef.adder_avst__DOT__count_out))) {
            vlSelfRef.end_out = 0U;
            vlSelfRef.valid_out = 0U;
        }
    }
    vlSelfRef.ready_in = __Vdly__ready_in;
    vlSelfRef.adder_avst__DOT__sum = __Vdly__adder_avst__DOT__sum;
    vlSelfRef.adder_avst__DOT__count_out = __Vdly__adder_avst__DOT__count_out;
}

void Vadder_avst___024root___eval_triggers__act(Vadder_avst___024root* vlSelf);

bool Vadder_avst___024root___eval_phase__act(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vadder_avst___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vadder_avst___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vadder_avst___024root___eval_phase__nba(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vadder_avst___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder_avst___024root___dump_triggers__nba(Vadder_avst___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder_avst___024root___dump_triggers__act(Vadder_avst___024root* vlSelf);
#endif  // VL_DEBUG

void Vadder_avst___024root___eval(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vadder_avst___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../rtl/adder_avst.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vadder_avst___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../rtl/adder_avst.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vadder_avst___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vadder_avst___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vadder_avst___024root___eval_debug_assertions(Vadder_avst___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder_avst___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelfRef.reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelfRef.end_in & 0xfeU))) {
        Verilated::overWidthError("end_in");}
    if (VL_UNLIKELY((vlSelfRef.valid_in & 0xfeU))) {
        Verilated::overWidthError("valid_in");}
    if (VL_UNLIKELY((vlSelfRef.ready_out & 0xfeU))) {
        Verilated::overWidthError("ready_out");}
}
#endif  // VL_DEBUG
