/*
 * Trajectory.cpp
 */

#include "Trajectory.h"

void Trajectory::exec(float dt) {
    std::cout << "Trajectory::exec" << std::endl;
    spent += dt;
}

float Trajectory::overtime() {
    return spent - dur;
}

float *Trajectory::getTarget() {
    return target;
}

//JointSpaceTrajectory::JointSpaceTrajectory(RobotModel *mdl) {
//JointSpaceTrajectory::JointSpaceTrajectory() {
//}

