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

// TrajectoryGenerator.hpp
// Written Ian Rankin - July 2019
//
// Returns a real-time trapezoidal or s-curve velocity profile.

#ifndef __TRAJECTORY_GENERATOR_IMPL__
#define __TRAJECTORY_GENERATOR_IMPL__


#include <iostream>

// generateTrapFilter
// Generate a square pulse for the trapezoidal profile.
template <class T>
int generateTrapFilter(T maxVel, T maxAccel, T updateRate, T *&gains) {
    int lenFilter = int(ceil((maxVel / maxAccel) * updateRate));

    gains = new T[lenFilter];

    T val = maxVel / T(lenFilter);
    for (int i = 0; i < lenFilter; i++) {
        gains[i] = val;
    }

    return lenFilter;
}


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
        T updateRate, T *&gains, int &jerkLen)
{
    std::cout << "Called generateJerkLimitedFilter maxVel = " << maxVel << std::endl;
    //int lenJerkPhase = int(ceil((maxAccel / maxJerk) * updateRate));
    //T jerkVel = lenJerkPhase * 0.5 *
    jerkLen = int(ceil((maxAccel / maxJerk) * updateRate));
    T jerkVel = 0.5 * jerkLen * maxAccel / updateRate;

    std::cout << "jerkLen = " << jerkLen << " jerkVel = " << jerkVel << std::endl;
    if (jerkVel > maxVel) {
        std::cout << "jerk to low to generate S-curve filter" << std::endl;
        return -1;
    }

    int accelLen = (maxVel - jerkVel) * (updateRate / maxAccel);
    int totalLen = (jerkLen * 2) + accelLen;

    int idx = 0;
    std::cout << "accelLen = " << accelLen << " jerkLen = " << jerkLen << std::endl;
    std::cout << "total len = " << totalLen << std::endl;
    gains = new T[totalLen];
    float height = maxVel / (accelLen + jerkLen);
    for (int i = 0; i < jerkLen; i++) {
        gains[idx] = i * height / jerkLen;
        idx++;
    }
    for (int i = 0; i < accelLen; i++) {
        gains[idx] = height;
        idx++;
    }
    for (int i = 0; i < jerkLen; i++) {
        gains[idx] = (jerkLen - i - 1) * height / jerkLen;
        idx++;
    }

    return totalLen;
}



// generate a trajectory generator as a trap profile.
template <class T>
TrajectoryGenerator<T>::TrajectoryGenerator(T MaxVel, T MaxAccel, T UpdateRate)
{
    pos = 0.0;
    maxVel = MaxVel;
    updateRate = UpdateRate;
    T *gains;
    uint16_t length = generateTrapFilter(MaxVel, MaxAccel, UpdateRate, gains);
    filter.setGains(gains, length);
    counter.setGap(length);
}

// generate a trajectory generator as a S-curve.
template <class T>
TrajectoryGenerator<T>::TrajectoryGenerator
    (T MaxVel, T MaxAccel, T MaxJerk, T UpdateRate)
{
    pos = 0.0;
    maxVel = MaxVel;
    updateRate = UpdateRate;
    T *gains;
    int jerkLen;
    int16_t length = generateJerkLimitedFilter(MaxVel, MaxAccel, MaxJerk, UpdateRate, gains, jerkLen);
    std::cout << "length = " << length << " jerkLen = " << jerkLen << std::endl;
    for (int i = 0; i < length; i++) {
        std::cout << "i: " << i << " : " << gains[i] << std::endl;
    }


    if (length < 0) {length = 0;}
    filter.setGains(gains, (uint16_t)length);
    for (int i = 0; i < length; i++) {
        std::cout << "i: " << i << " : " << gains[i] << std::endl;
    }
    counter.setGap(length - jerkLen);
}

template <class T>
void TrajectoryGenerator<T>::setpoint(T setpoint) {
    counter.setSetpoint(setpoint * (updateRate / maxVel));
}

template <class T>
void TrajectoryGenerator<T>::update(T &position, T &vel)
{
    vel = filter.filter(counter.update());
    //vel = filter.filter(1.0);
    pos += vel / updateRate;
    position = pos;
}



#endif
