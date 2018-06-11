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

// FIRIdealFilterSuite.cpp
// Written Ian Rankin - June 2018
//
// A test suite to show that various filters are working as designed.
//

#include <iostream>
#include <FIRFilter.h>
#include <FilterUtility.h>
#include <cmath>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    float *lowPassGains = idealFilterCoef<float>(M_PI / 2.0, 15);
    FIRFilter<float> lowPassRect(lowPassGains, 15);

    ////////////////// Test removes high freq data. /////////////////
    for (int i = 0; i < 50; i++) {
        float x = (i % 2) ? 1 : -1;
        float out = lowPassRect.filter(x);
        if (i > 21) {
            // check filter is past saturation period
            if (out > 0.1 && out > -0.1) {
                cout << "FAILED: lowpass allowed output = " << out << endl;
                return -1;
            }
        }
    }

    //////////////// Test keeps low frequency data.

    for (int i = 0; i < 50; i++) {
        float x = (i % 2) ? 1 : -1;
        float out = lowPassRect.filter(1.0);
        if (i > 21) {
            // check filter is past saturation period
            if (out < 0.9) {
                cout << "FAILED: lowpass didn't pass 1: output = " << out << endl;
                return -1;
            }
        }
    }


    /////////////// Test for kaiser window of tight requirements

    double A = 60.0;
    uint16_t length = calcKaiserLen(A, M_PI / 100.0);
    cout << "calculated kaiser length = " << length  << endl;

    // create filter coef, and apply kaiser window.
    double *gains = idealFilterCoef<double>(M_PI / 2.0, length);
    applyKaiserWindow<double>(gains, length, A);

    FIRFilter<double> lowKaiser(gains, length);

    ////////////////// Test removes high freq data. /////////////////
    for (int i = 0; i < 2000; i++) {
        double x = (i % 2) ? 1 : -1;
        double out = lowPassRect.filter(x);
        if (i > 200) {
            // check filter is past saturation period
            if (out > 0.002 && out > -0.002) {
                cout << "FAILED: lowpass allowed output = " << out << endl;
                return -1;
            }
        }
    }

} // end main
