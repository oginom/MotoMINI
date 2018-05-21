/*
 * Trajectory.h
 */

#pragma once

#include "numogi.h"
#include "RobotModel.h"

class Trajectory {
public:
    float dur;
    float spent;
    float target[6];
    //jointstatus targetjs;
    Trajectory() {
        spent = 0;
        dur = 1;
    }
    virtual void exec(float dt);
    virtual float overtime();
    //virtual transmat getTransform();
    virtual float *getTarget();
};
typedef Trajectory traj;

class JointSpaceTrajectory : public Trajectory {
public:
    RobotModel *mdl;
    JointSpaceTrajectory() {}
    JointSpaceTrajectory(RobotModel *mdl_) {
        mdl = mdl_;
    }
    //Kinematics* k;
    float phi[6];
    float dphi[6];
};

