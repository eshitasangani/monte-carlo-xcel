#pragma once

#include <cmath>
#include <iostream>

#include "typedefs.h"
#include <hls_stream.h>

typedef struct result_type result_type;

typedef float theta_type;

constexpr int num_sims = 1000000;      // Number of simulated asset paths
constexpr theta_type S = 100.0f;        // Option price
constexpr theta_type K = 100.0f;        // Strike price
constexpr theta_type r = 0.05f;         // Risk-free rate (5%)
constexpr theta_type v = 0.2f;          // Volatility of the underlying (20%)
constexpr theta_type T = 1.0f;          // One year until expire
void dut(hls::stream<bit32_t> &strm_out);

theta_type generate_rand();

theta_type gaussian_box_muller();

void monte_carlo_both_price(result_type &result);

struct result_type {
theta_type call;
theta_type put;
};