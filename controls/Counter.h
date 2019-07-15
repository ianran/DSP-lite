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

// Counter.h
// Written Ian Rankin - July 2019
//
// A counter object to continuously return a 1, 0, -1 to the trajectory
// generator filter.

#ifndef __COUNTER__
#define __COUNTER__

template <class T>
class Counter {
public:
    Counter(T startLocation = 0) {}

    void setSetpoint(T Setpoint) { setpoint = Setpoint; }

    // update
    // This should be called at periodic time intervals, which returns
    // a 1 to count up, 0 if there, or -1 to go down, with a small value if a
    // 1 will overshoot the setpoint.
    //
    // @return - output of counter.
    T update() {
        T diff = setpoint - loc;

        if (diff == 0.0) {
            return 0.0;
        } else if (diff >= 1.0) {
            loc += 1.0;
            return 1.0;
        } else if (diff <= -1.0) {
            loc += -1.0;
            return -1.0;
        } else { // and < 1.0
            loc += diff;
            return diff;
        }
    }

private:
    T loc;
    T updateRate;
    T setpoint;
};

#endif
