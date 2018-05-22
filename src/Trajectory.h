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
    float a0[6], a1[6], a2[6], a3[6];
    //RobotModel *mdl;
    JointSpaceTrajectory() {}
    JointSpaceTrajectory(
            float dur_,
            float phi0[6],
            float phif[6]) {
        float dphi0[6] = {0};
        float dphif[6] = {0};
        setup(dur_, phi0, phif, dphi0, dphif);
    }
    JointSpaceTrajectory(
            float dur_,
            float phi0[6],
            float phif[6],
            float dphi0[6],
            float dphif[6]) {
        setup(dur_, phi0, phif, dphi0, dphif);
    }
    JointSpaceTrajectory(
            float dur_,
            RobotModel *mdl,
            transmat T0,
            transmat Tf) {
        float phi0[6];
        mdl->inverseKinematics(T0, phi0);
        float phif[6];
        mdl->inverseKinematics(Tf, phif);
        float dphi0[6] = {0};
        float dphif[6] = {0};
        setup(dur_, phi0, phif, dphi0, dphif);
    }

    void setup(
        float dur_,
        float phi0[6],
        float phif[6],
        float dphi0[6],
        float dphif[6]
    );

    //Kinematics* k;
    float phi[6];
    float dphi[6];

    virtual void exec(float dt);
};

class OginoTrajectory : public Trajectory {
public:
    float phi_min[6];
    float phi_max[6];
    OginoTrajectory(float *phi_min_, float *phi_max_, float dur_) {
        rep (i, 6) {
            target[i] = phi_min_[i];
            phi_min[i] = phi_min_[i];
            phi_max[i] = phi_max_[i];
        }
        dur = dur_;
    }
    virtual void exec(float dt);
};


