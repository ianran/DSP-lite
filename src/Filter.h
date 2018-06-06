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

// Filter.h
// Written Ian Rankin June 2018
//
// The base filter class to build from.
// All other filters will extend this virtual filter class.
//

#ifndef __FILTER__
#define __FILTER__

template <typename T>
class Filter {
public:
    Filter() {}
    ~Filter() {}

    // update
    // The main function of all filter subclasses, is
    // the filter function, which given the next input to the
    // filter will return the output of the filter.
    // @param x - the input to the filter.
    //
    // @return - output of filter, if there is an error NaN.
    virtual T filter(T x) = 0;

    // getOutput
    // This function simply gets the last output of the filter, without changing
    // internal state of the filter.
    //
    // @return - last output of filter, if there is an error NaN.
    virtual T getOutput() = 0;
};

#endif
