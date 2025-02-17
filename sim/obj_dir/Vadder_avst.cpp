// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vadder_avst__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vadder_avst::Vadder_avst(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vadder_avst__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , reset{vlSymsp->TOP.reset}
    , data_in{vlSymsp->TOP.data_in}
    , end_in{vlSymsp->TOP.end_in}
    , valid_in{vlSymsp->TOP.valid_in}
    , ready_in{vlSymsp->TOP.ready_in}
    , data_out{vlSymsp->TOP.data_out}
    , end_out{vlSymsp->TOP.end_out}
    , valid_out{vlSymsp->TOP.valid_out}
    , ready_out{vlSymsp->TOP.ready_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vadder_avst::Vadder_avst(const char* _vcname__)
    : Vadder_avst(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vadder_avst::~Vadder_avst() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vadder_avst___024root___eval_debug_assertions(Vadder_avst___024root* vlSelf);
#endif  // VL_DEBUG
void Vadder_avst___024root___eval_static(Vadder_avst___024root* vlSelf);
void Vadder_avst___024root___eval_initial(Vadder_avst___024root* vlSelf);
void Vadder_avst___024root___eval_settle(Vadder_avst___024root* vlSelf);
void Vadder_avst___024root___eval(Vadder_avst___024root* vlSelf);

void Vadder_avst::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vadder_avst::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vadder_avst___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vadder_avst___024root___eval_static(&(vlSymsp->TOP));
        Vadder_avst___024root___eval_initial(&(vlSymsp->TOP));
        Vadder_avst___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vadder_avst___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vadder_avst::eventsPending() { return false; }

uint64_t Vadder_avst::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vadder_avst::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vadder_avst___024root___eval_final(Vadder_avst___024root* vlSelf);

VL_ATTR_COLD void Vadder_avst::final() {
    Vadder_avst___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vadder_avst::hierName() const { return vlSymsp->name(); }
const char* Vadder_avst::modelName() const { return "Vadder_avst"; }
unsigned Vadder_avst::threads() const { return 1; }
void Vadder_avst::prepareClone() const { contextp()->prepareClone(); }
void Vadder_avst::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vadder_avst::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vadder_avst___024root__trace_decl_types(VerilatedVcd* tracep);

void Vadder_avst___024root__trace_init_top(Vadder_avst___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vadder_avst___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vadder_avst___024root*>(voidSelf);
    Vadder_avst__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vadder_avst___024root__trace_decl_types(tracep);
    Vadder_avst___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vadder_avst___024root__trace_register(Vadder_avst___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vadder_avst::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vadder_avst::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vadder_avst___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
