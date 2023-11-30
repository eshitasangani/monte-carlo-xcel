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

int nbytes;
int error = 0;

theta_type params[5] = {num_sims, S, K, r, v, T}

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
  result_type result;

  timer.start();

  //--------------------------------------------------------------------
  // send all values to the module
  //--------------------------------------------------------------------

  for (int i = 0; i < PARAM_SIZE; ++i) {
    bit64_t input_in;
    input_in = params[i]
    nbytes = write(fdw, (void *)&input_in, sizeof(input_in));
    assert(nbytes == sizeof(input_in));

  }
  
  
  //--------------------------------------------------------------------
  // read all results
  //--------------------------------------------------------------------

  nbytes = read(fdr, (void *)&result.call, sizeof(result.call));
  if (result.call != expected_call_value ) {
    error++;
  }

  timer.stop();

  // Report overall error out of all testing instances
  std::cout << "Expected Call Value = " << result.call << std::endl;
  std::cout << "Expected Put Value = " << result.put << std::endl;

  return 0;
}