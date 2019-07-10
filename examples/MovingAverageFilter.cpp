/* Copyright 2019 Ian Rankin
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

// MovingAverageFilter.cpp
// Written Ian Rankin - July 2019
//
// An example showing a basic usage of a moving average filter.
//

// Depends:
// FIRFilter.h
// FIRFilter.hpp
// FilterUtility.h
// FilterUtility.hpp
// Filter.h

#include <FilterUtility.h>
#include <FIRFilter.h>
#include <cmath>
#include <iostream>

int16_t gains[] = {1,1,1,1,1};

int main(int argc, char **argv) {
    // create FIRFilter.
    FIRFilter<int16_t> filter(gains, 5);

    int16_t in;
    int16_t out;
    while (true) {
        in = 3; // some input.
        out = filter.filter(in);
        std::cout << out << std::endl;
    }
}
