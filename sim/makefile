CC              = gcc
CFLAGS		= -Wall -O3 -fPIC
SEED            = 1

DFLAGS = -relocation-model=pic -w

LDC2BINDIR = $(dir $(shell which ldc2))
VLBINDIR = $(dir $(shell which verilator))
VERBOSITY = DEBUG

VLATOR_SRC = euvm_dir/Vadder_avst_euvm.d euvm_dir/Vadder_avst_euvm_funcs.cpp obj_dir/Vadder_avst.cpp obj_dir/Vadder_avst.h

all: avst_adder

clean:
	rm -rf avst_adder* euvm_dir obj_dir verilator.stamp

run: avst_adder
	./avst_adder +UVM_TESTNAME=adder_avst.random_test +UVM_VERBOSITY=$(VERBOSITY) +random_seed=$(SEED) # +UVM_OBJECTION_TRACE

verilator.stamp: ../rtl/adder_avst.v
	touch verilator.stamp
	verilator --threads 1 --trace --cc --euvm $^
	(cd euvm_dir; g++ -c -I ../obj_dir/ -I $(VLBINDIR)/../share/verilator/include Vadder_avst_euvm_funcs.cpp)
	(cd euvm_dir; g++ -c -I ../obj_dir/ -I $(VLBINDIR)/../share/verilator/include $(LDC2BINDIR)/../import/esdl/intf/verilator/cpp/verilated_vcd_d.cpp -o verilated_vcd_d.o)
	(cd euvm_dir; g++ -c -I ../obj_dir/ -I $(VLBINDIR)/../share/verilator/include $(LDC2BINDIR)/../import/esdl/intf/verilator/cpp/verilated_d.cpp -o verilated_d.o)
	(cd obj_dir; make -f Vadder_avst.mk Vadder_avst__ALL.a verilated.o verilated_vcd_c.o verilated_threads.o)

euvm_dir/Vadder_avst_euvm.d euvm_dir/Vadder_avst_euvm_funcs.o euvm_dir/verilated_vcd_d.o obj_dir/Vadder_avst__ALL.a obj_dir/verilated.o: verilator.stamp


avst_adder: ../testbench/adder_avst.d euvm_dir/Vadder_avst_euvm.d  \
	   $(LDC2BINDIR)/../import/esdl/intf/verilator/trace.d \
	   euvm_dir/verilated_vcd_d.o euvm_dir/verilated_d.o \
	   euvm_dir/Vadder_avst_euvm_funcs.o  \
	   obj_dir/Vadder_avst__ALL.a \
	   obj_dir/verilated.o  obj_dir/verilated_threads.o obj_dir/verilated_vcd_c.o \
	   obj_dir/verilated_threads.o
	ldc2 $(DFLAGS) -Ieuvm_dir -link-defaultlib-shared -of$@ -L-luvm-ldc-shared -L-lesdl-ldc-shared -L-lz3 \
		-L-lphobos2-ldc-shared -L-ldl $^ -L-lstdc++



