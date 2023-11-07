#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and synthesizes the bnn program
#
# @desc: 1. "make" runs csim by default
#        2. "make csim" compiles & executes the software implementation
#        3. "make clean" cleans up the directory

# Extract Vivado HLS include path
XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
VHLS_INC=$(XILINX_VIVADO)/include
# Specify compilation flags
CFLAGS=-g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB -std=c++11 

TCL_SCRIPT=run.tcl

.PHONY: all csim bitstream clean

all: csim

monte-carlo: monte-carlo.cpp monte-carlo_test.cpp
	g++ ${CFLAGS} $^ -o $@ -lrt

result/monte-carlo.txt: monte-carlo
	@echo "Running monte carlo sim..."
	mkdir -p result
	./$< | tee $@

sw: 
	make clean; make; vivado_hls -f run.tcl

csim: result/monte-carlo.txt
	@echo "Result recorded to $<"

xillydemo.bit:
	@echo "=====================================================================" 
	@echo "Synthesizing Monte Carlo and creating bitstream with $(TCL_SCRIPT)..."
	@echo "=====================================================================" 
	$(XIL_HLS) -f $(TCL_SCRIPT)
	source $(XILINX_VIVADO)/settings64.sh; ./run_bitstream.sh

bitstream: xillydemo.bit
	@echo "Bitstream saved to $<"

clean:
	rm -rf monte-carlo *.dat *.prj *.log
	rm -rf zedboard_project* xillydemo.bit
