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

// FIRFilter.hpp
// Written Ian Rankin - June 2018
//
// Depends:
// filter.h
// FIRFilter.h
//
// This is the class for all Finite Impulse Response filters.
// implemented using a circular buffer.
//

#ifndef __FIR_FILTER_IMPL__
#define __FIR_FILTER_IMPL__

// Constructor
// Give it your FIR coefficients as an array, and length of the array.
// These can be changed later, and placing NULL is ok.
// Will allocate needed buffer. Set length to -1 if unknown size.
//
// @param coefficients - the FIR coefficients for the filter.
// @param length - the length of the filter. -1 for unknown.
template <typename T>
FIRFilter<T>::FIRFilter()
{
    length = -1; // set default to not got strange results.
    setGains(NULL, -1);
} // end constructor

// Constructor
// Give it your FIR coefficients as an array, and length of the array.
// These can be changed later, and placing NULL is ok.
// Will allocate needed buffer. Set length to -1 if unknown size.
//
// @param coefficients - the FIR coefficients for the filter.
// @param length - the length of the filter. -1 for unknown.
template <typename T>
FIRFilter<T>::FIRFilter(T *coefficients, uint16_t Length)
{
    length = -1; // set default to not got strange results.
    setGains(coefficients, Length);
} // end constructor


// setGains
// set gains lets you reset the current gains to any FIR
// gains. Will not delete old gains / coefficients.
//
// @param coefficients - the coefficients used in the filter.
// @param length - the length of the filter.
template <typename T>
void FIRFilter<T>::setGains(T *coefficients, uint16_t Length)
{
    if (Length != length && Length > 0) {
        // reallocate correct size buffer
        buffer = new T[Length];
        for (uint16_t i = 0; i < length; i++) { buffer[i] = 0.0; }
    }

    length = Length;
    gains = coefficients;
}


// update
// The main function of all filter subclasses, is
// the filter function, which given the next input to the
// filter will return the output of the filter.
// @param x - the input to the filter.
//
// @return - output of filter, if there is an error NaN.
template <typename T>
T FIRFilter<T>::filter(T x)
{
    // TODO: actually write this code!
    output = x;
    return output;
} // end filter function

// getOutput
// This function simply gets the last output of the filter, without changing
// internal state of the filter.
//
// @return - last output of filter, if there is an error NaN.
template <typename T>
T FIRFilter<T>::getOutput()
{
    return output;
} // end getOutput function.














#endif
