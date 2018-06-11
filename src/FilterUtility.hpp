/* Copyright 2018 Ian Rankin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

// FilterUtility.hpp
// Written Ian Rankin - June 2018
//
// Depends:
// FilterUtility.h
//
// This is utility functions for various filter designs.
// The implementation file.
//
// [1] TODO

#ifndef __FILTER_UTILITY_IMP__
#define __FILTER_UTILITY_IMP__

#include <cmath>
#include <cstdint>

// applyHammingWindow
// This function applies a hamming window to an arbituary input
// @param input - the input array to apply a hamming window to.
// @param length - the length of the input array.
// NOTE: The length must be odd.
//
// @return - 0 for success, else failure.
template <class T>
int applyHammingWindow(T *input, uint16_t N)
{
    for (uint16_t n = 0; n < N; n++)
    {
        double w = 0.54 - (0.46 * cos(2 * M_PI * n / (N - 1)));
        input[n] = (T)((double)input[n] * w);
    } // end for loop

    return 0;
} // end applyHammingWindow


// applyKaiserWindow
// This function applies a kaiser window to an arbituary input
// @param input - the input array to apply a hamming window to.
// @param length - the length of the input array.
// @param A - stopband attenuation required in dB
// NOTE: The length must be odd.
//
// @return - 0 for success, else failure.
template <class T>
int applyKaiserWindow(T *input, uint16_t N, double A)
{
    double alpha;
    if (A >= 50.0) {
        alpha = 0.1102 * (A - 8.7);
    } else if (A > 21.0) {
        double lhs = 0.5842 * pow(A-21, 0.4);
        alpha = lhs + (0.07886 * (A - 21));
    } else {
        alpha = 0;
    }

    double denominator = besselFunc(alpha);
    double M = (double)((int)(N / 2));

    for (uint16_t n = 0; n < N; n++)
    {
        double w = besselFunc(alpha *
            sqrt(1.0 - ((n - M) * (n - M) / (M * M))))
            / denominator;
        std::cout << "w = " << w << std::endl;
        input[n] = (T)((double)input[n] * w);
    } // end for loop

    return 0;
} // end applyKaiserWindow



// idealFilterCoef
// this function returns N gains from an ideal low pass filter.
// This is equivilent to a rectangular window.
// NOTE: the length must be odd.
// @param omegaCutoff - the cutoff frequency of the filter.
// @param N - the length of the filter.
// @param isHighPassFilter - says which filter type to compute, 0 for lowpass,
//           1 for high pass filter.
//
// @return - the filter coefficients given as an array.
template <class T>
T *idealFilterCoef(double omegaCutoff, uint16_t N, bool isHighPassFilter)
{
    uint16_t M = N / 2; // returns the center index of the filter.
    if (N % 2 == 0) { return NULL; }
    // init the gains
    T *gains = new T[N];

    for (int16_t k = 0; k < N; k++)
    {
        double w;
        if (isHighPassFilter) {
            // define coefficients for high pass filter.
            if (k == M) { w = 1.0 - (omegaCutoff / M_PI); }
            else { w = -sin(omegaCutoff * (k - M)) / (M_PI * (k - M)); }
        } else {
            // define coefficients for low pass filter.
            if (k == M) { w = omegaCutoff / M_PI; }
            else { w = sin(omegaCutoff * (k - M)) / (M_PI * (k - M)); }
        } // end if else for high pass filtering

        gains[k] = w;
    } // end for loop.

    return gains;
} // end idealLowpassCoef


// idealDifferentiatorCoef
// this function returns N gains from an ideal low pass filter.
// This is equivilent to a rectangular window.
// NOTE: the length must be odd.
// @param N - the length of the filter.
//
// @return - the filter coefficients given as an array.
template <class T>
T *idealDifferentiatorCoef(uint16_t N)
{
    uint16_t M = N / 2; // returns the center index of the filter.
    if (N % 2 == 0) { return NULL; }
    // init the gains
    T *gains = new T[N];

    for (int16_t k = 0; k < N; k++)
    {
        double w;
        if (k == M) { w = 0.0; }
        else { w = (cos(M_PI * (k - M)) / (k - M)) -
            (sin(M_PI * (k - M)) / (M_PI * (k - M) * (k - M))); }

        gains[k] = w;
    } // end for loop.

    return gains;
} // end idealLowpassCoef


// calcKaiserLen
// This function applies a hamming window to an arbituary input
// @param A - the stopband attenuation required (dB).
// @param deltaW - the size of the frequency between pass and stop bands.
//
// @return - length of filter required.
uint16_t calcKaiserLen(double A, double deltaW)
{
    double D;
    if (A > 21.0) {
        D = (A - 7.95) / 14.36;
    } else {
        D = 0.922;
    }

    uint16_t N = ceil((D / deltaW) + 1);
    if (N % 2 == 0) { N++; } // check to make sure is odd length.

    return N;
} // end calcKaiserLen

#define EPS (1.E-9)

// besselFunc
// calculate the bessel function of the first order.
// This is taken directly from [1] p. 472.
double besselFunc(double x)
{
    int n = 1;
    double S = 1;
    double D = 1;
    double T;

    while (D > (EPS * S)) {
        T = x / (2 * n++);
        D *= T * T;
        S += D;
    } // end while

    return S;
}




#endif
