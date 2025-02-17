import esdl.base.core: Entity;
import esdl.data.bvec: ubvec;
import esdl.intf.verilator.verilated: VerilatedContext, VerilatedModel, VlExport;
import esdl.intf.verilator.trace: VerilatedVcdC, VerilatedTraceBaseC,VerilatedVcdD;

//DESCRIPTION: Dlang code to link D classes and functions with the C++ classes


extern(C++) {
    align(8) class Vadder_avst: VerilatedModel {
        //Symbol table, currently unimplemented, using void pointer
        void* vlSymsp;

        //PORTS 
        ubvec!(1)* clk;
        ubvec!(1)* reset;
        ubvec!(8)* data_in;
        ubvec!(1)* end_in;
        ubvec!(1)* valid_in;
        ubvec!(1)* ready_in;
        ubvec!(8)* data_out;
        ubvec!(1)* end_out;
        ubvec!(1)* valid_out;
        ubvec!(1)* ready_out;

        // CELLS
        //Currently unimplemented, using void pointers 

        // Root instance pointer, currently unimplemented, using void pointers 
        void* rootp;
        this(VerilatedContext* contextp, const char* name = "TOP".ptr);
        ~this();
        final void eval();
        final void eval_step();
        final void eval_end_step();
        final void trace(VerilatedTraceBaseC tfp, int levels, int options = 0) {
              contextp().trace(tfp, levels, options);
        }
        final const(char*) name();
        final override char* hierName() const;
        final override char* modelName() const;
        final override uint threads() const;
    }
    Vadder_avst create_Vadder_avst();
    void finalize(Vadder_avst obj);
    
}
class DVadder_avst: Entity
 {
    Vadder_avst _dut;
    
    this () {
        _dut = create_Vadder_avst();
    }
    override void doConnect() {
        clk(_dut.clk);
        reset(_dut.reset);
        data_in(_dut.data_in);
        end_in(_dut.end_in);
        valid_in(_dut.valid_in);
        ready_in(_dut.ready_in);
        data_out(_dut.data_out);
        end_out(_dut.end_out);
        valid_out(_dut.valid_out);
        ready_out(_dut.ready_out);
    }

    //Functions for Ports 
    VlExport!(1) clk;
    VlExport!(1) reset;
    VlExport!(8) data_in;
    VlExport!(1) end_in;
    VlExport!(1) valid_in;
    VlExport!(1) ready_in;
    VlExport!(8) data_out;
    VlExport!(1) end_out;
    VlExport!(1) valid_out;
    VlExport!(1) ready_out;
    final void eval() {
        _dut.eval();
    }
    final void finish() {
        finalize(_dut);
    }
    final void trace(VerilatedVcdD tfp, int levels, int options = 0) {
        _dut.trace(tfp.getTraceBase(), levels, options);
    }
    final void trace(VerilatedTraceBaseC tfp, int levels, int options = 0) {
        _dut.trace(tfp, levels, options);
    }
}
