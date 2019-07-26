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

// TrajectoryGenerator.h
// Written Ian Rankin - July 2019
//
// Returns a real-time trapezoidal or s-curve velocity profile.

#ifndef __TRAJECTORY_GENERATOR__
#define __TRAJECTORY_GENERATOR__

#include <FIRFilter.h>
#include <Counter.h>
#include <cmath>


// generateTrapFilter
// Generate a square pulse for the trapezoidal profile.
// @param maxVel [in] - the max velocity of the filter block.
// @param maxAccel [in] - the max acceleration of the filter block.
// @param updateRate [in] - the rate the trajectory generator is updated.
// @param gains [out] - the output pointer of the gains.
//
// @return - length of the trap filter.
template <class T>
int generateTrapFilter(T maxVel, T maxAccel, T updateRate, T *&gains);


// generateJerkLimitedFilter
// Generate a square pulse for the trapezoidal profile.
// @param maxVel [in] - the max velocity of the filter block.
// @param maxAccel [in] - the max acceleration of the filter block.
// @param maxJerk [in] - the max jerk allowed by the filter block.
// @param updateRate [in] - the rate the trajectory generator is updated.
// @param gains [out] - the output pointer of the gains.
//
// @return - length of the trap filter.
template <class T>
int generateJerkLimitedFilter(T maxVel, T maxAccel, T maxJerk,
        T updateRate, T *&gains);

template <class T>
class TrajectoryGenerator {
public:
    // generate a trajectory generator as a trap profile.
    TrajectoryGenerator(T MaxVel, T MaxAccel, T UpdateRate);

    // generate a trajectory generator as a S-curve.
    TrajectoryGenerator(T MaxVel, T MaxAccel, T MaxJerk, T UpdateRate);

    void setpoint(T setpoint);
    // update
    // get the latest update on the trajectory generator.
    // @param position [out] - position output of the trajectory generator.
    // @param vel [out]- velocity output of the trajectory generator.
    void update(T &position, T &vel);

private:
    Counter<T> counter;
    FIRFilter<T> filter;

    T pos;
    T maxVel;
    T updateRate;
};

#include <TrajectoryGenerator.hpp>

#endif
