
#ifndef _MOTOMINI_H_
#define _MOTOMINI_H_

#include <iostream>
#include <vector>
#include "numogi.h"
#include "Trajectory.h"
#include "Controller.h"
#include "RobotModel.h"

typedef vector3f vec;
//typedef vector2f vec2;
typedef matrix33f mat;
typedef vec point;
typedef vec velo;

#define P_DIFF_SCALE (0.000001)

float Tdiff(transmat T1, transmat T2);

//class Kinematics {
//public:
//    static transmat forwardKinematics() {
//        return transmat();
//    }
//};

//struct jointstatus {
//    float phi[6];
//    float dphi[6];
//};
//typedef jointstatus js;

class MotoMINI {
public:
    std::vector<Trajectory*> trajvec;
    RobotModel *mdl;
    PDController *ctl;

    MotoMINI();
    void exec(float dt);
};

#endif // _MOTOMINI_H_

