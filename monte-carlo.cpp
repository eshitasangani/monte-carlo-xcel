#include <algorithm> // Needed for the "max" function
#include <cmath>
#include <iostream>

// Function to generate a random number in the range [0, 1)
double generateRandomNumber(unsigned int& seed, int size, unsigned int feedbackMask) {
    // Generate the next bit in the LFSR sequence
    bool nextBit = seed & 1;
    seed >>= 1;
    if (nextBit) {
        seed ^= feedbackMask;
    }

    // Convert the LFSR output to a random number in the range [0, 1)
    return static_cast<double>(seed) / ((1U << size) - 1);
}

// A simple implementation of the max
template <typename T>
T custom_max(T a, T b)
{
  return (b < a) ? a : b;
}

template <typename T>
T custom_sqrt(T x, T epsilon)
{
  T guess = x;
  while ((guess * guess - x) > epsilon)
  {
    guess = 0.5 * (guess + x / guess);
  }
  return guess;
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
  int denominator = 1;

  for (int i = 1; i <= terms; i++)
  {
    result += numerator / denominator;
    numerator *= term_squared;
    denominator += 2;
  }

  return 2 * result;
}

// A simple implementation of the Box-Muller algorithm, used to generate
// gaussian random numbers - necessary for the Monte Carlo method below
// Note that C++11 actually provides std::normal_distribution<> in
// the <random> library, which can be used instead of this function
double gaussian_box_muller()
{
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;
  double epsilon = 0.00001;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity
  do
  {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
    euclid_sq = x * x + y * y;
  } while (euclid_sq >= 1.0);

  return x * custom_sqrt(-2 * custom_log(euclid_sq, 10) / euclid_sq, epsilon);
}

// Pricing a European vanilla call option with a Monte Carlo method
double monte_carlo_call_price(const int &num_sims, const double &S, const double &K, const double &r, const double &v, const double &T)
{
  double S_adjust = S * exp(T * (r - 0.5 * v * v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i = 0; i < num_sims; i++)
  {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v * v * T) * gauss_bm);
    payoff_sum += custom_max<double>(S_cur - K, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
}

// Pricing a European vanilla put option with a Monte Carlo method
double monte_carlo_put_price(const int &num_sims, const double &S, const double &K, const double &r, const double &v, const double &T)
{
  double S_adjust = S * exp(T * (r - 0.5 * v * v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i = 0; i < num_sims; i++)
  {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v * v * T) * gauss_bm);
    payoff_sum += custom_max<double>(K - S_cur, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r * T);
}

int main(int argc, char **argv)
{
  // First we create the parameter list
  int num_sims = 10000000; // Number of simulated asset paths
  double S = 100.0;        // Option price
  double K = 100.0;        // Strike price
  double r = 0.05;         // Risk-free rate (5%)
  double v = 0.2;          // Volatility of the underlying (20%)
  double T = 1.0;          // One year until expiry

  // Then we calculate the call/put values via Monte Carlo
  double call = monte_carlo_call_price(num_sims, S, K, r, v, T);
  double put = monte_carlo_put_price(num_sims, S, K, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Call Price:      " << call << std::endl;
  std::cout << "Put Price:       " << put << std::endl;

   unsigned int seed = 0b101101;  // Initial seed
    int size = 6;  // LFSR size
    unsigned int feedbackMask = 0b100101;  // Feedback mask (adjust for desired behavior)

    for (int i = 0; i < 10; i++) {
        double randomNumber = generateRandomNumber(seed, size, feedbackMask);
        std::cout << randomNumber << " ";
    }

    std::cout << std::endl;

  return 0;
}