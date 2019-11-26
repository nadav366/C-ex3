#include "infi.h"
#include <assert.h>

/**    Minimum legal value       */
const unsigned int MIN_VAL = 0;

/**    Count variable initialization value       */
const int EMPTY = 0;

/**
 * @brief  Computes the numerical integration for the given rationale function
 *          at the given numbers range, based on Riemann sums.
 * @param func The function for which you want to do the integral
 * @param start The initial value of the integration domain
 * @param end The integration value end value
 * @param parts The number of parts they want to divide
 * @return The integration result.
 */
double integration(RealFunction func, double start, double end, unsigned int parts)
{
    assert(parts > MIN_VAL);
    assert(start < end);
    const double delta = (end - start) / parts;
    double cur = start + (delta / 2);
    double sum = EMPTY;
    for (unsigned int i = EMPTY; i < parts; ++i)
    {
        assert(!isnan(func(cur)));
        sum += func(cur) * delta;
        cur += delta;
    }
    return sum;
}

/**
 * @brief  Computes a numerical derivative for the given rationale function
 *          at the point, for a given epsilon.
 * @param func The function you want to make a derivative to it
 * @param x_0 Derivative evaluation point
 * @param h
 * @return Epsilon, the approximation level derived
 */
double derivative(RealFunction func, double x_0, double h)
{
    assert(h > MIN_VAL);
    assert(!isnan(func(x_0 + h)));
    assert(!isnan(func(x_0 - h)));
    return (func(x_0 + h) - func(x_0 - h)) / (2 * h);
}
