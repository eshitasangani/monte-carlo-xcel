//=========================================================================
// monte-carlo_test.cpp
//=========================================================================
// @brief: testbench for Monte Carlo Xcel

#include <iostream>
#include <cmath>

#include "monte-carlo.h"

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