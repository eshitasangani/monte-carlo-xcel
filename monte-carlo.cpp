#include <iostream>
#include "hls_math.h"
#include "monte-carlo.h"

void dut(hls::stream<bit32_t> &strm_out) {
  // First we create the parameter list hard coded in h file

  // Then we calculate the call/put values via Monte Carlo
  result_type result;
  monte_carlo_both_price(result);
  theta_type call = result.call;
  theta_type put = result.put;

  // Write the output to the stream
  // strm_out.write(num_sims);
  // strm_out.write(S);
  // strm_out.write(K);
  // strm_out.write(r);
  // strm_out.write(v);
  // strm_out.write(T);
  strm_out.write(call);
  strm_out.write(put);
}

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

const theta_type rand_max_div_two = 0.000000000931322575049159384821150165433599690642952774950746807712478007;
// Function to generate a random number in the range [0, 1)
theta_type generate_rand1() {
    theta_type casted_seed = pseudo_random(lfsr1);
    return rand_max_div_two * casted_seed - 1.0f;
}
// Function to generate a random number in the range [0, 1)
theta_type generate_rand2() {
    theta_type casted_seed = pseudo_random(lfsr2);
    return rand_max_div_two * casted_seed - 1.0f;
}

// box muller algorithm
theta_type gaussian_box_muller()
{
  theta_type x = 0.45543f;
  theta_type y = -0.337388f;
  theta_type euclid_sq = 0.353308f;
  
  theta_type euclid_sq_temp = 0.0f;
  theta_type epsilon = 0.00001f;
  theta_type temp_x = 0.0f;
  theta_type temp_y = 0.0f;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity

  GAUSS_LABEL:
  for (int i = 0; i < 20; i++) {
    temp_x = generate_rand1();
    temp_y = generate_rand2();
    euclid_sq_temp = temp_x * temp_x + temp_y * temp_y;
    if (euclid_sq_temp < 1.0f) {
      euclid_sq = euclid_sq_temp;
      x = temp_x;
      y = temp_y;
    }
  }
  
  return x * hls::sqrt(-2.0f * hls::log(euclid_sq) / euclid_sq);
}

// Pricing a European vanilla option with a Monte Carlo method
void monte_carlo_both_price(result_type &result)
{
  const theta_type S_adjust = S * hls::exp(T * (r - 0.5f * v * v));
  const theta_type K_adjust = K/S_adjust;
  const theta_type sqrt_const = hls::sqrt(v * v * T);
  theta_type S_cur = 0.0;
  
  constexpr int FADD_LAT = 8;
  constexpr int MOD = FADD_LAT - 1;
  theta_type call_payoff_sum_arr[FADD_LAT];
  theta_type put_payoff_sum_arr[FADD_LAT];
  theta_type call_payoff_sum = 0.0f;
  theta_type put_payoff_sum = 0.0f;

  LOOP_INIT:
  for (int i =0 ; i< FADD_LAT; i++){
    call_payoff_sum_arr[i] = 0.0f;
    put_payoff_sum_arr[i] = 0.0f;
  }


  GAUSS_GEN_LABEL:
  for (int i = 0; i < num_sims; i++) {
    theta_type gauss_bm = gaussian_box_muller();
    theta_type S_cur = hls::exp(sqrt_const * gauss_bm);
    call_payoff_sum_arr[i & MOD] += hls::fmax(S_cur - K_adjust, 0.0f);
    put_payoff_sum_arr[i & MOD] += hls::fmax(K_adjust - S_cur, 0.0f);
  }

  FINAL:
  for (int k = 0; k < FADD_LAT;k++){
    call_payoff_sum +=  call_payoff_sum_arr[k];
    put_payoff_sum += put_payoff_sum_arr[k];
  }

  theta_type cast_num_sims = num_sims;
  theta_type call = S_adjust * (call_payoff_sum / cast_num_sims) * hls::exp(-r * T);
  theta_type put = S_adjust * (put_payoff_sum / cast_num_sims) * hls::exp(-r * T);

  result.call = call;
  result.put = put;
}