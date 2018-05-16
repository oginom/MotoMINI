
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include "numogi.h"
#include "RobotModel.h"

class Trajectory {
public:
    float dur;
    //jointstatus targetjs;
    Trajectory() {}
    virtual void exec(float dt);
    virtual float overtime();
    //virtual transmat getTransform();
    virtual float *getTarget();
};
typedef Trajectory traj;

class JointSpaceTrajectory : public Trajectory {
public:
    JointSpaceTrajectory() {}
    //JointSpaceTrajectory(RobotModel *mdl);
    //Kinematics* k;
    float phi[6];
    float dphi[6];
};


#endif//_TRAJECTORY_H_
