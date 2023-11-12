#pragma once

#include <cmath>
#include <iostream>

#include "typedefs.h"
#include <hls_stream.h>

typedef struct result_type result_type;

typedef float theta_type;

const int num_sims = 1000000;      // Number of simulated asset paths
const theta_type S = 100.0;        // Option price
const theta_type K = 100.0;        // Strike price
const theta_type r = 0.05;         // Risk-free rate (5%)
const theta_type v = 0.2;          // Volatility of the underlying (20%)
const theta_type T = 1.0;          // One year until expiry

void dut(hls::stream<bit32_t> &strm_out);

theta_type generate_rand();

theta_type gaussian_box_muller();

void monte_carlo_both_price(result_type &result);

struct result_type {
theta_type call;
theta_type put;
};