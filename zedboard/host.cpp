#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>
#include "typedefs.h"
#include "timer.h"
#include "monte-carlo.h"

theta_type params[6] = {num_sims, S, K, r, v, T};

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

  int nbytes;
  int error = 0;

  // Timer
  Timer timer("monte-carlo FPGA");

  timer.start();

  //--------------------------------------------------------------------
  // send all values to the module
  //--------------------------------------------------------------------

  for (int i = 0; i < 6; ++i) {
    theta_type input_in;
    input_in = params[i];
// try converting the float to uint32
    streamVal convert;
    convert.fl = input_in;
    nbytes = write(fdw, (void *)&convert.u32, sizeof(convert.u32));
    assert(nbytes == sizeof(convert.u32));
  }

  //--------------------------------------------------------------------
  // read all results
  //--------------------------------------------------------------------

    int icall, iput;

    // read call price 
    nbytes = read (fdr, (void*)&icall, sizeof(int));
    assert (nbytes == sizeof(icall));

    // read put price
    nbytes = read (fdr, (void*)&iput, sizeof(int));
    assert (nbytes == sizeof(iput));
    streamVal callConvert, putConvert;
    callConvert.u32 = icall;
    putConvert.u32 = iput;
    float fcall = callConvert.fl;
    float fput = putConvert.fl;
    //float fcall = icall;
    //float fput = iput;

  timer.stop();


  // Print out price
  std::cout << "Expected Call Value = " << fcall << std::endl;
  std::cout << "Expected Put Value = " << fput << std::endl;

  close(fdr);
  close(fdw);

  return 0;
} 
