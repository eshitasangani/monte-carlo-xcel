#pragma once

#ifndef MONTE_H
#define MONTE_H

#include <cmath>
#include <iostream>

#include "typedefs.h"
#include <hls_stream.h>

typedef struct result_type result_type;

typedef float theta_type;

// int num_sims = 1000000;      // Number of simulated asset paths
// theta_type S = 100.0;        // Option price
// theta_type K = 100.0;        // Strike price
// theta_type r = 0.05;         // Risk-free rate (5%)
// theta_type v = 0.2;          // Volatility of the underlying (20%)
// theta_type T = 1.0;          // One year until expiry

extern int num_sims;
extern theta_type S, K, r, v, T;


void dut(hls::stream<bit32_t> &strm_out);

theta_type generate_rand();

theta_type gaussian_box_muller();

void monte_carlo_both_price(result_type &result);

struct result_type {
theta_type call; 
theta_type put;
};


#endif // MONTE_H
