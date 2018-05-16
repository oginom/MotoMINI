/*
 * MotoMINI.cpp
 */

#include "MotoMINI.h"
#include <math.h>

float Tdiff(transmat T1, transmat T2) {
    float ret = 0.0;
    rep3(i) rep3(j) ret += pow2(T1.R[i][j] - T2.R[i][j]);
    rep3(i) ret += pow2(T1.p[i] - T2.p[i]) * P_DIFF_SCALE;
    return ret;
}

MotoMINI::MotoMINI() {
    mdl = new MotoMINIModel();
    ctl = new PDController();
}

void MotoMINI::exec(float dt) {
    std::vector<Trajectory*>::iterator it;
    float overtime = dt;
    while (trajvec.size() > 0) {
        it = trajvec.begin();
        (*it)->exec(overtime);
        overtime = (*it)->overtime();
        if (0 < overtime) {
            it = trajvec.erase(it);
            //s = NULL;
        } else {
            break;
        }
    }
    if (it != trajvec.end()) {
        //transmat targetT = (*it)->getTransform();
        float observed[6] = {0};
        //float *target = mdl->inverseKinematics(targetT);
        float *target = (*it)->getTarget();
        ctl->exec(dt, observed, target);
    }
}

