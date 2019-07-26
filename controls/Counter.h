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

#ifndef __COUNTER_TRAJ__
#define __COUNTER_TRAJ__

template <class T>
class Counter {
public:
    Counter(T startLocation = 0) { gapNum = 0; i = 0; }

    void setGap(int GapNum) { gapNum = GapNum; i = gapNum; }

    void setSetpoint(T Setpoint) { setpoint = Setpoint; }

    // update
    // This should be called at periodic time intervals, which returns
    // a 1 to count up, 0 if there, or -1 to go down, with a small value if a
    // 1 will overshoot the setpoint.
    //
    // @return - output of counter.
    T update() {
        T diff = setpoint - loc;
        T change;

        if (diff == 0.0) {
            change = 0.0;
        } else if (diff >= 1.0) {
            change = 1.0;
        } else if (diff <= -1.0) {
            change = -1.0;
        } else { // and < 1.0
            change = diff;
        }

        int8_t sign = 0;
        if (diff > 0) { sign = 1; }
        else if (diff < 0) { sign = -1; }

        if ((prev != 0 && prev != sign)) {
            i = 0;
            change = 0.0;
        } else {
            i++;
        }

        if (!(i > gapNum || prevDir == sign)) {
            change = 0.0;
        }

        if (change > 0) { prevDir = 1; }
        else if (change < 0) { prevDir = -1; }

        loc += change;

        prev = sign;
        return change;
    }

private:
    T loc;
    int8_t prev;
    int8_t prevDir;
    int gapNum;
    int i;
    T updateRate;
    T setpoint;
};

#endif
