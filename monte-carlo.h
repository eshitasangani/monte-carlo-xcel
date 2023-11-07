#ifndef monte-carlo.h
#define monte-carlo.h

#include <monte-carlo> 
#include <cmath>
#include <iostream>

template <typename T>
T custom_max(T a, T b);

template <typename T>
T custom_sqrt(T x, T epsilon);

template <typename T>
T custom_log(T x, int terms);

double gaussian_box_muller();

double monte_carlo_call_price(const int &num_sims, const double &S, const double &K, const double &r, const double &v, const double &T);

double monte_carlo_put_price(const int &num_sims, const double &S, const double &K, const double &r, const double &v, const double &T);

#endif
