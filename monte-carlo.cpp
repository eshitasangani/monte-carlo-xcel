#include <iostream>
typedef double theta_type;
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

    while (custom_abs<T>(guess - nextGuess) >= epsilon) {
        guess = nextGuess;
        nextGuess = 0.5 * (guess + x / guess);
    }

    return nextGuess;
}

template <typename T>
T custom_log(T x, int terms)
{
  if (x <= 0)
  {
    std::cerr << "Error: Input must be greater than 0" << std::endl;
    return -1.0; // Error value
  }

  T result = 0.0;
  T term = (x - 1) / (x + 1);
  T term_squared = term * term;
  T numerator = term;
  T denominator = 1;

  for (int i = 1; i <= terms; i++)
  {
    result += numerator / denominator;
    numerator *= term_squared;
    denominator += 2;
  }

  return 2 * result;
}

template <typename T>
T custom_exp(T x, int terms = 10)
{
  T result = 1.0;
  T term = 1.0;
  T factorial = 1.0;

  for (int i = 1; i <= terms; i++)
  {
    term *= x / i;
    result += term;
  }

  return result;
}

// A simple implementation of the Box-Muller algorithm, used to generate
// gaussian random numbers - necessary for the Monte Carlo method below
// Note that C++11 actually provides std::normal_distribution<> in
// the <random> library, which can be used instead of this function
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
    theta_type randMax = RAND_MAX;
    x = 2.0 * rand() / randMax - 1;
    y = 2.0 * rand() / randMax - 1;
    euclid_sq = x * x + y * y;
  } while (euclid_sq >= 1.0);

  return x * custom_sqrt<theta_type>(-2 * custom_log<theta_type>(euclid_sq, 10) / euclid_sq, epsilon);
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

int main(int argc, char **argv)
{
  // First we create the parameter list
  int num_sims = 10000000; // Number of simulated asset paths
  theta_type S = 100.0;        // Option price
  theta_type K = 100.0;        // Strike price
  theta_type r = 0.05;         // Risk-free rate (5%)
  theta_type v = 0.2;          // Volatility of the underlying (20%)
  theta_type T = 1.0;          // One year until expiry

  // Then we calculate the call/put values via Monte Carlo
  theta_type call = monte_carlo_call_price(num_sims, S, K, r, v, T);
  theta_type put = monte_carlo_put_price(num_sims, S, K, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Call Price:      " << call << std::endl;
  std::cout << "Put Price:       " << put << std::endl;

  return 0;
}