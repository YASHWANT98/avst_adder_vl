// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder_avst.h for the primary calling header

#include "Vadder_avst__pch.h"
#include "Vadder_avst__Syms.h"
#include "Vadder_avst___024root.h"

void Vadder_avst___024root___ctor_var_reset(Vadder_avst___024root* vlSelf);

Vadder_avst___024root::Vadder_avst___024root(Vadder_avst__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vadder_avst___024root___ctor_var_reset(this);
}

void Vadder_avst___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vadder_avst___024root::~Vadder_avst___024root() {
}
