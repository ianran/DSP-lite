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

// FilterUtility.h
// Written Ian Rankin - June 2018
//
// Depends:
// FilterUtility.hpp
//
// This is utility functions for various filter designs.

#ifndef __FILTER_UTILITY__
#define __FILTER_UTILITY__


// applyHammingWindow
// This function applies a hamming window to an arbituary input
// @param input - the input array to apply a hamming window to.
// @param length - the length of the input array.
//
// @return - 0 for success, else failure.
template <class T>
int applyHammingWindow(T *input, uint16_t length);


// applyKaiserWindow
// This function applies a kaiser window to an arbituary input
// @param input - the input array to apply a hamming window to.
// @param length - the length of the input array.
// @param A - stopband attenuation required in dB
// NOTE: The length must be odd.
//
// @return - 0 for success, else failure.
template <class T>
int applyKaiserWindow(T *input, uint16_t N, double A);

// calcKaiserLen
// This function applies a hamming window to an arbituary input
// @param A - the stopband attenuation required (dB).
// @param deltaW - the size of the frequency between pass and stop bands.
//
// @return - length of filter required.
uint16_t calcKaiserLen(double A, double deltaW);

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
T *idealFilterCoef(double omegaCutoff, uint16_t N, bool isHighPassFilter = false);


// idealDifferentiatorCoef
// this function returns N gains from an ideal low pass filter.
// This is equivilent to a rectangular window.
// NOTE: the length must be odd.
// @param N - the length of the filter.
//
// @return - the filter coefficients given as an array.
template <class T>
T *idealDifferentiatorCoef(uint16_t N);

// besselFunc
// calculate the bessel function of the first order.
// This is taken directly from [1] p. 472.
double besselFunc(double x);





#include "FilterUtility.hpp"

#endif
