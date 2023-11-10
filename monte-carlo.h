#pragma once

#include <cmath>
#include <iostream>

#include "typedefs.h"
#include <hls_stream.h>

typedef struct result_type result_type;

typedef double theta_type;

void dut(hls::stream<bit32_t> &strm_out);

template <typename T>
T custom_max(T a, T b);

template <typename T>
T custom_abs(T x);

template <typename T>
T custom_sqrt(T x, T epsilon);

template <typename T>
T custom_log(T x);

template <typename T>
T custom_exp(T x);

theta_type generate_rand();

theta_type gaussian_box_muller();

void monte_carlo_both_price(result_type &result, const int &num_sims, const theta_type &S, const theta_type &K, const theta_type &r, const theta_type &v, const theta_type &T);

struct result_type {
theta_type call;
theta_type put;
};