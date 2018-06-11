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

// IIRTestSuite.cpp
// Written Ian Rankin - June 2018
//
// This is a test suite for the IIR filter to make sure
// it is working correctly.

#include <iostream>
#include <IIRFilter.h>
#include <Filter.h>



int main(int argc, char **argv)
{

    ////////////////// Test 1 ///////////////////
    float y[] = {0, 0, 1, 1, 1.5, 1.5, 1.75, 1.75};

    float ffGain1[] = {0, 0, 1};
    float fbGain1[] = {0, -0.5};

    // Test that outputs are correct for basic block filter.
    Filter<float> *filter1 = new IIRFilter<float>(ffGain1, fbGain1, 3, 2);

    for (int i = 0; i < 8; i++) {
        float result = filter1->filter(1.0);
        //std::cout << result << std::endl;
        if (result != y[i]) {
            std::cout << "y["<<i<<"] = " << y[i] << " result = " << result << std::endl;
            std::cerr << "FAILED: test 1 for simple IIR filtering." << std::endl;
            return -1;
        } // end if
    } // end for


    //////////////////////////// Test 2 ///////////////////////////////

    int x2[] = {1,3,2,5,4,6,0,0,0};
    int y2[] = {1,4,7,14,17,27,28,29,27};

    int ffGain2[] = {1, 1, 2};
    int fbGain2[] = {0, 0, -1};

    IIRFilter<int> filter2;
    filter2.setGains(ffGain2, fbGain2, 3, 3);

    for (int i = 0; i <= 8; i++)
    {
        int res = filter2.filter(x2[i]);

        if (res != y2[i]) {
            std::cerr << "FAILED: test 2 for IIR filtering." << std::endl;
            return -1;
        }
    }

    if (filter2.getFeedbackGains() == NULL) {
        std::cout << "FAILED: feedback gains get." << std::endl;
        return -1;
    }
    if (filter2.getFeedForwardGains() == NULL) {
        std::cout << "FAILED: feed forward gains get." << std::endl;
        return -1;
    }
    if (filter2.getLength() != 4) {
        std::cout << "FAILED: length incorrect." << std::endl;
        return -1;
    }





    // test passed if reached here.
    std::cout << "PASSED all tests!" << std::endl;
    return 0;
} // end main
