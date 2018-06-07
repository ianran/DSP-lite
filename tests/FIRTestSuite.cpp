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

// FIRTestSuite.cpp
// Written Ian Rankin - June 2018
//
// This is a test suite for the FIR filter to make sure
// it is working correctly.

#include <iostream>
#include <FIRFilter.h>
#include <Filter.h>

float gains[] = {1.0, 1.0, 1.0, 1.0, 1.0};

int main(int argc, char **argv)
{

    ////////////////// Test 1 ///////////////////
    float y[] = {1,2,3,4,5,5,5,5,5,5};

    // Test that outputs are correct for basic block filter.
    Filter<float> *filter1 = new FIRFilter<float>(gains, 5);

    for (int i = 0; i < 10; i++) {
        float result = filter1->filter(1.0);
        if (result != y[i]) {
            std::cerr << "FAILED: test 1 for simple block filtering." << std::endl;
            return -1;
        } // end if
    } // end for

    ///////////////// Test 2 ///////////////////////
    int gains2[] = {3,-1,1};
    int y2[] = {3,2,3,3,3};

    FIRFilter<int> filter2;
    filter2.setGains(gains2, 3);

    for (int i = 0; i < 5; i++) {
        int result = filter2.filter(1);
        //std::cout << result << " y2 = " << y2[i] << " " << (int)(result != y2[i]) << std::endl;
        if (result != y2[i]) {
            std::cerr << "FAILED: test 2 for simple filtering." << std::endl;
            return -1;
        } // end if
    } // end for

    ///////////////////// Test 3 /////////////////////////

    double gains3[] = {0.1, 0.2, 0.3, 0.4, 0.5};
    double y3[] = {0.1, 0.4, 1.0, 2.0};

    FIRFilter<double> filter3(gains3, 5);

    for (int i = 1; i < 5; i++) {
        double result = filter3.filter(i);
        if (result != y3[i-1]) {
            std::cerr << "FAILED: test 3 for simple filtering." << std::endl;
            std::cerr << "Result = " << result << " y3[i] = " << y3[i] << std::endl;
            return -1;
        } // end if
    }





} // end main
