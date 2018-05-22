/*
 * Controller.cpp
 */

#include "Controller.h"

PDController::PDController() {
    rep (i, 6) { obs[i] = tgt[i] = 0; }
}

void PDController::exec(float dt, float *observed, float *target) {
    static const float Kp = 1.0;
    static const float Kd = 1.0;
    float torque[6];
    float dobs[6], dtgt[6];
    rep (i, 6) {
        dobs[i] = (observed[i] - obs[i]) / dt;
        dtgt[i] = (target[i] - tgt[i]) / dt;
        torque[i] = (target[i] - observed[i]) * Kp + (dtgt[i] - dobs[i]) * Kd;
        obs[i] = observed[i];
        tgt[i] = target[i];
    }
    std::cout << "torque:" << torque << std::endl;
}
