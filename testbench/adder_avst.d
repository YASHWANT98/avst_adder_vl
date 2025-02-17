import esdl;
import esdl.intf.verilator.verilated;
import esdl.intf.verilator.trace;
import uvm;
import std.stdio;
import std.string: format;

class avst_item: uvm_sequence_item                                        // Initialising avst_item as Sequence item 
{
  mixin uvm_object_utils;

  @UVM_DEFAULT {                                                        
    @rand ubyte data;                                                     // unsigned 8-bit data 
    @rand ubyte delay;                                                    // unsigned 8-bit delay
    ubvec!1 end;                                                          
  }
   
  this(string name = "avst_item") {
    super(name);
  }
                                                                          // delay distribution  = 0 for 99% and 1-9 for 1%
  constraint! q{                                                          
    delay dist [0 := 99, 1:9 :/ 1];
  } cst_delay;

                                                                          // data range = (0x30 to 0x7a)
  constraint! q{
    data >= 0x30;
    data <= 0x7a;
  } cst_ascii;

}

class avst_phrase_seq: uvm_sequence!avst_item                             // Created only for this testcase 
{

  mixin uvm_object_utils;

  @UVM_DEFAULT {
    ubyte[] phrase;                                                       // dynammic integer array phrase  
  }

  this(string name="") {
    super(name);
  }

  void set_phrase(string phrase) {                                        //  function that take a string 0-9,A-Z,a-z anything with ascii code b/w 0x30 - 0x7a
    this.phrase = cast(ubyte[]) phrase;                                   //  Return the ASCII code to phrase
  }

  bool _is_final;

  bool is_finalized() {
    return _is_final;
  }

  void opOpAssign(string op)(avst_item item) if(op == "~")                // Concatenate the item.data to phrase, and then return is_final when item stream is endded
    {
      assert(item !is null);
      phrase ~= item.data;
      if (item.end) _is_final = true;                                     
    }
  // task
  override void body() {                                                  // Assign data from phrase to req.data and set req.end after transaction is done
    // uvm_info("avst_seq", "Starting sequence", UVM_MEDIUM);

    for (size_t i=0; i!=phrase.length; ++i) {
      wait_for_grant();
      req.data = cast(ubyte) phrase[i];
      if (i == phrase.length - 1) req.end = true;
      else req.end = false;
      avst_item cloned = cast(avst_item) req.clone;
      send_request(cloned);
    }
    
    // uvm_info("avst_item", "Finishing sequence", UVM_MEDIUM);
  } // body

  ubyte[] transform() {                                                  // adds the bytes in "phrase", one by one and assign the sum to "value"
    ubyte[] retval;
    uint value;
    foreach (c; phrase) {
      value += c;
    }
    for (int i=4; i!=0; --i) {                                           // The sum is then stored in a array "retval" of size 4 each coloumn of size 1 byte 
      retval ~= cast (ubyte) (value >> (i-1)*8);
    }
    return retval;                                                       // "retval" is returned
  }
}

class avst_seq: uvm_sequence!avst_item                                   // Initialising Sequence Item
{
  @UVM_DEFAULT {
    @rand uint seq_size;                                                 
  }

  mixin uvm_object_utils;


  this(string name="") {
    super(name);
    req = avst_item.type_id.create(name ~ ".req");                     // create a new instance of avst_item and registers "req" to UVM factory with the handle type_id and track it unique name ".req"
  }
                                                                       // Constraint set on sequence item size [64,16]
  constraint!q{
    seq_size < 64;
    seq_size > 16;
  } seq_size_cst;

  // task
  override void body() {                                                // sending each each sequence data present in sequence item one by one 
      for (size_t i=0; i!=seq_size; ++i) {                               
	wait_for_grant();
	req.randomize();
	if (i == seq_size - 1) req.end = true;                                // "req.end" is set when every data in seq item is sent
	else req.end = false;
	avst_item cloned = cast(avst_item) req.clone;                         // The "clone" is used here to send each sequence data present in the item one by one
	// uvm_info("avst_item", cloned.sprint, UVM_DEBUG);
	send_request(cloned);
      }
      // uvm_info("avst_item", "Finishing sequence", UVM_DEBUG);
    }

}

class avst_driver: uvm_driver!(avst_item)                              // Initialising UVM Driver with base class uvm_driver templating with seq_item
{

  mixin uvm_component_utils;                                           // Registering to factory
  
  AvstIntf avst_in;                                                    // "avst_in" instance of "AvstIntf" is created for I/P transaction from the Sequencer 

  this(string name, uvm_component parent = null) {
    super(name, parent);
    uvm_config_db!AvstIntf.get(this, "", "avst_in", avst_in);          //  Initialing acst_in as config_db so that it communicate with DUT
    assert (avst_in !is null);
  }


  override void run_phase(uvm_phase phase) {                            // RUN PHASE :
    super.run_phase(phase);
    while (true) {
      // uvm_info("AVL TRANSACTION", req.sprint(), UVM_DEBUG);
      seq_item_port.try_next_item(req);                                 // "req" is assigned the next data present in the current sequence item

      if (req !is null) {                                               

	for (int i = 0; i != req.delay; ++i) {                                // For number of "req.delay" clock cycles, input (end and valid bit) will 0  
	  wait (avst_in.clock.negedge());

	  avst_in.end = false;
	  avst_in.valid = false;
	}
	
	while (avst_in.ready == 0 || avst_in.reset == 1) {                    // Till "input ready" = 0  OR "reset" = 1 , input (end and valid bit) will 0
	  wait (avst_in.clock.negedge());

	  avst_in.end = false;
	  avst_in.valid = false;
	}
	  

	wait (avst_in.clock.negedge());                                       

	avst_in.data  = req.data;                                            // Once the above conditions are met, the input (data and end is assigned to req.data and req.end and valid = 1)
	avst_in.end   = req.end;
	avst_in.valid = true;

	// req_analysis.write(req);
	seq_item_port.item_done();                                            // The data present in "req" is all transfered to  "avst_in" in the driver
      }
      else {
	wait (avst_in.clock.negedge());                                      // If "req" = NULL ,  input (end and valid bit) will 0

	avst_in.end = false;
	avst_in.valid = false;
      }
    }
  }

  // protected void trans_received(avst_item tr) {}
  // protected void trans_executed(avst_item tr) {}

}

class avst_out_driver: uvm_component                                  // Another Driver Class for driving out the data to monitor - Not a standard practice in UVM
{

  mixin uvm_component_utils;                                          // Factory resgitration 
  
  AvstIntf avst_out;                                                  // Initialing an instance "avst_out" of "AvstIntf" for O/P transaction towards the monitor  

  this(string name, uvm_component parent = null) {                  
    super(name, parent);
    uvm_config_db!AvstIntf.get(this, "", "avst_out", avst_out);
    assert (avst_out !is null);
  }


  override void run_phase(uvm_phase phase) {                          // RUN PHASE : 
    super.run_phase(phase);
    while (true) {
      uint delay;
      uint flag;
      delay = urandom(0, 10);                                         // Randoming the "delay" clock cycles b/w 0 to 10
      flag = urandom(0, 10);
      if (flag == 0) {                                                // avst_out.ready = 0 , when flag = 0
	for (size_t i=0; i!=delay; ++i) {
	  avst_out.ready = false;                                           //  delay clock cycles 
	  wait (avst_out.clock.negedge());
	}
      }
      else {
	avst_out.ready = true;                                              // avst_out.ready = 1, when flag != 0 
	wait (avst_out.clock.negedge());
      }
    }
  }

  // protected void trans_received(avst_item tr) {}
  // protected void trans_executed(avst_item tr) {}

}

class avst_snooper: uvm_monitor                                     // UVM Snooper (Here it performs the duty of the Monitor)
{
  mixin uvm_component_utils;                                        // Factory registration 

  AvstIntf avst;                                                    // Creating an instance "avst" of "AvstIntf"

  int _ready_latency = 0;

  void set_read_latency(int latency) {                              // latency is default set to 1
    assert (latency == 0 || latency == 1);
    _ready_latency = latency;
  }

  bool prev_ready;

  this (string name, uvm_component parent = null) {
    super(name,parent);
    uvm_config_db!AvstIntf.get(this, "", "avst", avst);           // Get the values from the DUT 
    assert (avst !is null);
  }

  @UVM_BUILD {                                                    // BUILD PHASE : Building snooper.egress 
    uvm_analysis_port!avst_item egress;
  }
  
  override void run_phase(uvm_phase phase) {                      // RUN PHASE : 
    super.run_phase(phase);

    while (true) {
      wait (avst.clock.posedge());
      if (_ready_latency == 0) 
            prev_ready = avst.ready;
      if (avst.reset == 1 || prev_ready == 0 || avst.valid == 0)
      {
	      if (_ready_latency == 1) prev_ready = avst.ready;
	      continue;
      }
      else 
      {
	      avst_item item = avst_item.type_id.create(get_full_name() ~ ".avst_item");
	      item.data = avst.data;
	      item.end = cast(bool) avst.end;
	      egress.write(item);
	      uvm_info("AVL Monitored Req", item.sprint(), UVM_DEBUG);
	      // writeln("valid input");
      }
      if (_ready_latency == 1) 
              prev_ready = avst.ready;
    }
  }

}


class avst_scoreboard: uvm_scoreboard                           // Scoreboard Initialisation
{
  this(string name, uvm_component parent = null) {
    super(name, parent);
  }

  mixin uvm_component_utils;                                     // Factory Registration

  uvm_phase phase_run;

  uint matched;

  avst_phrase_seq[] req_queue;                                    
  avst_phrase_seq[] rsp_queue;

  @UVM_BUILD {                                                   // BUILD PHASE : building the request (Excact) and repond (From DUT through monitor )analysis port 
    uvm_analysis_imp!(avst_scoreboard, write_req) req_analysis;
    uvm_analysis_imp!(avst_scoreboard, write_rsp) rsp_analysis;
  }

  override void run_phase(uvm_phase phase) {                      // RUN PHASE  
    phase_run = phase;
    auto imp = phase.get_imp();
    assert(imp !is null);
    uvm_wait_for_ever();
  }

  void write_req(avst_phrase_seq seq) {                           // Reciveing the sequence item from the monitor in the request side 
      uvm_info("Monitor", "Got req item", UVM_DEBUG);
      req_queue ~= seq;
      assert(phase_run !is null);
      phase_run.raise_objection(this);
      // writeln("Received request: ", matched + 1);
  }

  void write_rsp(avst_phrase_seq seq) {                          // Reciveing the sequence item from the monitor in the respond side (DUT)
      uvm_info("Monitor", "Got rsp item", UVM_DEBUG);
      // seq.print();
      rsp_queue ~= seq;
      assert(phase_run !is null);
      check_matched();                                           // The functions checks for matches 
      phase_run.drop_objection(this);
  }

  void check_matched() {                                         // Checking whether the exact and actaul value match 
    auto expected = req_queue[matched].transform();              // "transform" calcuate the extact value 
    // writeln("Ecpected: ", expected[0..64]);
    if (expected == rsp_queue[matched].phrase) {
      uvm_info("MATCHED",
	       format("Scoreboard received expected response #%d", matched),
	       UVM_LOW);
      uvm_info("REQUEST", format("%s", req_queue[$-1].phrase), UVM_LOW);
      uvm_info("RESPONSE", format("%s", rsp_queue[$-1].phrase), UVM_LOW);
    }
    else {
      uvm_error("MISMATCHED", "Scoreboard received unmatched response");
      writeln(expected, " != ", rsp_queue[matched].phrase);
    }
    matched += 1;
  }

}

class avst_monitor: uvm_monitor                                       // UVM Monitor Initialisation
{

  mixin uvm_component_utils;                                          // Factory Registration
  
  @UVM_BUILD {                                                        // BUILD PHASE : (Macro) Building :-
    uvm_analysis_port!avst_phrase_seq egress;                         // egress    with uvm_analysis_port as template class and avst_pharse_seq as argument class       
    uvm_analysis_imp!(avst_monitor, write) ingress;                   // ingress   with uvm_analysis_imp  as template class and avst_monitor as argument class & write as argument function    
  }


  this(string name, uvm_component parent = null) {                     // Constructor  
    super(name, parent);                                               // Base class construction
  }

  avst_phrase_seq seq;                                                 

  void write(avst_item item) {
    if (seq is null) {
      seq = avst_phrase_seq.type_id.create("avst_seq");
    }
    seq ~= item;
    if (seq.is_finalized()) {
      uvm_info("Monitor", "Got Seq " ~ seq.sprint(), UVM_DEBUG);
      egress.write(seq);
      seq = null;
    }
  }
  
}


class avst_sequencer: uvm_sequencer!avst_item                       // UVM Sequencer initialization  (extending base class uvm sequencer (template of avst_item ) to avst_sequnecer)
{
  mixin uvm_component_utils;

  this(string name, uvm_component parent=null) {
    super(name, parent);
  }
}

class avst_agent: uvm_agent                                         // UVM agent initialization : (Agent usually not consist of scoreboard)
{

  @UVM_BUILD {                                                     // BUILD PHASE : (Macro) Building :-
    avst_sequencer sequencer;                                      // Sequencer
    avst_driver    driver;                                         // Driver
    avst_out_driver driver_out;                                    // Driver_out

    avst_monitor   req_monitor;                                    // Request Monitor
    avst_monitor   rsp_monitor;                                    // Respond Monitor

    avst_snooper   rsp_snooper;                                    // Request Snooper
    avst_snooper   req_snooper;                                    // Respond Snooper

    avst_scoreboard   scoreboard;                                  // Scoreboard
  }
  
  mixin uvm_component_utils;
   
  this(string name, uvm_component parent = null) {
    super(name, parent);
  }

  override void connect_phase(uvm_phase phase) {                    // CONNECT PAHSE : Connection made using TLM
    driver.seq_item_port.connect(sequencer.seq_item_export);        // driver      .seq_item_port    to  sequencer   .seq_item_export
    req_snooper.egress.connect(req_monitor.ingress);                // req_snooper .egress           to  req_monitor .ingress
    req_monitor.egress.connect(scoreboard.req_analysis);            // req_monitor .egres            to  scoreboard  .req_analysis
    rsp_snooper.egress.connect(rsp_monitor.ingress);                // rsp_snooper .egress           to  rsp_monitor .ingress
    rsp_monitor.egress.connect(scoreboard.rsp_analysis);            // rsp_monitor .egress           to  scoreboard  .rsp_analysis 
  }

  override void end_of_elaboration_phase(uvm_phase phase) {         // Elaboration Phase ENDS (NEED more Insight) ? Does really required for other TBs
    rsp_snooper.set_read_latency(1);
  }
}

class random_test: uvm_test                                           // UVM test
{
  mixin uvm_component_utils;                                          // Registering in the Factory

  this(string name, uvm_component parent) {                           
    super(name, parent);
  }

  @UVM_BUILD {                                                        // BUILD PHASE : Building Enviornment (Macro) No need to overide (Its done automatically) 
    avst_env env;
  }
  
  override void run_phase(uvm_phase phase) {                          // RUN PHASE : The sequence item randomised and sent to the sequencer present in the agent after which the objection is dropped
    phase.get_objection().set_drain_time(this, 100.nsec);
    phase.raise_objection(this);
    auto rand_sequence = new avst_seq("avst_seq");

    for (size_t i=0; i!=100; ++i) {
      rand_sequence.randomize();
      auto sequence = cast(avst_seq) rand_sequence.clone();
      sequence.start(env.agent.sequencer, null);
    }
    phase.drop_objection(this);
  }
}

// class QuickFoxTest: uvm_test
// {
//   mixin uvm_component_utils;

//   this(string name, uvm_component parent) {
//     super(name, parent);
//   }

//   @UVM_BUILD avst_env env;
  
//   override void run_phase(uvm_phase phase) {
//     phase.raise_objection(this);
//     auto sequence = new avst_phrase_seq("QuickFoxSeq");
//     sequence.set_phrase("The quick brown fox jumps over the lazy dog");

//     sequence.start(env.agent.sequencer, null);
//     phase.drop_objection(this);
//   }
// }

class avst_env: uvm_env                                 // UVM Enviornment Initialisation
{
  mixin uvm_component_utils;                            // Registering the Env in the factory

  @UVM_BUILD private avst_agent agent;                  // BUILD PHASE : Building Agent  (Using Macro)

  this(string name, uvm_component parent) {             // Why ?          
    super(name, parent);
  }

}

class AvstIntf: VlInterface                             //  All the signal template required for the top level design are initialised in the class AvstIntf from V1Interface
{
  Port!(Signal!(ubvec!1)) clock;                        //  1-bit clock port template
  Port!(Signal!(ubvec!1)) reset;                        //  1-bit reset port template
  
  VlPort!8 data;                                        //  8-bit data  port template
  VlPort!1 end;                                         //  1-bit end   port template
  VlPort!1 valid;                                       //  1-bit valid port template
  VlPort!1 ready;                                       //  1-bit ready port template
}

class Top: Entity                                       // NOT A PART of EUVM. 
{
  import Vadder_avst_euvm;
  import esdl.intf.verilator.verilated;

  VerilatedVcdD _trace;                                 // intialising the trace 

  Signal!(ubvec!1) reset;                               // initialising 1-bit reset signal
  Signal!(ubvec!1) clock;                               // initialising 1-bit clock signal

  DVadder_avst dut;                                     // intialising DUT 

  AvstIntf avstIn;                                      // initialising input ports objects to the top module in DUT using the class AvstIntf   
  AvstIntf avstOut;                                     // initialising output ports objects to the top module in DUT using the class AvstIntf

  void opentrace(string vcdname) {                      // Function to  Open trace if  NULL
    if (_trace is null) {           
      _trace = new VerilatedVcdD();                     // Creating a VCD object and assigning it to the trace
      dut.trace(_trace, 99);                            // Attaching the DUT to the trace  (99 ?)
      _trace.open(vcdname);         
    }
  }

  void closetrace() {                                   // Function to Close trace if not NULL
    if (_trace !is null) {            
      _trace.close();           
      _trace = null;                                    // Assign trace back to NULL
    }           
  }           

  override void doConnect() {                           // Connecting the input and output ports of the TOP ----> signals of top module of DUT 
    import std.stdio;                                   //As TOP is not a part of UVM. There are no phases. ITs just doConnect

    //   INPUT SIGNALS 
    avstIn.clock(clock);
    avstIn.reset(reset);

    avstIn.data(dut.data_in);
    avstIn.end(dut.end_in);
    avstIn.valid(dut.valid_in);
    avstIn.ready(dut.ready_in);

    // OUTPUT SIGNALS
    avstOut.clock(clock);
    avstOut.reset(reset);

    avstOut.data(dut.data_out);
    avstOut.end(dut.end_out);
    avstOut.valid(dut.valid_out);
    avstOut.ready(dut.ready_out);
  }

  override void doBuild() {                     //  building DUT from DVadder_avst (As TOP is not a part of UVM. There are no phases. ITs just doBuild)
    dut = new DVadder_avst();                   //  Where is DVadder_avst ? Its present in Vadder_avst_evum.d
    traceEverOn(true);                          //  ?
    opentrace("avst_adder.vcd");
  }
  
  Task!stimulateClock stimulateClockTask;       // simulating clock parallely by implementing them as Task
  Task!stimulateReset stimulateResetTask;       // simulating reset parallely by implementing them as Task 
  Task!stimulateReadyOut stimulateReadyOutTask; // simulating reset parallely by implementing them as Task 

  void stimulateReadyOut() {                    // Calls when there are no more input to process. As the Reset will be high when there are no input to process 
    dut.reset = true;
  }
  
  void stimulateClock() {                       // Function to generate clock (1 million clock cycle, each = 10ns)
    import std.stdio;
    clock = false;
    for (size_t i=0; i!=1000000; ++i)
      {
	
      // writeln("clock is: ", clock);
        clock = false;
      dut.clk = false;
      wait (2.nsec);
      dut.eval();               // ?
      if (_trace !is null)
	_trace.dump(getSimTime().getVal());           // dump is verilator method used to signal values at the simulation time received by getSimTime().getVal
      wait (8.nsec);  
      clock = true;
      dut.clk = true;
      wait (2.nsec);
      dut.eval();
      if (_trace !is null) {
	_trace.dump(getSimTime().getVal());
	_trace.flush();                               // Ensures the waveform data is written immediately
      }
      wait (8.nsec);
    }
  }

  void stimulateReset() {                       // Function to generate Reset signal (True for 100ns, False for rest)
    reset = true;
    dut.reset = true;
    wait (100.nsec);
    reset = false;
    dut.reset = false;
  }
  
}

class uvm_sha3_tb: uvm_tb                       // config_db is used to make connections of UVM components (driver and snooper) with the DUT. Not a part of TLM 
{
  Top top;
  override void initial() {
    uvm_config_db!(AvstIntf).set(null, "uvm_test_top.env.agent.driver", "avst_in", top.avstIn);            
    uvm_config_db!(AvstIntf).set(null, "uvm_test_top.env.agent.driver_out", "avst_out", top.avstOut);  
    uvm_config_db!(AvstIntf).set(null, "uvm_test_top.env.agent.req_snooper", "avst", top.avstIn);      
    uvm_config_db!(AvstIntf).set(null, "uvm_test_top.env.agent.rsp_snooper", "avst", top.avstOut);       
  }
}

void main(string[] args) {
  import std.stdio;
  uint random_seed;

  CommandLine cmdl = new CommandLine(args);

  if (cmdl.plusArgs("random_seed=" ~ "%d", random_seed))   // ?
    writeln("Using random_seed: ", random_seed);
  else random_seed = 1;

  auto tb = new uvm_sha3_tb;
  tb.multicore(0, 1);         // multicore function allowing to distribute the task among different core. Not clear at this point. So better skip it.
  tb.elaborate("tb", args);   // Use in other TB as well
  tb.set_seed(random_seed);   // 
  tb.start();
  
}
