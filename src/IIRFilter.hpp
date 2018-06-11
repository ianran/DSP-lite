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

 // IIRFilter
 // Written Ian Rankin - June 2018
 //
 // Depends:
 // filter.h
 // impl/IIRFilter.hpp
 //
 // This is the class for all Infinte Impulse Response filters.
 // implemented using a circular buffer, in cascade form.
 // By using cannonical form, only a single circular buffer is required.
 //
 // The filter is assumed to be given as the form:
 // y[n] = (b0*x[n] + b1*x[n-1] + ... + bk*x[n-k] -
 //                 a1*y[n-1] - a2*y[n-2] - ... - ak*yn[-k])
 //
 // NOTE: a vector, starts at a1, and must be one shorter then b.
 //
 // a = feedback coefficients
 // b = feedforward coeffcients.
 //
 // However computation is done in cannonical from, which reverse the order of operations,
 // and reduces the memory usage by half.
 //

#ifndef __IIR_FILTER_IMPL__
#define __IIR_FILTER_IMPL__

#include "IIRFilter.h"

// Constructor
// Give it your FIR coefficients as an array, and length of the array.
// These can be changed later, and placing NULL is ok.
// Will allocate needed buffer. Set length to -1 if unknown size.
//
// @param coefficients - the FIR coefficients for the filter.
// @param forwardlength - the length of the feed foward filter.
// @param feedbackLength - the length of the feedback gains.
template <typename T>
IIRFilter<T>::IIRFilter()
{
    length = -1; // set default to not got strange results.
    setGains(NULL, NULL, -1, -1);
    curBufLoc = 0;
} // end constructor

// Constructor
// Give it your FIR coefficients as an array, and length of the array.
// These can be changed later, and placing NULL is ok.
// Will allocate needed buffer. Set length to -1 if unknown size.
//
// @param feedForwardCoef - the feed forward coefficients for the filter.
// @param feedbackCoef - the feedback coefficients for the filter.
// @param length - the length of the filter. -1 for unknown.
template <typename T>
IIRFilter<T>::IIRFilter(T *feedForwardCoef, T *feedbackCoef,
                    uint16_t forwardLength, uint16_t backLength)
{
    length = -1; // set default to not got strange results.
    setGains(feedForwardCoef, feedbackCoef, forwardLength, backLength);
    curBufLoc = 0;
} // end constructor


// setGains
// set gains lets you reset the current gains to any FIR
// gains. Will not delete old gains / coefficients.
//
// @param feedForwardCoef - the feed forward coefficients for the filter.
// @param feedbackCoef - the feedback coefficients for the filter.
// @param forwardlength - the length of the feed foward filter.
// @param feedbackLength - the length of the feedback gains.
template <typename T>
void IIRFilter<T>::setGains(T *feedForwardCoef, T *feedbackCoef,
                    uint16_t forwardLength, uint16_t backLength)
{
    uint16_t newLength;
    // select the
    if (forwardLength > (backLength + 1)) { newLength = forwardLength; }
    else { newLength = backLength + 1; }

    if (newLength != length && newLength > 0) {
        // reallocate correct size buffer
        length = newLength;
        buffer = new T[length];
        for (uint16_t i = 0; i < length; i++) { buffer[i] = 0.0; }
    }

    ffLength = forwardLength;
    fbLength = backLength;

    ffGains = feedForwardCoef;
    fbGains = feedbackCoef;
}


// update
// The main function of all filter subclasses, is
// the filter function, which given the next input to the
// filter will return the output of the filter.
// @param x - the input to the filter.
//
// @return - output of filter, if there is an error NaN.
template <typename T>
T IIRFilter<T>::filter(T x)
{
    T w0 = 0.0; // this is the intermediate value to place into the buffer.
    // multiply feedback gains first.
    for (uint16_t i = 0; i < fbLength; i++) {
        // have circular buffer wrap around on itself, pull out
        // current gain.
        w0 += -buffer[(i + curBufLoc + 1) % length] * fbGains[i];
    }

    // place into current buffer location.
    buffer[curBufLoc] = w0 + x;

    output = 0.0;
    // perform feedfoward step.
    for (uint16_t i = 0; i < ffLength; i++) {
        // have circular buffer wrap around on itself, pull out
        // current gain.
        output += buffer[(i + curBufLoc) % length] * ffGains[i];
    }
    // update buffer location for next iteration.
    if (curBufLoc == 0) { curBufLoc = length; }
    curBufLoc--;

    return output;
} // end filter function

// getOutput
// This function simply gets the last output of the filter, without changing
// internal state of the filter.
//
// @return - last output of filter, if there is an error NaN.
template <typename T>
T IIRFilter<T>::getOutput()
{
    return output;
} // end getOutput function.



#endif
