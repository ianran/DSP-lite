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
// y[n] = (1 / a0)(b0*x[n] + b1*x[n-1] + ... + bk*x[n-k] -
//                 a1*y[n-1] - a2*y[n-2] - ... - aj*yn[-k])
//
// a = feedback coefficients
// b = feedforward coeffcients.
//
// However computation is done in cannonical from, which reverse the order of operations,
// and reduces the memory usage by half.
//
// TODO: Need to re-write dealing buffer, lengths for 2 different buffer lengths

#ifndef __IIR_FILTER__
#define __IIR_FILTER__

#include "Filter.h"
#include <cstdint>
#include <iostream>

template <class T>
class IIRFilter: public Filter<T> {
public:
    // Constructor
    // Give it your FIR coefficients as an array, and length of the array.
    // These can be changed later, and placing NULL is ok.
    // Will allocate needed buffer. Set length to -1 if unknown size.
    //
    // @param feedForwardCoef - the feed forward coefficients for the filter.
    // @param feedbackCoef - the feedback coefficients for the filter.
    // @param forwardlength - the length of the feed foward filter.
    // @param feedbackLength - the length of the feedback gains.
    IIRFilter(T *feedForwardCoef, T *feedbackCoef,
         uint16_t forwardLength, uint16_t backLength);
    IIRFilter();

    // update
    // The main function of all filter subclasses, is
    // the filter function, which given the next input to the
    // filter will return the output of the filter.
    // @param x - the input to the filter.
    //
    // @return - output of filter, if there is an error NaN.
    T filter(T x);

    // getOutput
    // This function simply gets the last output of the filter, without changing
    // internal state of the filter.
    //
    // @return - last output of filter, if there is an error NaN.
    T getOutput();


    // setGains
    // set gains lets you reset the current gains to any FIR
    // gains. Will not delete old gains / coefficients.
    //
    // @param feedForwardCoef - the feed forward coefficients for the filter.
    // @param feedbackCoef - the feedback coefficients for the filter.
    // @param forwardlength - the length of the feed foward filter.
    // @param feedbackLength - the length of the feedback gains.
    void setGains(T *feedForwardCoef, T *feedbackCoef,
                uint16_t forwardLength, uint16_t backLength);

    // getFeedbackGains
    // This will return the array of the a vector gains.
    // You will be free to change the set of gains. (Don't abuse this!)
    //
    // @return - the gains as a single array.
    T *getFeedbackGains(){  return fbGains; }

    // getFeedForwardGains
    // This will return the array of the b vector gains.
    // You will be free to change the set of gains. (Don't abuse this!)
    //
    // @return - the gains as a single array.
    T *getFeedForwardGains(){  return ffGains; }

    // getLength
    // returns the order of the FIR filter.
    uint16_t getLength() const { return length; }

private:
    T *buffer;
    T *ffGains; // feedforward gains.
    T *fbGains;
    uint16_t curBufLoc;
    uint16_t length;
    uint16_t ffLength;
    uint16_t fbLength;
    T output;
};

// include "Implementation file
#include "IIRFilter.hpp"

#endif
