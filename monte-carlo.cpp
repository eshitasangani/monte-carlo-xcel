#include <iostream>
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
  theta_type call = monte_carlo_call_price(num_sims, S, K, r, v, T);
  theta_type put = monte_carlo_put_price(num_sims, S, K, r, v, T);

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

unsigned int seed = 0b101101;  // Initial seed
const int size = 6;  // LFSR size
const unsigned int feedbackMask = 0b101011;  // Feedback mask (adjust for desired behavior)

// Function to generate a random number in the range [0, 1)
theta_type generate_rand() {
    // Generate the next bit in the LFSR sequence
    bool nextBit = seed & 1;
    seed >>= 1;
    if (nextBit) {
        seed ^= feedbackMask;
    }
    // Convert the LFSR output to a random double in the range [0, 1)
    theta_type casted_seed = seed;
    theta_type casted_deno = (1U << size) - 1;
    return casted_seed/casted_deno;
}


// A simple implementation of the max
template <typename T>
T custom_max(T a, T b)
{
  return (b < a) ? a : b;
}
template <typename T>
T custom_abs(T x) {
    return (x < 0) ? -x : x;
}
template <typename T>
T custom_sqrt(T x, T epsilon) {
    if (x < 0) {
        return -1.0;
    }
    T guess = x;
    T nextGuess = 0.5 * (guess + x / guess);
    // key: 0 value: 152
    // key: 1 value: 65367
    // key: 2 value: 1319139
    // key: 3 value: 4814309
    // key: 4 value: 6109258
    // key: 5 value: 24183887
    // key: 6 value: 2107551
    // key: 7 value: 906203
    // key: 8 value: 341471
    // key: 9 value: 109410
    // key: 10 value: 31569
    // key: 11 value: 8540
    // key: 12 value: 2300
    // key: 13 value: 625
    // key: 14 value: 173
    // key: 15 value: 32
    // key: 16 value: 12
    // key: 17 value: 1
    // key: 19 value: 1
    while (custom_abs<T>(guess - nextGuess) >= epsilon) {
        guess = nextGuess;
        nextGuess = 0.5 * (guess + x / guess);
    }

    return nextGuess;
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
  theta_type epsilon = 0.00001;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity
  do
  {
    x = 2.0 * generate_rand() - 1;
    y = 2.0 * generate_rand() - 1;
    euclid_sq = x * x + y * y;
  } while (euclid_sq >= 1.0);

  return x * custom_sqrt<theta_type>(-2 * custom_log<theta_type>(euclid_sq) / euclid_sq, epsilon);
}

// Pricing a European vanilla call option with a Monte Carlo method
theta_type monte_carlo_call_price(const int &num_sims, const theta_type &S, const theta_type &K, const theta_type &r, const theta_type &v, const theta_type &T)
{
  theta_type S_adjust = S * custom_exp<theta_type>(T * (r - 0.5 * v * v));
  theta_type S_cur = 0.0;
  theta_type payoff_sum = 0.0;
  theta_type epsilon = 0.0001;

  for (int i = 0; i < num_sims; i++)
  {
    theta_type gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * custom_exp<theta_type>(custom_sqrt<theta_type>(v * v * T, epsilon) * gauss_bm);
    payoff_sum += custom_max<theta_type>(S_cur - K, 0.0);
  }
  theta_type cast_num_sims = num_sims;
  return (payoff_sum / cast_num_sims) * custom_exp<theta_type>(-r * T);
}

// Pricing a European vanilla put option with a Monte Carlo method
theta_type monte_carlo_put_price(const int &num_sims, const theta_type &S, const theta_type &K, const theta_type &r, const theta_type &v, const theta_type &T)
{
  theta_type S_adjust = S * custom_exp<theta_type>(T * (r - 0.5 * v * v));
  theta_type S_cur = 0.0;
  theta_type payoff_sum = 0.0;
  theta_type epsilon = 0.0001;

  for (int i = 0; i < num_sims; i++)
  {
    theta_type gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * custom_exp<theta_type>(custom_sqrt<theta_type>(v * v * T, epsilon) * gauss_bm);
    payoff_sum += custom_max<theta_type>(K - S_cur, 0.0);
  }

  theta_type cast_num_sims = num_sims;
  return (payoff_sum / cast_num_sims) * custom_exp<theta_type>(-r * T);
}