#include <iostream>
#include <cmath>
#include "monte-carlo.h"

typedef double theta_type;

void dut(hls::stream<bit32_t> &strm_out) {
  // First we create the parameter list
  int num_sims = 10000000; // Number of simulated asset paths
  theta_type S = 100.0;    // Option price
  theta_type K = 100.0;    // Strike price
  theta_type r = 0.05;     // Risk-free rate (5%)
  theta_type v = 0.2;      // Volatility of the underlying (20%)
  theta_type T = 1.0;      // One year until expiry

  // Then we calculate the call/put values via Monte Carlo
  result_type result;
  monte_carlo_both_price(result, num_sims, S, K, r, v, T);
  theta_type call = result.call;
  theta_type put = result.put;

  // Write the output to the stream
  strm_out.write(num_sims);
  strm_out.write(S);
  strm_out.write(K);
  strm_out.write(r);
  strm_out.write(v);
  strm_out.write(T);
  strm_out.write(call);
  strm_out.write(put);
}

int seed = 1;  // Initial seed
const int size = 6;  // LFSR size
const unsigned int feedbackMask = 0b101011;  // Feedback mask (adjust for desired behavior)

// Function to generate a random number in the range [0, 1)
theta_type generate_rand() {
    // Generate the next bit in the LFSR sequence
    seed = 1103515245 * seed + 12345; // assume 2^32 wraparound
    theta_type casted_seed = seed;
    theta_type rand_max = RAND_MAX;
    return 2.0* casted_seed/rand_max - 1;
}

template <typename T>
T custom_log(T x)
{
  if (x <= 0)
  {
    std::cerr << "Error: Input must be greater than 0" << std::endl;
    return -1.0; // Error value
  }
  
  const int logTerms = 10;

  T result = 0.0;
  T term = (x - 1) / (x + 1);
  T term_squared = term * term;
  T numerator = term;
  T denominator = 1;

  for (int i = 1; i <= logTerms; i++)
  {
    result += numerator / denominator;
    numerator *= term_squared;
    denominator += 2;
  }

  return 2 * result;
}

template <typename T>
T custom_exp(T x)
{
  T result = 1.0;
  T term = 1.0;
  T factorial = 1.0;
  const int expTerms = 10;

  for (int i = 1; i <= expTerms; i++)
  {
    term *= x / i;
    result += term;
  }

  return result;
}

// box muller algorithm
theta_type gaussian_box_muller()
{
  theta_type x = 0.0;
  theta_type y = 0.0;
  theta_type euclid_sq = 0.0;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity
  do
  {
    x = generate_rand();
    y = generate_rand();
    euclid_sq = x * x + y * y;
  } while (euclid_sq >= 1.0);

  return x * sqrt(-2 * custom_log<theta_type>(euclid_sq) / euclid_sq);
}

// Pricing a European vanilla option with a Monte Carlo method
void monte_carlo_both_price(result_type &result, const int &num_sims, const theta_type &S, const theta_type &K, const theta_type &r, const theta_type &v, const theta_type &T)
{
  theta_type S_adjust = S * custom_exp<theta_type>(T * (r - 0.5 * v * v));
  theta_type S_cur = 0.0;
  theta_type call_payoff_sum = 0.0;
  theta_type put_payoff_sum = 0.0;

  for (int i = 0; i < num_sims; i++)
  {
    theta_type gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * custom_exp<theta_type>(sqrt(v * v * T) * gauss_bm);
    call_payoff_sum += fmax(S_cur - K, 0.0);
    put_payoff_sum += fmax(K - S_cur, 0.0);
  }
  theta_type cast_num_sims = num_sims;
  theta_type call = (call_payoff_sum / cast_num_sims) * custom_exp<theta_type>(-r * T);
  theta_type put = (put_payoff_sum / cast_num_sims) * custom_exp<theta_type>(-r * T);

  result.call = call;
  result.put = put;
}