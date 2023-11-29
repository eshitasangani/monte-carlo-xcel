#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include "typedefs.h"

//------------------------------------------------------------------------
// Helper function for hex to int conversion
//------------------------------------------------------------------------
int64_t hexstring_to_int64(std::string h) {
  int64_t x = 0;
  for (int i = 0; i < h.length(); ++i) {
    char c = h[i];
    int k = (c > '9') ? toupper(c) - 'A' + 10 : c - '0';
    x = x * 16 + k;
  }
  return x;
}

//------------------------------------------------------------------------
// RAND FUNCTIONS 
//------------------------------------------------------------------------
ap_uint<32> lfsr1 = 0xdcba;  // Initial seed
ap_uint<32> lfsr2 = 1234;  // Initial seed

unsigned int pseudo_random(ap_uint<32>& lfsr) {
bool b_32 = lfsr.get_bit(32-32);
bool b_22 = lfsr.get_bit(32-22);
bool b_2 = lfsr.get_bit(32-2);
bool b_1 = lfsr.get_bit(32-1);
bool new_bit = b_32 ^ b_22 ^ b_2 ^ b_1;
lfsr = lfsr >> 1;
lfsr.set_bit(31, new_bit);
return lfsr.to_uint();
}

constexpr theta_type rand_two_div_max = 2.0 / RAND_MAX;
// Function to generate a random number in the range [0, 1)
theta_type generate_rand1() {
    theta_type casted_seed = pseudo_random(lfsr1);
    // theta_type casted_seed = gcc_rand(seed1);
    return rand_two_div_max * casted_seed - 1;
}
// Function to generate a random number in the range [0, 1)
theta_type generate_rand2() {
    theta_type casted_seed = pseudo_random(lfsr2);
    // theta_type casted_seed = gcc_rand(seed2);
    return rand_two_div_max * casted_seed - 1;
}

//------------------------------------------------------------------------
// VARIABLES USED 
//------------------------------------------------------------------------
constexpr int num_sims = 1000000;      // Number of simulated asset paths
constexpr theta_type S = 100.0;        // Option price
constexpr theta_type K = 100.0;        // Strike price
constexpr theta_type r = 0.05;         // Risk-free rate (5%)
constexpr theta_type v = 0.2;          // Volatility of the underlying (20%)
constexpr theta_type T = 1.0;          // One year until expiry

constexpr theta_type expected_call_value = 10.1341/* your expected call value */;
constexpr theta_type expected_put_value = 5.43944/* your expected put value */;
int num_test_insts = 0;
const int num_simulations = 1000000;
int nbytes;
int error = 0;

theta_type params[5] = {1000000, 100.0, 100.0, 0.05, 0.2, 1.0}

//--------------------------------------
// main function
//--------------------------------------
int main(int argc, char **argv) {
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0)) {
    fprintf(stderr, "Failed to open Xillybus device channels\n");
    return -1;
  }

  // Timer
  Timer timer("monte-carlo FPGA");
 
  // Arrays to store test data and expected results
  result_type results;

  timer.start();

  //--------------------------------------------------------------------
  // send all values to the module
  //--------------------------------------------------------------------
  for (int i = 0; i < params; ++i) {
    bit64_t input_in;
    input_in(63, 0) = static_cast<bit64_t>(5); 
    nbytes = write(fdw, (void *)&input_in, sizeof(input_in));
  }
  
  //--------------------------------------------------------------------
  // read all results
  //--------------------------------------------------------------------
  nbytes = read(fdr, (void *)&results, sizeof(result_type));
  if (results.call != expected_call_value || results.put != expected_put_value) {
    error++;
  }

  timer.stop();

  // Report overall error out of all testing instances
  std::cout << "Expected Call Value = " << results.call << std::endl;
  std::cout << "Expected Put Value = " << results.put << std::endl;

  return 0;
}