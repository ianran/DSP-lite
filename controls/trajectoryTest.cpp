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

// trajectoryTest.cpp
// Written Ian Rankin July 2019
//
//

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <TrajectoryGenerator.h>

int loopRate = 50;
TrajectoryGenerator<float> tg(5.0, 5.0, 5.0, loopRate);
//TrajectoryGenerator<float> tg(5.0, 1.0, loopRate);

void setpointCB(const std_msgs::Float32ConstPtr &msg) {
    //ROS_INFO_STREAM("Yo got called data = " << msg->data);
    tg.setpoint(msg->data);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "trajectoryTest");
    ros::NodeHandle n;
    ros::Publisher pubPos = n.advertise<std_msgs::Float32>("position", 500);
    ros::Publisher pubVel = n.advertise<std_msgs::Float32>("velocity", 500);
    ros::Subscriber sub = n.subscribe("setpoint", 500, setpointCB);

    ros::Rate r(loopRate);


    //TrajectoryGenerator<float> tg(5.0, 1.0, loopRate);
    tg.setpoint(0);

    while (ros::ok()) {
        float vel;
        float pos;

        tg.update(pos, vel);
        std_msgs::Float32 msg;
        msg.data = pos;
        pubPos.publish(msg);
        msg.data = vel;
        pubVel.publish(msg);
        ros::spinOnce();
        r.sleep();
    }

} // end main
