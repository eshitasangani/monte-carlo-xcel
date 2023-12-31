#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the monte-carlo design.

# Project name
set hls_prj monte-carlo.prj

# Open/reset the project
open_project ${hls_prj} -reset

# Top function of the design is "dut"
set_top dut

# Add design and testbench files
add_files monte-carlo.cpp -cflags "-std=c++11"
add_files -tb monte-carlo_test.cpp -cflags "-std=c++11"
# add_files -tb data

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

### You can insert your own directives here ###
set_directive_inline generate_rand1
set_directive_inline generate_rand2
set_directive_inline pseudo_random
set_directive_inline gaussian_box_muller

set_directive_pipeline gaussian_box_muller/GAUSS_LABEL
set_directive_pipeline gaussian_box_muller/GAUSS_LABEL_ONE
set_directive_pipeline gaussian_box_muller/GAUSS_LABEL_TWO
set_directive_pipeline monte_carlo_both_price/GAUSS_GEN_LABEL
set_directive_pipeline monte_carlo_both_price/OVERALL_LOOP
set_directive_unroll custom_exp/EXP_LABEL


############################################

# Simulate the C++ design
csim_design -O
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design
exit
