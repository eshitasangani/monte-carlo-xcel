#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the digitrec program
#
# @desc: 1. "make" or "make sw" runs software execution by default
#        2. "make fpga" invokes the HW accelerator
#        3. "make clean" cleans up the directory


INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH}

.PHONY: all sw fpga

all: sw

monte-carlo-arm: monte-carlo.cpp monte-carlo_test.cpp
	@echo "Compiling & executing monte-carlo software program on ARM ..."
	g++ ${CFLAGS} $^ -o $@

result/monte-carlo_arm_sim.txt: monte-carlo-arm
	mkdir -p result
	./$< | tee $@

sw: result/monte-carlo_arm_sim.txt
	@echo "Result saved to $@"

monte-carlo-fpga: host.cpp
	@echo "Compiling host program"
	g++ ${CFLAGS} $^ -o $@
	@echo "Make sure bitstream is loaded!"

fpga: monte-carlo-fpga
	@echo "Running monte carlo accelerator ..."
	./$<

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf monte-carlo-sw vivado_hls.log *.prj result out.dat *~
	rm -rf monte-carlo-fpga
