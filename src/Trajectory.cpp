/*
 * Trajectory.cpp
 */

#include "Trajectory.h"

void Trajectory::exec(float dt) {
    //std::cout << "Trajectory::exec" << std::endl;
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

void JointSpaceTrajectory::setup(
        float dur_,
        float phi0[6],
        float phif[6],
        float dphi0[6],
        float dphif[6]) {
    dur = dur_;
    rep (i, 6) {
        a0[i] = phi0[i];
        a1[i] = dphi0[i] * dur;
        a2[i] = 3 * (phif[i] - phi0[i]) - (2 * dphi0[i] + dphif[i]) * dur;
        a3[i] = -2 * (phif[i] - phi0[i]) + (dphi0[i] + dphif[i]) * dur;
    }
}

void JointSpaceTrajectory::exec(float dt) {
    this->Trajectory::exec(dt);
    float r = min(1.0f, spent / dur);
    rep(i, 6) {
        target[i] = a0[i] + a1[i] * r + a2[i] * r * r + a3[i] * r * r * r;
    }
}

void OginoTrajectory::exec(float dt) {
    this->Trajectory::exec(dt);

    static const int lines[16][2] = {
        {1, 1},
        {0, 1},
        {2, 1},
        {0, 0},
        {1, 0},
        {0, 1},
        {2, 0},
        {0, 0},
        {2, 1},
        {0, 1},
        {1, 1},
        {0, 0},
        {2, 0},
        {0, 1},
        {1, 0},
        {0, 0}
    };
    float r = min(1.0f, spent / dur) * 16.0f;
    int s = min(15, (int)r);
    float rs = r - (float)s;
    int is = lines[s][0];
    int ds = lines[s][1];
    float r1 = ds * (1 - rs) + (1 - ds) * rs;
    float r2 = ds * rs + (1 - ds) * (1 - rs);
    target[is] = phi_min[is] * r1 + phi_max[is] * r2;
}


